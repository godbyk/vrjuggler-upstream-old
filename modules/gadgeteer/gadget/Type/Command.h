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

#ifndef _GADGET_COMMAND_H_
#define _GADGET_COMMAND_H_

#include <gadget/gadgetConfig.h>

#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/signals2/signal.hpp>

#include <vpr/Util/SignalProxy.h>
#include <vpr/IO/SerializableObject.h>

#include <jccl/Config/ConfigElementPtr.h>

#include <gadget/Type/CommandPtr.h>
#include <gadget/Type/CommandData.h>
#include <gadget/Type/SampleBuffer.h>
#include <gadget/Util/DeviceSerializationTokens.h>


namespace gadget
{

const unsigned short MSG_DATA_COMMAND = 423;

/** \class Command Command.h gadget/Type/Command.h
 *
 * Command is the abstract base class for devices that generate
 * commands into integer-identified commands.  Drivers for all such
 * devices must derive from this class (through gadget::InputDevice).  This
 * is in addition to gadget::Input.  gadget::Input provides pure virtual
 * function constraints in the following functions: startSampling(),
 * stopSampling(), sample(), and updateData().
 *
 * gadget::Command adds the function getCommandData() for retreiving the
 * received commands.  This is similar to the additions made by
 * gadget::Position and gadget::Analog.
 *
 * @see Input
 * @see InputDevice
 */
class GADGET_API Command
   : public vpr::SerializableObject
   , private boost::noncopyable
{
public:
   typedef SampleBuffer<CommandData> SampleBuffer_t;
   typedef boost::signals2::signal<void (const std::vector<CommandData>&)> add_signal_t;

protected:
   /* Constructor/Destructors */
   Command();

public:
   /**
    * Creates a Command instance and returns it wrapped in a
    * CommandPtr object.
    *
    * @since 1.3.7
    */
   static CommandPtr create();

   virtual ~Command();

   virtual bool config(jccl::ConfigElementPtr)
   {
      return true;
   }

   /**
    * Gets the command data for the given devNum.
    *
    * @return Command 0 or 1, if devNum makes sense.
    *         -1 is returned if function fails or if devNum is out of range.
    * @note If devNum is out of range, function will fail, possibly issuing
    *       an error to a log or console - but will not ASSERT.
    */
   const CommandData getCommandData(const int devNum = 0) const;

   /**
    * Helper method to add a collection of command samples to the sample
    * buffers.  This MUST be called by all command devices to add new
    * samples.
    *
    * @post The given command samples are added to the buffers.
    *
    * @param cmdSample A vector of CommandData objects that represent the
    *                  newest samples taken.
    */
   void addCommandSample(const std::vector<CommandData>& cmdSample);

   /**
    * Swaps the command data buffers.
    *
    * @post If the ready queue has values, then those values are copied from
    *       the ready queue to the stable queue.  If not, then stable queue
    *       is not changed.
    */
   void swapCommandBuffers()
   {
      mCommandSamples.swapBuffers();
   }

   /**
    * Returns the current stable sample buffers for this device.
    */
   const SampleBuffer_t::buffer_t& getCommandDataBuffer() const
   {
      return mCommandSamples.stableBuffer();
   }

   /**
    * Serializes this object into the given object writer.
    *
    * @param writer The object writer to which this object will be
    *               serialized.
    *
    * @throw vpr::IOException is thrown if serialization fails.
    */
   virtual void writeObject(vpr::ObjectWriter* writer);

   /**
    * De-serializes this object.
    *
    * @param reader The object reader from which this object will be
    *               de-serialized.
    *
    * @throw vpr::IOException is thrown if de-serialization fails.
    */
   virtual void readObject(vpr::ObjectReader* reader);

   /**
    * @since 2.1.7
    */
   vpr::SignalProxy<add_signal_t> dataAdded()
   {
      return mDataAdded;
   }

private:
   static const std::string sTypeName;

   add_signal_t mDataAdded;

   SampleBuffer_t mCommandSamples; /**< Command samples */
   CommandData    mDefaultValue;   /**< Default command value to return */
};

} // End of gadget namespace

#endif   /* _GADGET_COMMAND_H_ */
