/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2011 by Iowa State University
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
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

//=====================================================
// Vrpn
//
// Purpose:
//    VR Juggler VRPN Hi-Ball tracking class
//
// Author:
//    Jason Jerald
// Last Modified:  8-26-02
//
// Revisions:
//      Ported to to 1.1 DR2 and sgi platform Anthony Steed, 10-4-02
//======================================================

#ifndef _GADGET_VRPN_H_
#define _GADGET_VRPN_H_

#include <gadget/Devices/DriverConfig.h>

#include <vector>
#include <boost/mpl/inherit.hpp>
#include <boost/shared_ptr.hpp>

#include <vpr/Sync/Mutex.h>
#include <gadget/Type/InputDevice.h>
#include <gadget/Type/Rumble.h>

#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Vec.h>
#include <gmtl/Quat.h>

#include <vrpn_Tracker.h>
#include <vrpn_Button.h>
#include <vrpn_Analog.h>
#include <vrpn_Analog_Output.h>

#if ! defined(VRPN_CALLBACK)
#  define VRPN_CALLBACK
#endif


namespace gadget
{

/**
 * Class interfacing with VRPN sensor data.
 *
 * @note A note on reciever access:
 *  Clients of Juggler should access tracker recievers as [0-n].  For
 *  example, if you have recievers 1,2, and 4 with transmitter on 3, then
 *  you can access the data, in order, as 0, 1, 2.
 *
 * @see gadget::Digital
 * @see gadget::Analog
 * @see gadget::Position
 */
class Vrpn
   : public InputDevice<boost::mpl::inherit<Digital, Analog, Position, Rumble>::type>
{
public:

   /** Constructor. */
   Vrpn();

   /**
    * Destructor.
    *
    * @pre None.
    * @post Shared memory is released.
    */
   virtual ~Vrpn();

   /**
    * Configures the VRPN with the given config element.
    *
    * @pre e must be a element that has VRPN config information.
    * @post If e is a valid config element, the device is configured using
    *       its contents.  Otherwise, configuration fails and false is
    *       returned to the caller.
    *
    * @param e A pointer to a config element.
    *
    * @return true is returned if the device was configured succesfully.
    *         false is returned if the config element is invalid.
    */
   virtual bool config(jccl::ConfigElementPtr e);

   /** Begins sampling. */
   bool startSampling();

   /** Stops sampling. */
   bool stopSampling();

   /** Samples a value. */
   bool sample();

   /**
    * Update to the sampled data.
    *
    * @pre None.
    * @post Most recent value is copied over to temp area.
    */
   void updateData();

   /** Returns what element type is associated with this class. */
   static std::string getElementType();

   /**
    * Gets the supported capabilities in a bitmask.
    *
    * @return bitmask defined in Rumble::RumbleType
    *
    */
   virtual unsigned int getCapabilities();


   void startRumble();
   void stopRumble();

protected:
   virtual gadget::RumbleEffectPtr createEffectImp(gadget::RumbleEffect::RumbleType type);

private:

   void readLoop();

   /** @name VRPN Data Handlers */
   //@{
   void trackerChange(const vrpn_TRACKERCB& t);
   void buttonChange(const vrpn_BUTTONCB& b);
   void analogChange(const vrpn_ANALOGCB& b);
   //@}

   bool mExitFlag;

   /** @name Tracker Data */
   //@{
   std::string              mTrackerServer;
   int                      mTrackerNumber;
   vpr::Mutex               mTrackerMutex;
   std::vector<gmtl::Quatf> mQuats;
   std::vector<gmtl::Vec3f> mPositions;
   //@}

   /** @name Button Data */
   //@{
   std::string                      mButtonServer;
   int                              mButtonNumber;
   vpr::Mutex                       mButtonMutex;
   std::vector<gadget::DigitalData> mButtons;
   //@}

   /** @name Analog Data */
   //@{
   std::string                     mAnalogServer;
   int                             mAnalogNumber;
   vpr::Mutex                      mAnalogMutex;
   std::vector<gadget::AnalogData> mAnalogs;
   boost::shared_ptr<vrpn_Analog_Output_Remote> mAnalogOutHandle;
   vpr::Mutex                      mVrpnConnectionMutex;;
   //@}

   friend void VRPN_CALLBACK handleTrackerChange(void*, vrpn_TRACKERCB);
   friend void VRPN_CALLBACK handleButtonChange(void*, vrpn_BUTTONCB);
   friend void VRPN_CALLBACK handleAnalogChange(void*, vrpn_ANALOGCB);
};

} // End of gadget namespace


#endif
