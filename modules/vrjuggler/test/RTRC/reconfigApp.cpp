#include <reconfigApp.h>

void reconfigApp::init()
{

   mWand.init("VJWand") ;
   mHead.init("VJHead") ;
   mButton0.init("VJButton0") ;
   mButton1.init("VJButton1") ;
   mButton2.init("VJButton2") ;
   mButton3.init("VJButton3") ;
   mButton4.init("VJButton4") ;
   mButton5.init("VJButton5") ;

   mFrameCount = 0;
   mStartTime = 1000;
   mWaitTime = 100;
   mTestState = 0;
   mTesting = false;
   mFinished = false;

   mNewChunkDB = NULL;
}

void reconfigApp::contextInit()
{
   initGLState();
}

//Do some pre draw calculations
void reconfigApp::preFrame()
{
   if (mFinished) return;

   //Don't start tests until a certain frame number
   if (mStartTime > 1) { mStartTime-- ; return; }


   bool status = false;

   //If we are not currently doing any testing, start a new test state
   if (!mTesting) 
   {
      mTesting = true;

      //Switch on the test state
      switch (mTestState)
      {
         case  0:  status =       addGFXWindow_exec();         break;

         case  1:  status =       removeGFXWindow_exec();      break;

         case  2:  status =       readdGFXWindow_exec();       break;

         case  3:  status =       resizeGFXWindow_exec();      break;

         case  4:  status =       moveGFXWindow_exec();        break;

         case  5:  status =       addViewport_exec();          break;

         case  6:  status =       removeViewport_exec();       break;

         case  7:  status =       resizeViewport_exec();       break;

         case  8:  status =       moveViewport_exec();         break;

         case  9:  status =       enableStereoSurface_exec();  break;

         case 10:  status =       disableStereoSurface_exec(); break;

         case 11:  status =       removeKeyboardWin_exec();    break;

         case 12:  status =       readdKeyboardWin_exec();     break;

         case 13:  status =       addSimPos_exec();            break;

         case 14:  status =       removeSimPos_exec();         break;

         case 15:  status =       readdSimPos_exec();          break;

         case 16:  status =       repointProxy_exec();         break;

         case 17:  status =       reconfigSimPos_exec();       break;

         case 18:  status =       reconfigSimDigital_exec();   break;

         case 19:  status =       reconfigSimAnalog_exec();    break;

         case 20:  status =       addSimDigital_exec();        break;

         case 21:  status =       removeSimDigital_exec();     break;

         case 22:  status =       readdSimDigital_exec();      break;

         case 23:  status =       addSimAnalog_exec();         break;

         case 24:  status =       removeSimAnalog_exec();      break;

         case 25:  status =       readdSimAnalog_exec();       break;

         case 26:  status =       addPosProxy_exec();          break;

         case 27:  status =       reconfigPosProxy_exec();     break;

         case 28:  status =       removePosProxy_exec();       break;

         case 29:  status =       addAnalogProxy_exec();       break;

         case 30:  status =       reconfigAnalogProxy_exec();  break;

         case 31:  status =       removeAnalogProxy_exec();    break;

         case 32:  status =       addDigitalProxy_exec();      break;

         case 33:  status =       reconfigDigitalProxy_exec(); break;

         case 34:  status =       removeDigitalProxy_exec();   break;

         case 35:  status =       addKeyboardProxy_exec();     break;

         case 36:  status =       reconfigKeyboardProxy_exec();break;

         case 37:  status =       removeKeyboardProxy_exec();  break;

         case 38:  status = true; 
                   mFinished = true; 
                   std::cout << "\n\n[Test battery completed]\n\n" << std::flush; 
                   mKernel->stop();
                   break;

         default: status = true; break;
      }

      if (!status)
      {
         std::cout << "WARNING: Problem executing test. Subsequent results may be inaccurate\n\n" << std::flush;
      }

   }

   //If we have waited enough time after executing a test...
   //Then we need to run the 
   if (checkTime())
   {

      switch ( mTestState )
      {
         case  0:  status =       addGFXWindow_check();         break;

         case  1:  status =       removeGFXWindow_check();      break;

         case  2:  status =       readdGFXWindow_check();       break;

         case  3:  status =       resizeGFXWindow_check();      break;

         case  4:  status =       moveGFXWindow_check();        break;

         case  5:  status =       addViewport_check();          break;

         case  6:  status =       removeViewport_check();       break;

         case  7:  status =       resizeViewport_check();       break;

         case  8:  status =       moveViewport_check();         break;

         case  9:  status =       enableStereoSurface_check();  break;

         case 10:  status =       disableStereoSurface_check(); break;

         case 11:  status =       removeKeyboardWin_check();    break;

         case 12:  status =       readdKeyboardWin_check();     break;

         case 13:  status =       addSimPos_check();            break;

         case 14:  status =       removeSimPos_check();         break;

         case 15:  status =       readdSimPos_check();          break;

         case 16:  status =       repointProxy_check();         break;

         case 17:  status =       reconfigSimPos_check();       break;

         case 18:  status =       reconfigSimDigital_check();   break;

         case 19:  status =       reconfigSimAnalog_check();    break;

         case 20:  status =       addSimDigital_check();        break;

         case 21:  status =       removeSimDigital_check();     break;

         case 22:  status =       readdSimDigital_check();      break;

         case 23:  status =       addSimAnalog_check();         break;

         case 24:  status =       removeSimAnalog_check();      break;

         case 25:  status =       readdSimAnalog_check();       break;

         case 26:  status =       addPosProxy_check();          break;

         case 27:  status =       reconfigPosProxy_check();     break;

         case 28:  status =       removePosProxy_check();       break;

         case 29:  status =       addAnalogProxy_check();       break;

         case 30:  status =       reconfigAnalogProxy_check();  break;

         case 31:  status =       removeAnalogProxy_check();    break;

         case 32:  status =       addDigitalProxy_check();      break;

         case 33:  status =       reconfigDigitalProxy_check(); break;

         case 34:  status =       removeDigitalProxy_check();   break;

         case 35:  status =       addKeyboardProxy_check();     break;

         case 36:  status =       reconfigKeyboardProxy_check();break;

         case 37:  status =       removeKeyboardProxy_check();  break;

         default: status = true; break;

      }

      mTestState++;      //Next test state
      mTesting = false;  //No longer in the middle of a test

      if (status)
         std::cout << "[TEST PASSED]\n\n" << std::flush;
      else
         std::cout << "[ *** TEST FAILED *** ]\n\n" << std::flush;

   }

}

void reconfigApp::postFrame()
{

}

void reconfigApp::bufferPreDraw()
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void reconfigApp::draw()
{

   initGLState();

   glColor3f( 0.3, 0.05, 0.6 );
   glBegin( GL_POLYGON );
      glVertex3f( 5.0, 0.0, -5.0 );
      glVertex3f( -5.0, 0.0, -5.0 );
      glVertex3f( 0.0, 10.0, -5.0 );
   glEnd();
}

void reconfigApp::initGLState()
{
   GLfloat light0_ambient[] = { .2,  .2,  .2,  1.0};
   GLfloat light0_diffuse[] = { 0.8,  0.8,  0.8,  1.0};
   GLfloat light0_specular[] = { 1.0,  1.0,  1.0,  1.0};
   GLfloat light0_position[] = {0.0, 10,0, 0.0, 1.0};

   glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR,  light0_specular);
   glLightfv(GL_LIGHT0, GL_POSITION,  light0_position);

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);
   glShadeModel(GL_SMOOTH);

   glMatrixMode(GL_MODELVIEW);
}



/********************************************************************
UTILITY FUNCTIONS
********************************************************************/
bool reconfigApp::addChunkFile( std::string filename )
{
   //Attempt to load a new config chunk
   if (mNewChunkDB != NULL) delete mNewChunkDB;

   mNewChunkDB = new jccl::ConfigChunkDB;

   if (mNewChunkDB->load( std::string( filename )))
   {
      jccl::ConfigManager::instance()->addPendingAdds( mNewChunkDB );
      return true;
   }
   else
   {
      std::cout << "\tError: Failed to load config file: " << filename << std::endl << std::flush;
      delete mNewChunkDB;  
      mNewChunkDB = NULL;
      return false;
   }
}

bool reconfigApp::removeChunkFile( std::string filename )
{
   //Attempt to load a new config chunk
   if (mNewChunkDB != NULL) delete mNewChunkDB;

   mNewChunkDB = new jccl::ConfigChunkDB;

   if (mNewChunkDB->load( std::string( filename )))
   {
      jccl::ConfigManager::instance()->addPendingRemoves( mNewChunkDB );
      return true;
   }
   else
   {
      std::cout << "\tError: Failed to load config file: " << filename << std::endl << std::flush;
      delete mNewChunkDB;  
      mNewChunkDB = NULL;
      return false;
   }
}

bool reconfigApp::swapChunkFiles( std::string remove_file, std::string add_file )
{
   if (!removeChunkFile( remove_file ))
   {
      std::cout << "\tError: Could not remove config file " << remove_file << "\n" << std::flush;
      return false;
   }

   if (!addChunkFile( add_file ))
   {
      std::cout << "\tError: Could not add config file " << add_file << "\n" << std::flush;
      return false;
   }

   return true;

}

bool reconfigApp::removeRecentChunkDB()
{
   if (mNewChunkDB != NULL)
   {
      jccl::ConfigManager::instance()->addPendingRemoves( mNewChunkDB );
      return true;
   }
   else
   {
      std::cout << "\tError: Cannot remove a NULL chunk db\n" << std::flush;
      return false;
   }
}

bool reconfigApp::checkTime()
{
   if (mFrameCount >= mWaitTime)
   {
      mFrameCount = 0;
      return true;
   }
   else
   {
      mFrameCount++;
      return false;
   }
}

bool reconfigApp::verifyProxy( std::string proxyName, std::string deviceName )
{
   //Try to get the new proxy and check its values
   gadget::Proxy* proxy = gadget::InputManager::instance()->getProxy( proxyName );

   if (proxy == NULL)
   {
      std::cout << "\tError: Could not find the proxy\n" << std::flush;
      return false;
   }

   if (proxy->isStupified())
   {
      std::cout << "\tError: Proxy is stupified\n" << std::flush;
      return false;
   }

   gadget::Input* inputDevice = proxy->getProxiedInputDevice();

   if (inputDevice == NULL)
   {
      std::cout << "\tError: Proxy does not point at a valid device\n" << std::flush;
      return false;
   }

   if (inputDevice->getInstanceName() != deviceName )
   {
      std::cout << "\tError: Input device has wrong name: " << inputDevice->getInstanceName() << "   It should be " << deviceName << "\n" << std::flush;
      return false;
   }

   return true;

}

vrj::Display* reconfigApp::getDisplay( std::string name )
{
   //Search the display manager for the display by name
   std::vector<vrj::Display*>::iterator iter;
   std::vector<vrj::Display*> allDisplays = vrj::DisplayManager::instance()->getAllDisplays();

   for (iter = allDisplays.begin(); iter != allDisplays.end(); iter++)
   {
      if (name == (*iter)->getName())
      {
         return *iter;
      }
   }

   return NULL;
}

bool reconfigApp::verifyDisplayProps(  vrj::Display* disp,
                                       std::string name,
                                       int x_origin,
                                       int y_origin,
                                       int x_size,
                                       int y_size,
                                       int pipe_num,
                                       bool stereo,
                                       bool border,
                                       bool active  )
{
   bool ok = true;

   if (disp->getName() != name)
   {
      ok = false;
   }

   int xo, yo, xs, ys;   
   disp->getOriginAndSize(xo, yo, xs, ys);

   if (xo != x_origin)
   {
      ok = false;      
   }

   if (yo != y_origin)
   {
      ok = false;      
   }

   if (xs != x_size)
   {
      ok = false;      
   }

   if (ys != y_size)
   {
      ok = false;      
   }

   if (disp->getPipe() != pipe_num)
   {
      ok = false;      
   }

   if (disp->inStereo() != stereo)
   {
      ok = false;        
   }

   if (disp->shouldDrawBorder() != border)
   {
      ok = false;        
   }

   if (disp->isActive() != active)
   {
      ok = false;        
   }

   return ok;
}

bool reconfigApp::verifyDisplayFile( std::string filename )
{
   //Assume that the file given has the displayWindow chunk in it
   //Load up the given file 
   jccl::ConfigChunkDB fileDB ; fileDB.load( filename );
   std::vector<jccl::ConfigChunkPtr> windowChunks;
   fileDB.getByType( "displayWindow", windowChunks );

   //Verify EACH display in the file
   for (int i=0; i < windowChunks.size(); i++)
   {
      //Get its attributes
      std::string displayName = windowChunks[i]->getName();

      //Get the display with the same name from the DisplayManager
      //and make sure it exists first
      vrj::Display* display = getDisplay( displayName );
      if (display == NULL)
      {
         std::cout << "\tError: display chunk named " << displayName << " is not in the display manager\n" << std::flush;
         return false;
      }

      //Get origin values
      if (windowChunks[i]->getNum( "origin" ) < 2 )
      {
         std::cout << "\tError: display chunk named " << displayName << " doesn't have origin properties\n" << std::flush;
         return false;
      }
      int x_origin = windowChunks[i]->getProperty<int>("origin", 0);
      int y_origin = windowChunks[i]->getProperty<int>("origin", 1);

      //Get size values
      if (windowChunks[i]->getNum( "size" ) < 2 )
      {
         std::cout << "\tError: display chunk named " << displayName << " doesn't have size properties\n" << std::flush;
         return false;
      }
      int x_size = windowChunks[i]->getProperty<int>("size", 0);
      int y_size = windowChunks[i]->getProperty<int>("size", 1);


      //Get pipe number
      if (windowChunks[i]->getNum( "pipe" ) < 1 )
      {
         std::cout << "\tError: display chunk named " << displayName << " doesn't have pipe property\n" << std::flush;
         return false;
      }
      int pipe_num = windowChunks[i]->getProperty<int>( "pipe" );

      //Get stereo value
      if (windowChunks[i]->getNum( "stereo" ) < 1 )
      {
         std::cout << "\tError: display chunk named " << displayName << " doesn't have stereo property\n" << std::flush;
         return false;
      }
      bool stereo = (windowChunks[i]->getProperty<int>( "stereo" ) == 1 ? true : false );

      //Get border value
      if (windowChunks[i]->getNum( "border" ) < 1 )
      {
         std::cout << "\tError: display chunk named " << displayName << " doesn't have border property\n" << std::flush;
         return false;
      }
      bool border = (windowChunks[i]->getProperty<int>( "border" ) == 1 ? true : false );

      //Get active value
      if (windowChunks[i]->getNum( "active" ) < 1 )
      {
         std::cout << "\tError: display chunk named " << displayName << " doesn't have active property\n" << std::flush;
         return false;
      }
      bool active = (windowChunks[i]->getProperty<int>( "active" ) == 1 ? true : false );


      //Run a verification check (verifyDisplayProps)
      return verifyDisplayProps( display, displayName, x_origin, y_origin, x_size, y_size, pipe_num, stereo, border, active );
   }

   return true;
}

/********************************************************************
TEST SUITE FUNCTIONS
********************************************************************/

//  - Adding gfx window     
bool reconfigApp::addGFXWindow_exec()
{
   std::cout << "Beginning test for adding a graphics window...\n" << std::flush;
   return addChunkFile( "./Chunks/sim.extradisplay.01.config" );
}

bool reconfigApp::addGFXWindow_check()
{
   return verifyDisplayFile( "./Chunks/sim.extradisplay.01.config" );
}


//  - Remove gfx window     
bool reconfigApp::removeGFXWindow_exec()
{
   std::cout << "Beginning test for removing a graphics window...\n" << std::flush;
   return removeChunkFile( "./Chunks/sim.extradisplay.01.config" );
}

bool reconfigApp::removeGFXWindow_check()
{

   //Load up the given file 
   jccl::ConfigChunkDB fileDB ; fileDB.load( "./Chunks/sim.extradisplay.01.config" );
   std::vector<jccl::ConfigChunkPtr> windowChunks;
   fileDB.getByType( "displayWindow", windowChunks );

   if (windowChunks.size() != 1)
   {
      std::cout << "\tError: the display config chunk file contains " << windowChunks.size() << " displays (should be 1)\n" << std::flush;
      return false;
   }   

   vrj::Display* display = getDisplay(windowChunks[0]->getName());
   if (display != NULL)
   {
      std::cout << "\tError: there is still a display in the system named " << windowChunks[0]->getName() << "\n" << std::flush;
      return false;
   }   

   return true;

}

bool reconfigApp::readdGFXWindow_exec()
{
   std::cout << "Beginning test for readding a graphics window...\n" << std::flush;

   return (   addChunkFile( "./Chunks/sim.extradisplay.01.config" )
           && addChunkFile( "./Chunks/sim.extradisplay.02.config" ));
}

bool reconfigApp::readdGFXWindow_check()
{
   //Verify that both windows SimWindowX01 and SimWindowX02 have been added
   return verifyDisplayFile( "./Chunks/sim.extradisplay.01.config" ) &&
          verifyDisplayFile( "./Chunks/sim.extradisplay.02.config" );
}

bool reconfigApp::resizeGFXWindow_exec()
{
   std::cout << "Beginning test for resizing a graphics window...\n" << std::flush;

   return swapChunkFiles( "./Chunks/sim.extradisplay.02.config",
                          "./Chunks/sim.extradisplay.02.resize.config" );

}

bool reconfigApp::resizeGFXWindow_check()
{
   return verifyDisplayFile( "./Chunks/sim.extradisplay.02.resize.config" );
}

bool reconfigApp::moveGFXWindow_exec()
{
   std::cout << "Beginning test for moving a graphics window...\n" << std::flush;
  
   return swapChunkFiles( "./Chunks/sim.extradisplay.01.config",
                          "./Chunks/sim.extradisplay.01.move.config" );
}

bool reconfigApp::moveGFXWindow_check()
{
   return verifyDisplayFile( "./Chunks/sim.extradisplay.01.move.config" );
}

bool reconfigApp::addViewport_exec()
{
   std::cout << "Beginning test for adding a viewport to a display window...\n" << std::flush;

   return swapChunkFiles( "./Chunks/sim.extradisplay.02.resize.config",
                          "./Chunks/sim.extradisplay.02.twoviews.config" );
}

bool reconfigApp::addViewport_check()
{
   //Get the chunk
   vrj::Display* simDisplay = getDisplay( "SimWindowX02" );

   if (simDisplay == NULL)
   {
      std::cout << "\tError: Could not find SimWindowX02 to check its viewport\n" << std::flush;
      return false;
   }

   //Check the number of viewports
   if (simDisplay->getNumViewports() != 2)
   {
      std::cout << "\tError: SimWindowX02 doesn't have 2 viewports\n" << std::flush;
      return false;
   }

   return true;
}

bool reconfigApp::removeViewport_exec()
{

   std::cout << "Beginning test for removing a viewport from a graphics window...\n" << std::flush;

   return swapChunkFiles( "./Chunks/sim.extradisplay.02.twoviews.config",
                          "./Chunks/sim.extradisplay.02.oneview.config" );
}

bool reconfigApp::removeViewport_check()
{
   //Get the SimWindowX02
   vrj::Display* simDisplay = getDisplay( "SimWindowX02" );

   if (simDisplay == NULL)
   {
      std::cout << "\tError: Could not find SimWindowX02 to check its viewport\n" << std::flush;
      return false;
   }

   //Check the number of viewports
   if (simDisplay->getNumViewports() != 1)
   {
      std::cout << "\tError: SimWindowX02 doesn't have 1 viewport\n" << std::flush;
      return false;
   }

   return true;
}

bool reconfigApp::resizeViewport_exec()
{
   std::cout << "Beginning test for resizing a viewport...\n" << std::flush;

   return swapChunkFiles( "./Chunks/sim.extradisplay.02.oneview.config",
                          "./Chunks/sim.extradisplay.02.largerview.config" );
}

bool reconfigApp::resizeViewport_check()
{
   //Get the SimWindowX02
   vrj::Display* simDisplay = getDisplay( "SimWindowX02" );

   //If we could not find the window...we have a problem to start with
   if (simDisplay == NULL)
   {
      std::cout << "\tError: Could not find SimWindowX02 to check its viewport\n" << std::flush;
      return false;
   }

   //Make sure we have one viewport
   if (simDisplay->getNumViewports() != 1)
   {
      std::cout << "\tError: SimWindowX02 has an incorrect number of viewports\n" << std::flush;
      return false;   
   }

   vrj::Viewport* simViewport = simDisplay->getViewport(0);

   //Test its size
   float xo, yo, xs, ys;
   simViewport->getOriginAndSize(xo, yo, xs, ys);

   if ((xo != 0.0f) || (yo != 0.0f) || (xs != 0.9f) || (ys != 0.9f))
   {
      std::cout << "\tError: SimWindowX02's viewport has an incorrect origin and/or size\n" << std::flush;
      return false;   
   }

   return true;
}

bool reconfigApp::moveViewport_exec()
{
   std::cout << "Beginning test for moving a viewport...\n" << std::flush;

   return swapChunkFiles( "./Chunks/sim.extradisplay.02.largerview.config",
                          "./Chunks/sim.extradisplay.02.moveview.config" );
}

bool reconfigApp::moveViewport_check()
{
   //Get the SimWindowX02
   vrj::Display* simDisplay = getDisplay( "SimWindowX02" );

   //If we could not find the window...we have a problem to start with
   if (simDisplay == NULL)
   {
      std::cout << "\tError: Could not find SimWindowX02 to check its viewport\n" << std::flush;
      return false;
   }

   //Make sure we have one viewport
   if (simDisplay->getNumViewports() != 1)
   {
      std::cout << "\tError: SimWindowX02 has an incorrect number of viewports\n" << std::flush;
      return false;   
   }

   vrj::Viewport* simViewport = simDisplay->getViewport(0);

   //Test its size
   float xo, yo, xs, ys;
   simViewport->getOriginAndSize(xo, yo, xs, ys);

   if ((xo != 0.1f) || (yo != 0.1f) || (xs != 0.9f) || (ys != 0.9f))
   {
      std::cout << "\tError: SimWindowX02's viewport has an incorrect origin and/or size\n" << std::flush;
      return false;   
   }

   return true;

}

bool reconfigApp::enableStereoSurface_exec()
{
   std::cout << "Beginning test for enabling stereo on a surface display...\n" << std::flush;

   return        removeChunkFile( "./Chunks/sim.extradisplay.02.moveview.config" )
              && removeChunkFile( "./Chunks/sim.extradisplay.01.move.config" )
              && addChunkFile( "./Chunks/sim.surfacedisplay.01.stereo.config" );

}

bool reconfigApp::enableStereoSurface_check()
{

   //Get the SimSurfaceX01
   vrj::Display* surfaceDisplay = getDisplay( "SimSurfaceX01" );

   //If we could not find the window...we have a problem to start with
   if (surfaceDisplay == NULL)
   {
      std::cout << "\tError: Could not find SimSurfaceX01 to check its viewport\n" << std::flush;
      return false;
   }

   //Make sure we have one viewport
   if (surfaceDisplay->getNumViewports() != 1)
   {
      std::cout << "\tError: SimSurfaceX01 has an incorrect number of viewports\n" << std::flush;
      return false;   
   }

   vrj::Viewport* surfaceViewport = surfaceDisplay->getViewport(0);

   if (!surfaceViewport->inStereo())
   {
      std::cout << "\tError: SimSurfaceX01's viewport is not in stereo\n" << std::flush;
      return false;   
   }

   return true;

}

bool reconfigApp::disableStereoSurface_exec()
{
   std::cout << "Beginning test for disabling stereo on a surface display...\n" << std::flush;

   return swapChunkFiles( "./Chunks/sim.surfacedisplay.01.stereo.config",
                          "./Chunks/sim.surfacedisplay.01.mono.config" );
}

bool reconfigApp::disableStereoSurface_check()
{
   //Get the SimSurfaceX01
   vrj::Display* surfaceDisplay = getDisplay( "SimSurfaceX01" );

   //If we could not find the window...we have a problem to start with
   if (surfaceDisplay == NULL)
   {
      std::cout << "\tError: Could not find SimSurfaceX01 to check its viewport\n" << std::flush;
      return false;
   }

   //Make sure we have one viewport
   if (surfaceDisplay->getNumViewports() != 1)
   {
      std::cout << "\tError: SimSurfaceX01 has an incorrect number of viewports\n" << std::flush;
      return false;   
   }

   vrj::Viewport* surfaceViewport = surfaceDisplay->getViewport(0);

   if (surfaceViewport->inStereo())
   {
      std::cout << "\tError: SimSurfaceX01's viewport is in stereo\n" << std::flush;
      return false;   
   }

   return true;

}


bool reconfigApp::removeKeyboardWin_exec()
{
   std::cout << "Beginning test for removing a keyboard window...\n" << std::flush;

   //Note that we are assuming ./Chunks/startup/sim.wandkeyboardproxy.config has 
   //already been loaded

   return removeChunkFile( "./Chunks/startup/sim.wandkeyboard.config" );
}

bool reconfigApp::removeKeyboardWin_check()
{
   //First check that the keyboard device no longer exists
   jccl::ConfigChunkDB fileDB ; fileDB.load( "./Chunks/startup/sim.wandkeyboard.config" );
   std::vector<jccl::ConfigChunkPtr> fileChunks;
   fileDB.getByType( "Keyboard", fileChunks );

   std::string keyboardName = fileChunks[0]->getName();

   gadget::Keyboard* keyboard = (gadget::Keyboard*)gadget::InputManager::instance()->getDevice( keyboardName );

   if (keyboard != NULL)
   {
      std::cout << "\tError: the keyboard device named " << keyboardName << " still exists\n" << std::flush;
      return false;
   }

   //Check the wand keyboard proxy that is supposed to point to it is stupified
   jccl::ConfigChunkDB fileDB2 ; fileDB2.load( "./Chunks/startup/sim.wandkeyboardproxy.config" );
   fileChunks.clear();
   fileDB2.getByType( "KeyboardProxy", fileChunks );

   if (fileChunks.size() != 1)
   {
      std::cout << "\tError: there are " << fileChunks.size() << " keyboard proxies in the file (should be 1)\n" << std::flush;
      return false;
   }

   gadget::KeyboardProxy* keyboard_proxy = (gadget::KeyboardProxy*)gadget::InputManager::instance()->getProxy( fileChunks[0]->getName() );

   if (keyboard_proxy == NULL)
   {
      std::cout << "\tError: there is no keyboard proxy named " << fileChunks[0]->getName() << "\n" << std::flush;
      return false;
   }
 
   if (!keyboard_proxy->isStupified())
   {
      std::cout << "\tError: keyboard proxy named " << fileChunks[0]->getName() << " is not stupified\n" << std::flush;
      return false;

   }

   if (keyboard_proxy->getDeviceName() != keyboardName)
   {
      std::cout << "\tError: this keyboard proxy points at a keyboard named " << keyboard_proxy->getDeviceName() << "\n" << std::flush;
      return false;
   }

   return true;
}


bool reconfigApp::readdKeyboardWin_exec()
{
   std::cout << "Beginning test for readding a keyboard window...\n" << std::flush;
   return addChunkFile( "./Chunks/startup/sim.wandkeyboard.config" );
}

bool reconfigApp::readdKeyboardWin_check()
{
   //Check the wand keyboard proxy that is supposed to point to it

   //First check that the keyboard device exists again
   jccl::ConfigChunkDB fileDB ; fileDB.load( "./Chunks/startup/sim.wandkeyboard.config" );
   std::vector<jccl::ConfigChunkPtr> fileChunks;
   fileDB.getByType( "Keyboard", fileChunks );

   std::string keyboardName = fileChunks[0]->getName();

   gadget::Keyboard* keyboard = (gadget::Keyboard*)gadget::InputManager::instance()->getDevice( keyboardName );

   if (keyboard == NULL)
   {
      std::cout << "\tError: the keyboard device named " << keyboardName << " doesn't exist\n" << std::flush;
      return false;
   }

   //Check the wand keyboard proxy that is supposed to point to it is stupified
   jccl::ConfigChunkDB fileDB2 ; fileDB2.load( "./Chunks/startup/sim.wandkeyboardproxy.config" );
   fileChunks.clear();
   fileDB2.getByType( "KeyboardProxy", fileChunks );

   if (fileChunks.size() != 1)
   {
      std::cout << "\tError: there are " << fileChunks.size() << " keyboard proxies in the file (should be 1)\n" << std::flush;
      return false;
   }

   gadget::KeyboardProxy* keyboard_proxy = (gadget::KeyboardProxy*)gadget::InputManager::instance()->getProxy( fileChunks[0]->getName() );

   if (keyboard_proxy == NULL)
   {
      std::cout << "\tError: there is no keyboard proxy named " << fileChunks[0]->getName() << "\n" << std::flush;
      return false;
   }
 
   if (keyboard_proxy->isStupified())
   {
      std::cout << "\tError: keyboard proxy named " << fileChunks[0]->getName() << " is stupified\n" << std::flush;
      return false;

   }

   if (keyboard_proxy->getDeviceName() != keyboardName)
   {
      std::cout << "\tError: this keyboard proxy points at a keyboard named " << keyboard_proxy->getDeviceName() << "\n" << std::flush;
      return false;
   }

   //Make sure the pointers match up
   if (((gadget::Keyboard*)(keyboard_proxy->getProxiedInputDevice())) != keyboard)
   {
      std::cout << "\tError: pointers don't match up\n" << std::flush;
      return false;
   }

   return true;
}


bool reconfigApp::addSimPos_exec()
{
   std::cout << "Beginning test for adding a sim position device and pointing proxies at it...\n" << std::flush;
   return (  addChunkFile( "./Chunks/sim.positiondevice.config" ) 
          && addChunkFile( "./Chunks/sim.positiondeviceproxy.config" ));
}

bool reconfigApp::addSimPos_check()
{
   //Check that the sim pos device exists and that the proxy points at it
   return verifyProxy( "ExtraPositionProxy", "ExtraPositionDevice" );
}


bool reconfigApp::removeSimPos_exec()
{
   std::cout << "Beginning test for removing a sim position device and checking its proxies...\n" << std::flush;
   return removeChunkFile( "./Chunks/sim.positiondevice.config" );
}

bool reconfigApp::removeSimPos_check()
{

   //Look at the button proxy and see what it points at
   gadget::Proxy* proxy = gadget::InputManager::instance()->getProxy( "ExtraPositionProxy" );

   if (proxy == NULL)
   {
      std::cout << "\tError: Could not find the proxy\n" << std::flush;
      return false;
   }

   if (!proxy->isStupified())
   {
      std::cout << "\tError: Proxy is not stupified\n" << std::flush;
      return false;
   }
 
   return true;

}


bool reconfigApp::readdSimPos_exec()
{
   std::cout << "Beginning test for readding a sim position device and checking its proxies...\n" << std::flush;
   return addChunkFile( "./Chunks/sim.positiondevice.config" );
}

bool reconfigApp::readdSimPos_check()
{
   //Check that the sim pos device exists and that the proxy points at it
   return verifyProxy( "ExtraPositionProxy", "ExtraPositionDevice" );
}


bool reconfigApp::repointProxy_exec()
{
   std::cout << "Beginning test for repointing a proxy to something else...\n" << std::flush;

   return swapChunkFiles( "./Chunks/sim.positiondeviceproxy.config",
                          "./Chunks/sim.positiondeviceproxy.repoint.config" );
}

bool reconfigApp::repointProxy_check()
{
   //Load the repoint config file, get its device property, match that name
   //with the gadget::Proxy's instance name
   jccl::ConfigChunkDB fileDB ; fileDB.load( "./Chunks/sim.positiondeviceproxy.repoint.config" );
   std::vector<jccl::ConfigChunkPtr> fileChunks;
   fileDB.getByType( "PosProxy", fileChunks );


   if (fileChunks.size() != 1)
   {
      std::cout << "\tError: there are " << fileChunks.size() << " proxies in the config file (should be 1)\n" << std::flush;
      return false;
   }

   if (fileChunks[0]->getNum( "device" ) != 1)
   {
      std::cout << "\tError: there are " << fileChunks[0]->getNum("device") << " device properties in the config file (should be 1)\n" << std::flush;
      return false;
   }

   //Get the proxy's name from the file
   std::string proxyname = fileChunks[0]->getName();

   gadget::PositionProxy* proxy = (gadget::PositionProxy*)gadget::InputManager::instance()->getProxy( proxyname );

   if (proxy == NULL)
   {
      std::cout << "\tError: Could not find proxy named " << proxyname << " in the Input Manager\n" << std::flush;
      return false;
   }

   if (fileChunks[0]->getProperty<std::string>("device", 0) != proxy->getDeviceName())
   {
      std::cout << "\tError: the proxy points at device named " << proxy->getDeviceName() 
                << ", but should point at " << fileChunks[0]->getProperty<std::string>("device", 0) << "\n" << std::flush;
      return false;
   }

   return true;
}


bool reconfigApp::reconfigSimPos_exec()
{
   std::cout << "Beginning test for reconfiguring a sim position device...\n" << std::flush;

   return swapChunkFiles( "./Chunks/startup/sim.simheadpos.config", "./Chunks/sim.simheadpos.reconfig.config" );
}

bool reconfigApp::reconfigSimPos_check()
{
   //Get the sim position pointer
   gadget::SimPosition* device = (gadget::SimPosition*)gadget::InputManager::instance()->getDevice( "SimHeadPos" );

   if ( device == NULL )
   {
      std::cout << "\tError: Could not find the sim position device\n" << std::flush;
      return false;      
   }

   vrj::Matrix mat = *(device->getPositionData().getPosition());

   vrj::Vec3 pos = mat.getTrans();

   if ((pos[0] != 1.0) || (pos[1] != 2.0) || (pos[2] != 3.0))
   {
      std::cout << "\tError: Sim position device has incorrect initial position: " << pos[0] << "  " << pos[1] << "  " << pos[2] << "\n" << std::flush;
   }

   return true;
}


bool reconfigApp::reconfigSimDigital_exec()
{
   std::cout << "Beginning test for reconfiguring a sim digital device...\n" << std::flush;

   return swapChunkFiles( "./Chunks/startup/sim.wandbuttonsdigital02.config", 
                          "./Chunks/sim.wandbuttonsdigital02.reconfig.config" );
}

bool reconfigApp::reconfigSimDigital_check()
{

   //Get the sim digital pointer
   gadget::SimDigital* device = (gadget::SimDigital*)gadget::InputManager::instance()->getDevice( "SimWandButtons02" );

   if ( device == NULL )
   {
      std::cout << "\tError: Could not find the sim digital device\n" << std::flush;
      return false;      
   }

   //Get the vector of keymodpairs
   std::vector<gadget::SimInput::KeyModPair> keypairs = device->getKeys();

   //Load up the config file.
   jccl::ConfigChunkDB fileDB ; fileDB.load( "./Chunks/sim.wandbuttonsdigital02.reconfig.config" );
   std::vector<jccl::ConfigChunkPtr> fileChunks;
   fileDB.getByType( "SimDigital", fileChunks );

   bool key_status;
   //For each keymodpair that was defined in the device...
   for (int i=0; i < keypairs.size(); i++)
   {
      key_status = false;

      //Scan the sim digital config chunk to see if was defined there
      for ( int j=0; j < fileChunks[0]->getNum("keyPairs"); j++ )
      {
         jccl::ConfigChunkPtr key_mod_pair = fileChunks[0]->getProperty<jccl::ConfigChunkPtr>("keyPairs", j);

         //If they are the same..
         if (( keypairs[i].mModifier == key_mod_pair->getProperty<int>("modKey", 0))
            && keypairs[i].mKey == key_mod_pair->getProperty<int>("key", 0))
         {
            key_status = true;
            continue;
         }
      }  

      //If we have not found a key that matches...
      if (key_status == false)
      {
         std::cout << "\tError: One or more of the key pair definitions are incorrect\n" << std::flush;
         return false;
      }

   }

   return true;

}


bool reconfigApp::reconfigSimAnalog_exec()
{
   std::cout << "Beginning test for reconfiguring a sim analog device...\n" << std::flush;

   return swapChunkFiles( "./Chunks/startup/sim.analogdevice1.config",
                          "./Chunks/sim.analogdevice1.reconfig.config" );
}

bool reconfigApp::reconfigSimAnalog_check()
{

   //Get the sim analog pointer
   gadget::SimAnalog* device = (gadget::SimAnalog*)gadget::InputManager::instance()->getDevice( "AnalogDevice1" );

   if ( device == NULL )
   {
      std::cout << "\tError: Could not find the sim analog device\n" << std::flush;
      return false;      
   }

   //Get the vector of keymodpairs
   std::vector<gadget::SimInput::KeyModPair> keypairsup = device->getUpKeys();
   std::vector<gadget::SimInput::KeyModPair> keypairsdown = device->getDownKeys();

   //Load up the config file.
   jccl::ConfigChunkDB fileDB ; fileDB.load( "./Chunks/sim.analogdevice1.reconfig.config" );
   std::vector<jccl::ConfigChunkPtr> fileChunks;
   fileDB.getByType( "SimAnalog", fileChunks );

   bool key_status;

   //Scan the sim digital config chunk to see if was defined there
   for ( int i=0; i < fileChunks[0]->getNum("keyPairs"); i++ )
   {
      key_status = false;

      jccl::ConfigChunkPtr key_mod_pair = fileChunks[0]->getProperty<jccl::ConfigChunkPtr>("keyPairs", i);

      //Scan the up keys
      for (int j=0; j < keypairsup.size(); j++)
      {
         //If they are the same..
         if (( keypairsup[j].mModifier == key_mod_pair->getProperty<int>("modKey", 0))
            && keypairsup[j].mKey == key_mod_pair->getProperty<int>("key", 0))
         {
            key_status = true;
            continue;
         }
      }  

      //Scan the down keys
      for (int j=0; j < keypairsdown.size(); j++)
      {
         //If they are the same..
         if (( keypairsdown[j].mModifier == key_mod_pair->getProperty<int>("modKey", 0))
            && keypairsdown[j].mKey == key_mod_pair->getProperty<int>("key", 0))
         {
            key_status = true;
            continue;
         }
      }  

      //If we have not found a key that matches...
      if (key_status == false)
      {
         std::cout << "\tError: One or more of the key pair definitions are incorrect\n" << std::flush;
         return false;
      }
   }

   return true;
}


bool reconfigApp::addSimDigital_exec()
{
   std::cout << "Beginning test for adding a sim digital device and pointing proxies at it...\n" << std::flush;   

   return (  addChunkFile( "./Chunks/sim.digitaldevice.config" )
          && addChunkFile( "./Chunks/sim.digitalproxy.config"  ));
}

bool reconfigApp::addSimDigital_check()
{
   return verifyProxy( "DigitalProxy", "ExtraDigitalDevice" );
}


bool reconfigApp::removeSimDigital_exec()
{
   std::cout << "Beginning test for removing a sim digital device...\n" << std::flush;
   return removeChunkFile( "./Chunks/startup/sim.wandbuttonsdigital.config" );
}

bool reconfigApp::removeSimDigital_check()
{
   //Look at the button proxy and see what it points at
   gadget::Proxy* proxy = gadget::InputManager::instance()->getProxy( "Button0Proxy" );

   if (proxy == NULL)
   {
      std::cout << "\tError: Could not find the proxy\n" << std::flush;
      return false;
   }

   if (!proxy->isStupified())
   {
      std::cout << "\tError: Proxy is not stupified\n" << std::flush;
      return false;
   }
   
   return true;
}


bool reconfigApp::readdSimDigital_exec()
{
   std::cout << "Beginning test for readding a sim digital device and checking the proxies pointing at it...\n" << std::flush;
   
   return addChunkFile( "./Chunks/startup/sim.wandbuttonsdigital.config" );
}

bool reconfigApp::readdSimDigital_check()
{
   return (   verifyProxy( "Button0Proxy", "SimWandButtons" )
           && verifyProxy( "Button1Proxy", "SimWandButtons" )
           && verifyProxy( "Button2Proxy", "SimWandButtons" )
           && verifyProxy( "Button3Proxy", "SimWandButtons" )
           && verifyProxy( "Button4Proxy", "SimWandButtons" )
           && verifyProxy( "Button5Proxy", "SimWandButtons" ));
}

bool reconfigApp::addSimAnalog_exec()
{
   std::cout << "Beginning test for adding a sim analog device and pointing proxies at it...\n" << std::flush;   

   return (  addChunkFile( "./Chunks/sim.extraanalogdevice.config" )
          && addChunkFile( "./Chunks/sim.extraanalogproxy.config"  ));
}

bool reconfigApp::addSimAnalog_check()
{
   return verifyProxy( "ExtraAnalogProxy", "ExtraAnalogDevice" );
}


bool reconfigApp::removeSimAnalog_exec()
{
   std::cout << "Beginning test for removing a sim analog device and checking the proxies that point at it...\n" << std::flush;
   return removeChunkFile( "./Chunks/sim.extraanalogdevice.config" );
}

bool reconfigApp::removeSimAnalog_check()
{
   //Look at the button proxy and see what it points at
   gadget::Proxy* proxy = gadget::InputManager::instance()->getProxy( "ExtraAnalogProxy" );

   if (proxy == NULL)
   {
      std::cout << "\tError: Could not find the proxy\n" << std::flush;
      return false;
   }

   if (!proxy->isStupified())
   {
      std::cout << "\tError: Proxy is not stupified\n" << std::flush;
      return false;
   }
   
   return true;
}


bool reconfigApp::readdSimAnalog_exec()
{
   std::cout << "Beginning test for readding a sim analog device and checking the old proxies...\n" << std::flush;
   return addChunkFile( "./Chunks/sim.extraanalogdevice.config" ) ;
}

bool reconfigApp::readdSimAnalog_check()
{
   return verifyProxy( "ExtraAnalogProxy", "ExtraAnalogDevice" );
}

bool reconfigApp::addAnalogProxy_exec()
{
   std::cout << "Beginning test for adding an analog proxy...\n" << std::flush;
   return addChunkFile( "./Chunks/sim.analogproxy01.config" ) ;
}

bool reconfigApp::addAnalogProxy_check()
{
   return verifyProxy( "AnalogProxy01", "AnalogDevice1" );
}


bool reconfigApp::reconfigAnalogProxy_exec()
{
   std::cout << "Beginning test for reconfiguring an analog proxy...\n" << std::flush;
   return swapChunkFiles( "./Chunks/sim.analogproxy01.config", "./Chunks/sim.analogproxy01.reconfig.config" );
}

bool reconfigApp::reconfigAnalogProxy_check()
{
   return verifyProxy( "AnalogProxy01", "AnalogDevice2" );
}


bool reconfigApp::removeAnalogProxy_exec()
{
   std::cout << "Beginning test for removing an analog proxy...\n" << std::flush;
   return removeChunkFile( "./Chunks/sim.analogproxy01.reconfig.config" );
}

bool reconfigApp::removeAnalogProxy_check()
{

  //Try to get the new proxy and check its values

   if (gadget::InputManager::instance()->getProxy( "AnalogProxy01" ) != NULL)
   {
      std::cout << "\tError: AnalogProxy01 still exists\n" << std::flush;
      return false;
   }

   return true;
}


bool reconfigApp::addPosProxy_exec()
{
   std::cout << "Beginning test for adding a sim digital device...\n" << std::flush;
   return addChunkFile( "./Chunks/sim.simcam1proxy02.config" );
}

bool reconfigApp::addPosProxy_check()
{
   return verifyProxy( "SimCam1 Proxy02", "SimCamera1" );
}


bool reconfigApp::reconfigPosProxy_exec()
{
   std::cout << "Beginning test for reconfiguring a position proxy...\n" << std::flush;
   return swapChunkFiles( "./Chunks/sim.simcam1proxy02.config", "./Chunks/sim.simcam1proxy02.reconfig.config");
}

bool reconfigApp::reconfigPosProxy_check()
{
   return verifyProxy( "SimCam1 Proxy02", "SimCamera2") ;
}


bool reconfigApp::removePosProxy_exec()
{
   std::cout << "Beginning test for removing a position proxy...\n" << std::flush;
   return removeChunkFile( "./Chunks/sim.simcam1proxy02.reconfig.config" );
}

bool reconfigApp::removePosProxy_check()
{
  //Try to get the new proxy and check its values

   if (gadget::InputManager::instance()->getProxy( "SimCam1 Proxy02" ) != NULL)
   {
      std::cout << "\tError: SimCam1 Proxy02 still exists\n" << std::flush;
      return false;
   }

   return true;
}


bool reconfigApp::addDigitalProxy_exec()
{
   std::cout << "Beginning test for adding a digital proxy...\n" << std::flush;
   return addChunkFile( "./Chunks/sim.button0proxy02.config" );
}

bool reconfigApp::addDigitalProxy_check()
{
   return verifyProxy( "Button0Proxy02", "SimWandButtons" );
}


bool reconfigApp::reconfigDigitalProxy_exec()
{
   std::cout << "Beginning test for reconfiguring a digital proxy...\n" << std::flush;
   return swapChunkFiles( "./Chunks/sim.button0proxy02.config", "./Chunks/sim.button0proxy02.reconfig.config");
}

bool reconfigApp::reconfigDigitalProxy_check()
{
   return verifyProxy( "Button0Proxy02", "SimWandButtons02" );
}


bool reconfigApp::removeDigitalProxy_exec()
{
   std::cout << "Beginning test for removing a digital proxy...\n" << std::flush;
   return removeChunkFile( "./Chunks/sim.button0proxy02.reconfig.config" );
}

bool reconfigApp::removeDigitalProxy_check()
{
  //Try to get the new proxy and check its values

   if (gadget::InputManager::instance()->getProxy( "Button0Proxy02" ) != NULL)
   {
      std::cout << "\tError: Button0 proxy 02 still exists\n" << std::flush;
      return false;
   }

   return true;
}


bool reconfigApp::addKeyboardProxy_exec()
{
   std::cout << "Beginning test for adding a keyboard proxy...\n" << std::flush;
   return addChunkFile( "./Chunks/sim.wandkeyboardproxy02.config" );
}

bool reconfigApp::addKeyboardProxy_check()
{
   return verifyProxy( "WandKeyboardProxy02", "Wand Keyboard" );
}


bool reconfigApp::reconfigKeyboardProxy_exec()
{
   std::cout << "Beginning test for reconfiguring a keyboard proxy...\n" << std::flush;
   return swapChunkFiles( "./Chunks/sim.wandkeyboardproxy02.config", "./Chunks/sim.wandkeyboardproxy02.reconfig.config");
}

bool reconfigApp::reconfigKeyboardProxy_check()
{
   return verifyProxy( "WandKeyboardProxy02", "Head Keyboard" );
}


bool reconfigApp::removeKeyboardProxy_exec()
{
   std::cout << "Beginning test for removing a keyboard proxy...\n" << std::flush;
   return removeChunkFile( "./Chunks/sim.wandkeyboardproxy02.reconfig.config" );
}

bool reconfigApp::removeKeyboardProxy_check()
{

   //Try to get the new proxy and check its values

   if (gadget::InputManager::instance()->getProxy( "WandKeyboardProxy02" ) != NULL)
   {
      std::cout << "\tError: Keyboard proxy 02 still exists\n" << std::flush;
      return false;
   }

   return true;
}
