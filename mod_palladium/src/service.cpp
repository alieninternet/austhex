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

#include <aisutil/string/string.h>
#include <kineircd/daemon.h>
#include <kineircd/myserver.h>

#include "service.h"

using namespace AustHex::mod_palladium;
using AISutil::String;


/* Service - Create the palladium service! :)
 * Original 13/05/2003 simonb
 * Note: Should be grabbing defaults from config, not hard-coded
 */
Service::Service(void)
  : Kine::Service("Pd",
		  Kine::myServer().getName(),
		  Kine::daemon().getTime()),
    description("Palladium Operator Service")
{
}


/* sendQuery - Process a message sent to us from a client
 * Original 13/05/2003 simonb
 */
const Kine::Error::error_type
  Service::sendQuery(Client& from, const std::string& message,
		     const Receiver::Directivity directivity)
{
   /* For now, return what they said to us, since we have no code to handle
    * commands, yet.
    */
   from.sendNotice(*this, "You said: " + message);
   
   // We had no problems..
   return Error::NO_ERROR;
}


/* sendMessage - Process a private message sent to us
 * Original 13/05/2003 simonb
 */
const Kine::Error::error_type
  Service::sendMessage(Sender& from, const std::string& message,
		       const Receiver::Directivity directivity)
{
   // Okay.. well.. try to convert this into a client
   Client* const client =
     dynamic_cast<Client* const>(&from);
   
   // Is it a client? (it's most likely to be one)
   if (client != 0) {
      // Is the message CTCP?
      if ((message[0] == '\001') &&
	  (message[message.length() - 1] == '\001')) {
	 // Find the first space..
	 std::string::size_type separator = message.find(' ');

	 // Check the separator is valid
	 if (separator == (std::string::size_type)-1) {
	    separator = (message.length() - 1);
	 }

	 // Fob this off to the CTCP handling doohickey..
	 handleCTCP(*client,
		    static_cast<const String&>
		    (message.substr(1, separator - 1)).toUpper(),
		    message.substr(separator + 1,
				   message.length() - separator - 2));
	 return Error::NO_ERROR;
      }
      
      // Okay, it was not CTCP, so throw the payload over to the query handler
      return sendQuery(*client, message);
   }

   // Umm, if we got here, we cannot deal with the entity type who sent this
   return Error::UNSUPPORTED_BY_ENTITY;
}
