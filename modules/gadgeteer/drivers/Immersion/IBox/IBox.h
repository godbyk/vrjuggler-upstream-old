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

#ifndef _GADGET_IBOX_H_
#define _GADGET_IBOX_H_

#include <gadget/Devices/DriverConfig.h>

#include <vector>
#include <boost/mpl/inherit.hpp>

#include <gadget/Type/InputDevice.h>

#include "IBoxStandalone.h"


namespace gadget
{

/**
 * The Immersion Box input class.
 *
 * The Immersion Box is a 4 Digital, 4 Analog input device, the Ibox class
 * therefore must inherit from both Digital and Analog.
 */
class IBox
   : public InputDevice<boost::mpl::inherit<Digital, Analog>::type>
{
public:
   /** Construction/Destruction */
   IBox() : mDoneFlag(false), mButton(4), mAnalog(4)
   {
      // re-set Analog min/max values to ibox defaults.
      this->setMin( 0.0f );
      this->setMax( 255.0f );
   }
   virtual ~IBox();

   virtual bool config(jccl::ConfigElementPtr e);

   /** @name  Input Pure Virtual Functions */
   //@{
   bool startSampling();
   bool stopSampling();
   bool sample();
   void updateData();
   //@}

   static std::string getElementType();
   void controlLoop();

private:
   IBoxStandalone* mIBox;
   std::string     mPortName;
   long            mBaudRate;
   bool            mDoneFlag;
   bool            mDataUpdated;
   std::vector<DigitalData> mButton;    // size of 4
   std::vector<AnalogData>  mAnalog;    // size of 4
};

} // End of gadget namespace

#endif
