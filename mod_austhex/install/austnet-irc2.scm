;;; $Id$
;;; Additional KineIRCd mod_irc2user commands for the AustNet IRC network
;;;
;;; Copyright (c) 2003 Simon Butcher <pickle@alien.net.au>
;;;
;;; This file is a part of AustHex.
;;;
;;; AustHex is free software; you can redistribute it and/or modify
;;; it under the terms of the GNU General Public License as published by
;;; the Free Software Foundation; either version 2 of the License, or
;;; (at your option) any later version.
;;;
;;; AustHex is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.
;;;
;;; You should have received a copy of the GNU General Public License
;;; along with AustHex; if not, write to the Free Software
;;; Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
;;;


;;; Generic thingy for sending to austnet services
(define (send_to_service service payload)
   ;; Check if the service is really online
   (if
      ;; I guess, for now, this is the best way to determine if OPAS is alive?
      (online-server? "services.austnet.org")
   
      ;; Fob the data over to the PRIVMSG command
      (callcmd "PRIVMSG"
         (cons
            (string-append
	       service
	       "@austnet.org")
            payload))

      ;; Tell the user that the service is currently off-line
      (reply-notice
         (getlang "SERVICE_IS_OFFLINE"
	    (service)))))



;;; /NICKOP command
(define (cmd_NICKOP payload)
   (send_to_service "nickop" payload))

;;; Register /NICKOP command
(regcmd "NICKOP" cmd_NICKOP)



;;; /CHANOP command
(define (cmd_CHANOP payload)
   (send_to_service "chanop" payload))

;;; Register /CHANOP
(regcmd "CHANOP" cmd_CHANOP)



;;; /NOTEOP command
(define (cmd_NOTEOP payload)
   (send_to_service "noteop" payload))

;;; Register /NOTEOP
(regcmd "NOTEOP" cmd_NOTEOP)
