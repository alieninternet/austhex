/* $Id$
 * 
 * Copyright (c) 1998 Roger Yerramsetti <rogery@austnet.org>
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

/* Virtual world written by Roger 'RogerY' Yerramsetti <rogery@austnet.org> */
#error "This file hasn't been edited for mod_austhex yet"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "struct.h"
#include "vw.h"
#include "numeric.h"
#include "h.h"

extern	aClient me;
extern	int	seed;
int	match(char *, char *), find_exception(char *);
int active;
extern unsigned char tolowertab[];

 int str2array(char **pparv, char *string, char *delim)
{
    char *tok;
    int pparc=0;

    tok=(char *) strtok((char *) string,delim);
    while(tok != NULL)
    {
        pparv[pparc++]=tok;
        tok= (char *) strtok((char *) NULL,(char *) delim);
    }

    return pparc;
}


void truncstring(char *stringvar, int firstlast, int amount){
   if (firstlast)
   {
    stringvar+=amount;
    *stringvar=0;
    stringvar-=amount;
   }
    else
   {
    stringvar+=strlen(stringvar);
    stringvar-=amount;
   }
}

int
SetClient(sptr)
    aClient *sptr;
{
    SetUser(sptr);


}

unsigned
z(char *s)
{
    unsigned int i;
        
    for(i=0;*s;s++)
        i=seed*i+*s;
     
    return i;
}    



void
make_virthost(char *curr, char *new)
{
/* Virtual world written by Roger 'RogerY' Yerramsetti <rogery@austnet.org> */
    unsigned hash_total = z(curr) % HASHVAL_TOTAL, hash_partial;
    char     destroy[HOSTLEN+1], *parv[HOSTLEN+1], tmpnew[HOSTLEN], *ptr;
    int      parc=0, len=0, overflow=0, exception=0;
    
    strncpyzt(destroy, curr, HOSTLEN);
        
    len = strlen(destroy);

    if ((len + MAXVIRTSIZE) > HOSTLEN)
    {
        overflow = (len + MAXVIRTSIZE) - HOSTLEN;
        ptr = &destroy[overflow];
    }
    else 
        ptr = &destroy[0];
            
    parc = str2array(parv, ptr, ".");
    
    if (parc == 4)
    {
        len = strlen(parv[3]);
        
        if (strchr("0123456789", parv[3][len-1]))
        {
            hash_partial = (z(parv[0])+z(parv[1])+z(parv[2])) % HASHVAL_PARTIAL;
            sprintf(tmpnew, "%s.%s.%u.%u",
                parv[0], parv[1], hash_partial, hash_total);
    
            strncpyzt(new, tmpnew, HOSTLEN);
            return;
        }
    }   
        
    if (parc == 2)
    {
        sprintf(tmpnew, "vw-%u.%s.%s",
            hash_total, parv[parc-2], parv[parc-1]);
    
        strncpyzt(new, tmpnew, HOSTLEN);
        return;
    }
        
    len = strlen(parv[parc-1]);
    
    if ((len==2) && (find_exception(parv[parc-1])))
        exception = 1;
            
    if ((len == 2) && (exception == 0))
    {
        sprintf(tmpnew, "vw%u.%s.%s.%s",
            hash_total, parv[parc-3], parv[parc-2], parv[parc-1]);
        
        strncpyzt(new, tmpnew, HOSTLEN);
        return;
    }
        
    sprintf(tmpnew, "vw-%u.%s.%s",
        hash_total, parv[parc-2], parv[parc-1]);
     
    strncpyzt(new, tmpnew, HOSTLEN);
    return;
}   
