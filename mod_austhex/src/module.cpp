/* $Id$
 * 
 * Copyright (c) 2003 Simon Butcher <pickle@alien.net.au>
 *
 * This file is a part of AustHex.
 * 
 * AustHex is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * AustHex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with AustHex; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifdef HAVE_CONFIG_H
# include "autoconf.h"
#endif

#include <kineircd/module.h>
#include <kineircd/irc2/library.h>
#include <iostream>

namespace {
   /* Text for the INFO command; Keep this within 60 chars width.
    * 
    * NOTE: that it is in VIOLATION of the GNU GPL to remove any copyright
    * details from this text.
    */
   static const char* const infoText[] = {
      "\002                     __             __\002",
      "\002   ____ ___  _______/ /_____  ___  / /_\002    _ _ _  . _ _ _",
      "\002  / __ `/ / / / ___/ __/ __ \\/ _ \\/ __/\002   _)(\037-\037| \\/|(_(\037-\037_)",
      "\002 / /_/ / /_/ (__  ) /_/ / / /  __/ /__ \002    support module",
      "\002 \\__,_/\\__,_/____/\\__/_/ /_/\\___/\\___/\002",
      "        \037http://www.austnet.org/\037",
      "",
      "Copyright (c) 2003 Simon Butcher <pickle@alien.net.au>",
      "Please report bugs to \037" PACKAGE_BUGREPORT "\037",
      0
   };

   // Information about this module
   static const Kine::Module::Info info = {
      // Firstly, we list the version/copyright information for this module
      "mod_austhex",
      "AustNet Support Module",
      0, // Major version number
      0, // Minor version number
      infoText, // INFO text
	
      // Flags to define how we need to be run
      Kine::Module::Flags::UNIQUE_INSTANCE,

      // Configuration
      0
   };


   class mod_austhex : public Kine::Module {
    public:
      // Constructor
      mod_austhex(void)
	{};
      
      // Destructor
      ~mod_austhex(void)
	{
	   // Deinitialise the IRC-2 library
	   Kine::LibIRC2::deinit();
	};
      
      // Return the information
      const Kine::Module::Info& getInfo(void) const
	{ return info; };
      
      // Start the module
      bool start(void) {
	 // Initialise the IRC-2 library
	 if (!Kine::LibIRC2::init()) {
	    return false;
	 }
	 
	 // Tell Kine we started okay
	 return true;
      };
   }; // class mod_austhex
}; // namespace {anonymous}


// The initialisation function, called by Kine
KINE_MODULE_INIT { return new mod_austhex(); };
