/* $Id$
 * 
 * Copyright (c) 2003 Simon Butcher <pickle@alien.net.au>
 *
 * This file is a part of AustHex/Palladium.
 * 
 * KineIRCd is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * KineIRCd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with KineIRCd; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifdef HAVE_CONFIG_H
# include "autoconf.h"
#endif

#include <kineircd/module.h>
#include <kineircd/registry.h>

#include "service.h"


namespace {
   /* Text for the INFO command; Keep this within 60 chars width.
    * 
    * NOTE: that is is in VIOLATION of the GNU GPL to remove any copyright
    * details from this text.
    */
   static const char* const infoText[] = {
      "Copyright (c) 2003 Simon Butcher <pickle@alien.net.au>",
      "Please report bugs to \037" PACKAGE_BUGREPORT "\037",
      0
   };
   
   // Information about this module
   static const Kine::Module::Info info = {
      // Firstly, we list the version/copyright information for this module
      "mod_palladium",
      "Palladium Connection Monitor",
      0, // Major version number 
      0, // Minor version number
      infoText, // INFO text
	
      // Flags to define how we need to be run
      Kine::Module::Flags::UNIQUE_INSTANCE,

      // Configuration stuff
      0
   };


   class mod_palladium : public Kine::Module {
    private:
      AustHex::mod_palladium::Service* service;
      
    public:
      // Constructor
      mod_palladium(void)
	: service(0)
	{};
      
      // Destructor
      ~mod_palladium(void)
	{
	   // If we created the service, destroy it
	   if (service != 0) {
	      delete service;
	   }
	};

      // Return the information
      const Kine::Module::Info& getInfo(void) const
	{ return info; };

      /* start - Fire up the module
       * Original 12/05/2003 simonb
       */
      bool start(void) {
	 // If we already exist, that's not a good thing and something broke
	 if (service != 0) {
	    // log the error?
	    return false;
	 }
	 
	 // Create a new instance of ourself
	 if ((service = new AustHex::mod_palladium::Service()) == 0) {
	    // log the error?
	    return false;
	 }
	 
	 // Try to register the service
	 if (Kine::myServer().addService(*service) != Kine::Error::NO_ERROR) {
	    // log the error?
	    return false;
	 }
	 
	 // If we got this far, then we should be rocking!
	 return true;
      };
   }; // class mod_palladium
}; // namespace {anonymous}


// The initialisation function, called by Kine
KINE_MODULE_INIT { return new mod_palladium(); };
