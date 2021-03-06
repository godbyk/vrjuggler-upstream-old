#!/bin/sh

# ************** <auto-copyright.pl BEGIN do not edit this line> **************
#
# VR Juggler is (C) Copyright 1998-2011 by Iowa State University
#
# Original Authors:
#   Allen Bierbaum, Christopher Just,
#   Patrick Hartling, Kevin Meinert,
#   Carolina Cruz-Neira, Albert Baker
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301, USA.
#
# *************** <auto-copyright.pl END do not edit this line> ***************

# This script cleans up cached files and directories created as part of
# running aclocal(1) and autoconf(1). It is useful when either of Aclocal
# and/or Autoconf is updated or when trying to test multiple versions of
# these tools.
echo "Removing:"
find . -name aclocal.m4 -print -exec rm -f \{} \;
find . -name config.cache -print -exec rm -f \{} \;
find . -type d -name autom4te.cache -print -exec rm -rf \{} \;

echo "Updating modified type (to ensure regeneration):"
find . -name configure.ac -print -exec touch \{} \;
