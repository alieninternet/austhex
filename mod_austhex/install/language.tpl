[+ AutoGen5 template lang +][+ FOR languages +][+
   (out-push-new
      (sprintf "%s%s.austhex.lang"
         (base-name)
	 (get "langCode")))
 +]# $Id$
# Language file for the mod_austhex package ([+langName+])
#
# Copyright (c) 2003 Simon Butcher <pickle@alien.net.au>
#
# This file is a part of AustHex.
#
# AustHex is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# AustHex is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with AustHex; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
[+(dne "# ")+]
#
[+
   ;;; Make the variable we are looking for, in the form of data_<langcode>
   (define (makeDataVariable)
      (sprintf "data_%s"
         (get "langCode")))

 +]
.LangCode=[+langCode+]
.LangName=[+langName+][+ IF (exist? "langNote") +]
.LangNote=[+langNote+][+ ENDIF +][+ IF (exist? "langMaintainer") +]
.Maintainer=[+langMaintainer+][+ ENDIF +]
.Revision=[+
   ;; Generate a revision based on the current time (cropped ISO 8601 style)
   (strftime "%Y%m%d%H"
      (gmtime 
         (current-time)))
 +]
[+ FOR tag +][+ IF
   ;; Make sure there is data for this tag
   (or
      (exist? "data")
      (exist? 
         (makeDataVariable)))
 +][+tagPrefix+][+name+]=[+
   ;; Grab the right data - some tags may not include language specific stuff
   (if
      (exist? "data")
      (get "data")
      (get
         (makeDataVariable)))
 +]
[+ ENDIF +][+ ENDFOR +][+ (out-pop) +][+ ENDFOR +]
