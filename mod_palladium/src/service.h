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

#ifndef _SRC_SERVICE_H_
# define _SRC_SERVICE_H_ 1

# include <string>
# include <sstream>
# include <kineircd/client.h>
# include <kineircd/service.h>
# include <kineircd/errors.h>
# include <kineircd/myserver.h>

namespace AustHex {
   namespace mod_palladium {
      // The Palladium service
      class Service : public Kine::Service {
       private:
	 // Our 'description' of ourself
	 const std::string description;
	 
       public:
	 // Constructor
	 Service(void);
	 
	 
	 // Return our description
	 const std::string& getDescription(void) const
	   { return description; };

	 
	 // Send a correctly formatted CTCP reply
	 template <class Tc, class Tp>
	   void replyToCTCP(Client& to, const Tc& command, const Tp& params)
	     {
		std::ostringstream reply;
		reply << '\001' << command << ' ' << params << '\001';
		to.sendNotice(*this, reply.str());
	     }
	 
	 // Handle CTCP requests.. eek
	 const void handleCTCP(Client& from, const std::string& command,
			       const std::string& parameters);

	 
	 // Send a query to this service from a client
	 const Error::error_type
	   sendQuery(Client& from,
		     const std::string& message,
		     const Receiver::Directivity directivity =
		     Receiver::Directivity());

	 // We will accept PRIVMSG's if the rules are set to do so
	 const Error::error_type
	   sendMessage(Sender& from,
		       const std::string& message,
		       const Receiver::Directivity directivity =
		       Receiver::Directivity());
	 
	 
	 // Return the server we're connected to (which is 'us', locally)
	 Kine::Server& getServer(void)
	   { return Kine::myServer(); };
      }; // class Service
   }; // namespace mod_palladium
}; // namespace AustHex

#endif // _SRC_SERVICE_H_
