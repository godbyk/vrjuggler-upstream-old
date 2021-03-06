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

#include <gadget/gadgetConfig.h>
#include <jccl/Config/ConfigElement.h>
#include <gadget/Util/Debug.h>
#include <gadget/Type/RumbleProxy.h>

namespace gadget
{

RumbleProxy::RumbleProxy()
{
}

RumbleProxyPtr RumbleProxy::create()
{
   return RumbleProxyPtr(new RumbleProxy());
}

RumbleProxy::~RumbleProxy()
{
}

std::string RumbleProxy::getElementType()
{
   return "rumble_proxy";
}

bool RumbleProxy::config(jccl::ConfigElementPtr element)
{
   vpr::DebugOutputGuard dbg_output(gadgetDBG_INPUT_MGR, vprDBG_STATE_LVL,
      std::string("------------------ Rumble PROXY config() -----------------\n"),
      std::string("\n"));
   vprASSERT(element->getID() == getElementType());

   // We do not call TypedProxy::config() because we are explicitly overriding
   // its behavior.
   if (! Proxy::config(element))
   {
      return false;
   }

   mDeviceName = element->getProperty<std::string>("device");

   refresh();

   return true;
}

}
