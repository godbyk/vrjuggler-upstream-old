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

#ifndef _GADGET_DIGITAL_H_
#define _GADGET_DIGITAL_H_

#include <gadget/gadgetConfig.h>

#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/signals2/signal.hpp>

#include <vpr/Util/SignalProxy.h>
#include <vpr/IO/SerializableObject.h>

#include <jccl/Config/ConfigElementPtr.h>

#include <gadget/Type/DigitalData.h>
#include <gadget/Type/SampleBuffer.h>
#include <gadget/Type/DigitalPtr.h>


namespace gadget
{

const unsigned short MSG_DATA_DIGITAL = 420;

/** \class Digital Digital.h gadget/Type/Digital.h
 *
 * Digital is the abstract base class from which devices with digital data
 * derive (through gadget::InputDevice). This is in addition to gadget::Input.
 * gadget::Input provides pure virtual function constraints in the following
 * functions: startSampling(), stopSampling(), sample(), and updateData().
 *
 * gadget::Digital adds the function getDigitalData() for retreiving the
 * received digital data. This is similar to the additions made by
 * gadget::Position and gadget::Analog.
 *
 * @see Input
 * @see InputDevice
 */
class GADGET_API Digital
   : public vpr::SerializableObject
   , protected DigitalState
   , private boost::noncopyable
{
public:
   typedef SampleBuffer<DigitalData> SampleBuffer_t;
   typedef boost::signals2::signal<void (const std::vector<DigitalData>&)> add_signal_t;

   /** @name Compatibility */
   //@{
   using DigitalState::OFF;
   using DigitalState::ON;
   using DigitalState::TOGGLE_ON;
   using DigitalState::TOGGLE_OFF;
   //@}

protected:
   /* Constructor/Destructors */
   Digital();

public:
   /**
    * Creates a Digital instance and returns it wrapped in a
    * DigitalPtr object.
    *
    * @since 1.3.7
    */
   static DigitalPtr create();

   virtual ~Digital();

   virtual bool config(jccl::ConfigElementPtr)
   {
      return true;
   }

   /**
    * Gets the digital data for the given devNum.
    *
    * @return Digital 0 or 1, if devNum makes sense.
    *         -1 is returned if function fails or if devNum is out of range.
    *
    * @note If devNum is out of range, function will fail, possibly issuing
    *       an error to a log or console - but will not ASSERT.
    */
   const DigitalData getDigitalData(int devNum = 0);

   /**
    * Helper method to add a collection of digital samples to the sample
    * buffers.  This MUST be called by all digital devices to add new
    * samples.
    *
    * @post The given digital samples are added to the buffers.
    *
    * @param digSample A vector of DigitalData objects that represent the
    *                  newest samples taken.
    */
   void addDigitalSample(const std::vector<DigitalData>& digSample);

   /**
    * Swaps the digital data buffers.
    *
    * @post If the ready queue has values, then those values are copied from
    *       the ready queue to the stable queue.  If not, then stable queue
    *       is not changed.
    */
   void swapDigitalBuffers()
   {
      mDigitalSamples.swapBuffers();
   }

   /**
    * Returns the current stable sample buffers for this device.
    */
   const SampleBuffer_t::buffer_t& getDigitalDataBuffer()
   {
      return mDigitalSamples.stableBuffer();
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
    * @since 2.1.6
    */
   vpr::SignalProxy<add_signal_t> dataAdded()
   {
      return mDataAdded;
   }

private:
   static const std::string sTypeName;

   add_signal_t mDataAdded;

   SampleBuffer_t    mDigitalSamples; /**< Digital samples */
   DigitalData       mDefaultValue;   /**< Default digital value to return */
};

} // End of gadget namespace

#endif   /* _GADGET_DIGITAL_H_ */
