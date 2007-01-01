/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2007 by Iowa State University
 *
 * Original Authors:
 *   Allen Bierbaum, Christopher Just,
 *   Patrick Hartling, Kevin Meinert,
 *   Carolina Cruz-Neira, Albert Baker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#include <string>
#include <string.h>
#include <boost/bind.hpp>

#include <vpr/vpr.h>
#include <vpr/System.h>
#include <vpr/IO/TimeoutException.h>
#include <vpr/IO/WouldBlockException.h>
#include <vpr/Util/Assert.h>

#include <drivers/Polhemus/Fastrak/FastrakStandalone.h>

bool FastrakStandalone::open()
{
   bool status(true);

   mSerialPort = new vpr::SerialPort(std::string(mConf.port));
   mSerialPort->setBlocking(false);
   mSerialPort->setOpenReadWrite();

   try
   {
      mSerialPort->open();
   }
   catch (vpr::IOException&)
   {
      return false;
   }

   {
      vpr::Uint32 baud;

      mSerialPort->clearAll();

      mSerialPort->setBreakByteIgnore(true);
      mSerialPort->setBadByteIgnore(true);
      mSerialPort->setRead(true);
      mSerialPort->setLocalAttach(true);
      mSerialPort->setUpdateAction(vpr::SerialTypes::NOW);
      mSerialPort->setCharacterSize(vpr::SerialTypes::CS_BITS_8);

      if ( mConf.found & (1 << BAUD) )
      {
         baud = mConf.baud;
      }
      else
      {
         baud = 9600;
      }
      mSerialPort->setOutputBaudRate(baud);
      mSerialPort->setInputBaudRate(baud);

      mSerialPort->flushQueue(vpr::SerialTypes::INPUT_QUEUE);
      mSerialPort->flushQueue(vpr::SerialTypes::OUTPUT_QUEUE);
   }

   return status;
}

void FastrakStandalone::trackerFinish()
{
   vpr::Uint32 bytes_written;
   mSerialPort->write("c", 1, bytes_written);
   vpr::System::sleep(1);

   mSerialPort->flushQueue(vpr::SerialTypes::INPUT_QUEUE);
   mSerialPort->close();

   mExitFlag = true;
   if ( NULL != mReadThread )
   {
      mReadThread->join();
      delete mReadThread;
      mReadThread = NULL;
   }
}

int FastrakStandalone::Read(int len)
{
   vpr::Uint32 bytes_read;

   int rem = len;
   unsigned char tempBuf[256];
   char *cp = (char *) tempBuf;

   vpr::Interval timeoutVal(100, vpr::Interval::Msec);
   for ( ;; )
   {
      //Passing in timeout val here to wait for input
      try
      {
         mSerialPort->read(cp, rem, bytes_read, timeoutVal);
      }
      catch (vpr::TimeoutException&)
      {
         continue;
      }
      catch (vpr::IOException&)
      {
         tempBuf[len - rem] = '\0';
         memcpy(mTrackerBuf, tempBuf, 256);
         return len - rem;
      }

      if ( (rem -= bytes_read) == 0 )
      {
         tempBuf[len] = '\0';
         memcpy(mTrackerBuf, tempBuf, 256);
         return len;
      }

      cp += bytes_read;
   }
}


void FastrakStandalone::readloop()
{
   vpr::Uint32 bytes_written;
   vpr::Uint32 sleep_time(10000000/mConf.baud);

/*
   // XXX: Maybe this could be replaced with VPR's signal abstraction?
#ifndef VPR_OS_Windows
   sigignore(SIGINT);
#endif
*/

   while ( !mExitFlag )
   {
      if ( mDoFlush )
      {
         mSerialPort->write("c", 1, bytes_written);
         vpr::System::usleep(sleep_time);
         mSerialPort->flushQueue(vpr::SerialTypes::INPUT_QUEUE);
         vpr::System::usleep(sleep_time);
         mSerialPort->write("C", 1, bytes_written);
      }

      Read(mConf.len);

      // The Polhemus docs state that you won't get more than 100 samples a
      // second best case (with one station), so I figure this is safe, and
      // it help with performance.
      vpr::System::msleep(10);

      mDoFlush = false;
//      if ( getppid() == 1 )
//      {
//         trackerFinish();
//         _exit(0);
//      }
   }
}

bool FastrakStandalone::readStatus()
{
   vpr::Uint32 bytes_read, bytes_written;

   //Set to non-continuous mode
   try
   {
      mSerialPort->write("c", 1, bytes_written);
   }
   catch (vpr::IOException&)
   {
      fprintf(stderr,
              "[FastrakStandalone] Failure setting non-continuous mode for tracker");
      return false;
   }

   mSerialPort->flushQueue(vpr::SerialTypes::INPUT_QUEUE);
   mSerialPort->flushQueue(vpr::SerialTypes::OUTPUT_QUEUE);
   vpr::System::msleep(100);//Sleep for 0.1 seconds

   //Set to non-continuous and request status
   try
   {
      mSerialPort->write("S", 1, bytes_written);
   }
   catch (vpr::IOException&)
   {
      fprintf(stderr,
              "[FastrakStandalone] Failure writing status command to tracker");
      return false;
   }

   int numPasses = 0;
   int numElapsedWaits=0;
   char buffer[1024];
   int state=0;
   while (numElapsedWaits<100&&state<4)
   {
      vpr::Interval timeoutVal(100, vpr::Interval::Msec);
      try
      {
         mSerialPort->read(buffer, 1, bytes_read, timeoutVal);
      }
      catch (vpr::TimeoutException)
      {
         ++numElapsedWaits;
         continue;
      }
      catch (vpr::WouldBlockException)
      {
         ++numElapsedWaits;
         continue;
      }
      catch (vpr::IOException&)
      {
         fprintf(stderr,
                 "[FastrakStandalone] Failure reading status byte from tracker");
         return false;
      }

      /* Read next byte and try matching status reply's prefix: */
      char input = buffer[0];
      switch (state)
      {
         case 0: // Haven't matched anything
            if (input == '2')
            {
               state = 1;
            }
            break;
         case 1: // Have matched '2'
            if (input == '2')
            {
               state = 2;
            }
            else if (input >= '1'  &&  input <= '4')
            {
               state = 3;
            }
            else
            {
               state = 0;
            }
            break;
         case 2: // Have matched '22'
            if (input == 'S')
            {
               state = 4;
            }
            else if (input == '2')
            {
               state = 2;
            }
            else if (input >= '1'  &&  input <= '4')
            {
               state = 3;
            }
            else
            {
               state = 0;
            }
            break;
         case 3: // Have matched 2[1,3,4]
            if (input == 'S')
            {
               state = 4;
            }
            else if (input == '2')
            {
               state = 1;
            }
            else
            {
               state = 0;
            }
            break;
      }

      if (numPasses++ > 1000)
      {
         vprDEBUG(vprDBG_ERROR, vprDBG_WARNING_LVL)
            << "[FastrakStandalone] Tracker appears to be stuck in "
            << "continuous mode. You may need to manually reset if the "
            << "software reset doesn't work. Attempting reset..."
            << std::endl << vprDEBUG_FLUSH;
         return false;
      }
   }

   /* Fail if we timed out while trying to match the prefix: */
   if (state != 4)
   {
      fprintf(stderr,
              "[FastrakStandalone] Failure getting status message from tracker)");
      return false;
   }

   /* Read rest of status reply until final CR/LF pair: */
   char* cPtr=buffer;
   numElapsedWaits = 0;
   state=0;
   while (numElapsedWaits < 100  &&
          state < 2)
   {
      vpr::Interval timeoutVal(100, vpr::Interval::Msec);
      try
      {
         mSerialPort->read(cPtr, 1, bytes_read, timeoutVal);
      }
      catch (vpr::TimeoutException&)
      {
         vpr::System::msleep(100);//Sleep for 0.1 seconds
         ++numElapsedWaits;
         continue;
      }
      catch (vpr::WouldBlockException&)
      {
         vpr::System::msleep(100);//Sleep for 0.1 seconds
         ++numElapsedWaits;
         continue;
      }
      catch (vpr::IOException&)
      {
         fprintf(stderr,
                 "[FastrakStandalone] Failure reading second round status byte from tracker\n");
         return false;
      }

      char input = *cPtr;
      ++cPtr;
      switch (state)
      {
         case 0: // Haven't matched anything
            if (input == '\r')
            {
               state = 1;
            }
            else
            {
               state = 0;
            }
            break;
         case 1: // Have matched CR
            if (input == 10)
            {
               state=2;
            }
            else if(input==13)
            {
               state=1;
            }
            else
            {
               state=0;
            }
            break;
      }
   }

   *cPtr=0;
   vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
      << "[FastrakStandalone] Tracker status: " << buffer
      << std::endl << vprDEBUG_FLUSH;

   return true;
}

bool FastrakStandalone::trackerInit()
{
   vprASSERT(mSerialPort->isOpen() && "Port must be open before initializing");
   vpr::Uint32 bytes_written;

//   static struct termios tc;
   char buf[256];
   char c;

   //Added this to help check on the status of the tracker at startup
   if ( ! readStatus() )
   {
      vprDEBUG(vprDBG_ERROR, vprDBG_WARNING_LVL)
         << "[FastrakStandalone] Not able to read status from tracker. Attempting reset..."
         << std::endl << vprDEBUG_FLUSH;

      //Try resetting the system. Make sure to give it enough time to cycle
      mSerialPort->write("\31", 1, bytes_written);
      vpr::System::msleep(15000);//Sleep for 15 seconds

      //Added this to help check on the status of the tracker at startup
      if ( ! readStatus() )
      {
         vprDEBUG(vprDBG_ERROR, vprDBG_WARNING_LVL)
            << "[FastrakStandalone] Not able to read status from tracker "
            << std::endl << vprDEBUG_FLUSH;
         return false;
      }
   }

   mSerialPort->write("uf", 2, bytes_written); // unites: cm, mode binaire

   //Set the stylus button mode. NOTE: The station number is ignored by the
   //tracker. No need to set it to anything but one.
   mSerialPort->write("e1,", 3, bytes_written);
   mSerialPort->write(&mConf.button,1, bytes_written);
   mSerialPort->write("\r",1, bytes_written);

   for ( unsigned int station = 0; station < NSTATION; ++station )
   {
      struct perstation *psp = &(mConf.perstation[station]);
      int len;
      c = '1' + station;

      mSerialPort->write("l",1, bytes_written);
      mSerialPort->write(&c, 1, bytes_written);

      if ( mConf.found&(1<<(REC+station)) )
      {
         if ( psp->rec == 0 )
         {
            mSerialPort->write(",0\r", 3, bytes_written);
         }
         else
         {
            mSerialPort->write(",1\rO", 4, bytes_written);
            mSerialPort->write(&c, 1, bytes_written);

            if ( psp->rec & (1<<Pos) )
            {
               mSerialPort->write(",2", 2, bytes_written);
            }
            if ( psp->rec & (1<<Ang) )
            {
               mSerialPort->write(",4", 2, bytes_written);
            }
            if ( psp->rec & (1<<Quat) )
            {
               mSerialPort->write(",11", 3, bytes_written);
            }
            if ( psp->rec & (1<<But) )
            {
               mSerialPort->write(",16", 3, bytes_written);
            }
            mSerialPort->write(",1\r", 3, bytes_written);
         }
      }

      if ( mConf.found & (1<<(TIP+station)) )
      {
#if defined(_MSC_VER) && _MSC_VER >= 1400
         len = _snprintf_s(buf, sizeof(buf),
#elif defined(_MSC_VER)
         len = _snprintf(buf, sizeof(buf),
#elif defined(HAVE_SNPRINTF)
         len = snprintf(buf, sizeof(buf),
#else
         len = sprintf(buf,
#endif
                       "N%c,%.2f,%.2f,%.2f\r", c, psp->tip[0], psp->tip[1],
                       psp->tip[2]);
         mSerialPort->write(buf, len, bytes_written);
      }

      if ( mConf.found & (1<<(INC+station)) )
      {
#if defined(_MSC_VER) && _MSC_VER >= 1400
         len = _snprintf_s(buf, sizeof(buf),
#elif defined(_MSC_VER)
         len = _snprintf(buf, sizeof(buf),
#elif defined(HAVE_SNPRINTF)
         len = snprintf(buf, sizeof(buf),
#else
         len = sprintf(buf,
#endif
                       "I%c,%.2f\r", c, psp->inc);
         mSerialPort->write(buf, len, bytes_written);
      }

      if ( mConf.found & (1<<(HEM+station)) )
      {
#if defined(_MSC_VER) && _MSC_VER >= 1400
         len = _snprintf_s(buf, sizeof(buf),
#elif defined(_MSC_VER)
         len = _snprintf(buf, sizeof(buf),
#elif defined(HAVE_SNPRINTF)
         len = snprintf(buf, sizeof(buf),
#else
         len = sprintf(buf,
#endif
                       "H%c,%.2f,%.2f,%.2f\r", c, psp->hem[0], psp->hem[1],
                       psp->hem[2]);
         mSerialPort->write(buf, len, bytes_written);
      }

      if ( mConf.found & (1<<(TMF+station)) )
      {
#if defined(_MSC_VER) && _MSC_VER >= 1400
         len = _snprintf_s(buf, sizeof(buf),
#elif defined(_MSC_VER)
         len = _snprintf(buf, sizeof(buf),
#elif defined(HAVE_SNPRINTF)
         len = snprintf(buf, sizeof(buf),
#else
         len = sprintf(buf,
#endif
                       "r%c,%.2f,%.2f,%.2f\r", c, psp->tmf[0], psp->tmf[1],
                       psp->tmf[2]);
         mSerialPort->write(buf, len, bytes_written);
      }

      if ( mConf.found & (1<<(ARF+station)) )
      {
#if defined(_MSC_VER) && _MSC_VER >= 1400
         len = _snprintf_s(buf, sizeof(buf),
#elif defined(_MSC_VER)
         len = _snprintf(buf, sizeof(buf),
#elif defined(HAVE_SNPRINTF)
         len = snprintf(buf, sizeof(buf),
#else
         len = sprintf(buf,
#endif
                       "A%c,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\r",
                       c, psp->arf[0], psp->arf[1], psp->arf[2], psp->arf[3],
                       psp->arf[4], psp->arf[5], psp->arf[6], psp->arf[7],
                       psp->arf[8]);
         mSerialPort->write(buf, len, bytes_written);
      }
   }

   /*
   if (mConf.cont == 'C')
   {
      ReadPid = sproc(readloop, PR_SALL);
      if (ReadPid == -1)
      {
         perror("Can't creat read process");
         exit(1);
      }
    }
    */
   mSerialPort->write(&mConf.cont, 1, bytes_written);

   if (mConf.cont == 'C')
   {
      checkchild();
   }

   return true;
}

void FastrakStandalone::checkchild()
{
   // XXX: This is commented out because I do not know how useful it is.
/*
   if ( NULL != mReadThread )
   {
      if ( waitpid(mReadPid, 0, WNOHANG) == 0 )
      {
         return;
      }
      else
      {
         mReadThread->kill(9);
      }
   }
   mReadThread = new vpr::Thread(boost::bind(&FastrakStandalone::readloop,
                                             this));
*/
   mExitFlag = false;
   if ( NULL == mReadThread )
   {
      try
      {
         mReadThread =
            new vpr::Thread(boost::bind(&FastrakStandalone::readloop, this));
      }
      catch (vpr::Exception& ex)
      {
         vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
            << clrOutBOLD(clrRED, "ERROR")
            << ": Failed to spawn read thread for Fastrak standalone driver!\n"
            << vprDEBUG_FLUSH;
         vprDEBUG_NEXT(vprDBG_ALL, vprDBG_CRITICAL_LVL)
            << ex.what() << std::endl << vprDEBUG_FLUSH;
      }
   }
}

void FastrakStandalone::getTrackerBuf()
{
   if ( mConf.button == '0' )
   {
      vpr::Uint32 bytes_written;
      mSerialPort->write("P", 1, bytes_written);
   }
   Read(mConf.len);
}

void FastrakStandalone::getTrackerInfo(struct perstation* psp, unsigned char c)
{
   unsigned char *cp;
   retry:
   if ( mConf.cont != 'C')
   {
      getTrackerBuf();
   }

   cp = (unsigned char *)mTrackerBuf + psp->begin;
   if ( cp[0] != '0' || cp[1] != c )
   {
      if ( mConf.cont != 'C' )
      {
         mSerialPort->flushQueue(vpr::SerialTypes::INPUT_QUEUE);
      }
      else
      {
         mDoFlush = true;
         while ( mDoFlush )
         {
            vpr::Uint32 sleep_time(10000000/mConf.baud);
            vpr::System::usleep(sleep_time);
         }
      }

      goto retry;
   }
}

static float littlendian(unsigned char *src)
{
   int tempNum = (src[3]<<24)|(src[2]<<16)|(src[1]<<8)|src[0];
   float tempFloat = *(float *)(&tempNum);
   return tempFloat;
}

int FastrakStandalone::getCoords(unsigned int stations, float *vecXYZ,
                                  float *vecAER)
{
   unsigned char *cp;
   int i, station, button = 0;
   struct perstation *psp;
   unsigned char c = '1';
   for ( station = 0; station < NSTATION; ++station, ++c )
   {
      if ( (stations&(1<<station)) == 0 ) continue;
      psp  = &mConf.perstation[station];
      if ( psp->rec )
      {
         getTrackerInfo(psp, c);
         if ( psp->rec & (1<<Pos) )
         {
            cp = (unsigned char *)mTrackerBuf + psp->posoff;
            for ( i = 0; i < 3; ++i )
            {
               *(vecXYZ+i) = littlendian(cp);
               cp += 4;
            }
         }
         else
         {
            memset((void *)vecXYZ, 0, 3*sizeof (float));
         }

         vecXYZ += 3;
         if ( psp->rec & (1<<Ang) )
         {
            cp = (unsigned char *)mTrackerBuf + psp->angoff;
            for ( i = 0; i < 3; ++i )
            {
               *(vecAER+i) = littlendian(cp);
               cp += 4;
            }
         }
         else
         {
            memset((void *)vecAER, 0, 3*sizeof (float));
         }

         vecAER += 3;
         if ( psp->rec & (1<<But) )
         {
            button = mTrackerBuf[psp->butoff] - '0';
         }
      }
   }
   return button;
}

void FastrakStandalone::getNewCoords(unsigned int station, float *vecXYZ, float *vecAER)
{
   unsigned char *cp;
   int i;
   struct perstation *psp;
   unsigned char c;


   if ( (unsigned)(--station) >= 4 ) return;
   c = '1'+station;
   psp  = &mConf.perstation[station];
   if ( (psp->rec & ((1<<Pos)|(1<<Ang))) == 0 ) return;
   getTrackerInfo(psp, c);
   if ( psp->rec & (1<<Pos) )
   {
      cp = (unsigned char *)mTrackerBuf + psp->posoff;
      for ( i = 0; i < 3; ++i )
      {
         *(vecXYZ+i) = littlendian(cp);
         cp += 4;
      }
   }
   if ( psp->rec & (1<<Ang) )
   {
      cp = (unsigned char *)mTrackerBuf + psp->angoff;
      for ( i = 0; i < 3; ++i )
      {
         *(vecAER+i) = littlendian(cp);
         cp += 4;
      }
   }
}

int FastrakStandalone::getNewButtonStatus(unsigned int station)
{
   struct perstation *psp;
   char c;

   if ( (unsigned)(--station) >= 4 ) return 0;
   c = '1'+station;
   psp = &mConf.perstation[station];
   if ( (psp->rec & (1 << But)) == 0 ) return 0;
   getTrackerInfo(psp, c);
   return mTrackerBuf[psp->butoff] - '0';
}

#ifdef TEST
main(int argc, char **argv)
{
   float xyz[XYZ*4], aer[XYZ*4];
   //    int station = 1;
   int but;

   trackerInit(argv[1]);
   //    if (argc > 2) station = argv[2][0] - '0';

   for ( ;; )
   {
      but = getCoords(1, xyz, aer);
      printf("%7.2f %7.2f %7.2f %7.2f %7.2f %7.2f %d\n",
             xyz[0], xyz[1], xyz[2], aer[0], aer[1], aer[2], but);
      but = getCoords(2, xyz, aer);
      printf("%7.2f %7.2f %7.2f %7.2f %7.2f %7.2f %d\n",
             xyz[0], xyz[1], xyz[2], aer[0], aer[1], aer[2], but);
      but = getCoords(4, xyz, aer);
      printf("%7.2f %7.2f %7.2f %7.2f %7.2f %7.2f %d\n",
             xyz[0], xyz[1], xyz[2], aer[0], aer[1], aer[2], but);
      but = getCoords(8, xyz, aer);
      printf("%7.2f %7.2f %7.2f %7.2f %7.2f %7.2f %d\n",
             xyz[0], xyz[1], xyz[2], aer[0], aer[1], aer[2], but);
      fflush(stdout);
   }
}
#endif
