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

#include "service.h"

using namespace AustHex::mod_palladium;


/* handleCTCP - Process a CTCP command
 * Original 13/05/2003 simonb
 */
const void Service::handleCTCP(Client& from, const std::string& command,
			       const std::string& parameters)
{
   // For now we only reply to PING's.. this is daft :-/
   if (command == "PING") {
      // Return everything we got
      replyToCTCP(from, command, parameters);
      return;
   }
}
