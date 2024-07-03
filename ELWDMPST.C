/*****************************************************************************
 *                                                                           *
 *       EZEDMPST.C - An announcement broadcaster                            *
 *                                                                           *
 * Developed 09/24/94 by 'Easy Ed' Erdman.   Major BBS developer code 'EZE'. *
 *                                                                           *
 *       Updates : 1/19/95 - Version 1.1                                     *
 *                 Don't pester users in editor                              *
 *                 2/20/95 - Version 1.2                                     *
 *                 Remove code to not pester in editor due to bugs           *
 *                 6/8/95  - Version 1.3                                     *
 *                 Require access code to get info on the users              *
 *                 Color .MSG file messages                                  *
 *                 10/5/95 - Version 1.4                                     *
 *                 Remove access code requirement                            *
 *  		          Add option to "beep" users receiving message              *
 *		             Add option to not pester users in The Editor		        *
 *                 Move message from LEVEL4 {} CNF to LEVEL6 {}              *
 *                 7/24/96 - Version 1.4W                                    *
 *                 Converted for WG3.0 By Mike Baker of Risfter Ent.         *
 *                 5/15/2021 - Version 1.5                                   *
 *                 Converted for WG3.2 By Rick Hadsall/Elwynor Technologies  *
 *                 7/1/2024  - Version 1.5                                   *
 *                 Converted for MBBS V10                                    *
 *                                                                           *
 *       Copyright (C) 1995 by EzSoft. All rights reserved.                  *
 *       Copyright (C) 2004-2024 Elwynor Technologies. All Rights Reserved.  *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU Affero General Public License as published  *
 * by the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.     *
 *                                                                           *
 * Additional Terms for Contributors:                                        *
 * 1. By contributing to this project, you agree to assign all right, title, *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies.                              *
 * 2. You grant Rick Hadsall and Elwynor Technologies a non-exclusive,       *
 *    royalty-free, worldwide license to use, reproduce, prepare derivative  *
 *    works of, publicly display, publicly perform, sublicense, and          *
 *    distribute your contributions                                          *
 * 3. You represent that you have the legal right to make your contributions *
 *    and that the contributions do not infringe any third-party rights.     *
 * 4. Rick Hadsall and Elwynor Technologies are not obligated to incorporate *
 *    any contributions into the project.                                    *
 * 5. This project is licensed under the AGPL v3, and any derivative works   *
 *    must also be licensed under the AGPL v3.                               *
 * 6. If you create an entirely new project (a fork) based on this work, it  *
 *    must also be licensed under the AGPL v3, you assign all right, title,  *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies, and you must include these   *
 *    additional terms in your project's LICENSE file(s).                    *
 *                                                                           *
 * By contributing to this project, you agree to these terms.                *
 *                                                                           *
 *****************************************************************************/

#include "gcomm.h"
#include "majorbbs.h"
#include "protstuf.h"
#include "elwdmpst.h"

VOID EXPORT init__elwdmpst( VOID );      /* module initializer */
GBOOL dmpstinput( VOID );                /* module user input handler */
VOID clsdmpst( VOID );                   /* BBS shutdown routine */
VOID dmpst( VOID );                      /* the main routine - bug the DEMOs */
VOID dobeep( INT numbeeps );             /* "beep" user's computer */
INT userineditor( VOID );	    		 /* returns 1 if othusn is in the Editor, 0 if not or if error */

struct module dmpstmod={
	"",                           /* name used to refer to this module */
	NULL,                         /* user logon supplemental routine */
	dmpstinput,                   /* input routine if selected */
	dfsthn,                       /* status-input routine if selected */
	NULL,	                      /* "injoth" routine for this module */
	NULL,                         /* user logoff supplemental routine */
	NULL,                         /* hangup (lost carrier) routine */
	NULL,                         /* midnight cleanup routine */
	NULL,                         /* delete-account routine */
	clsdmpst,                     /* finish-up (sys shutdown) routine */
};

INT dmpststat;               /* the module state no. */
HMCVFILE dmpstmbk;           /* module message file pointer */
INT dmpstsecs;               /* number of seconds between broadcasts */
INT beepusers;               /* 1 if "beep" user's computer, 0 if don't */
CHAR *pesterkey;             /* key needed to not be bothered with announcement */
CHAR *DMPST_VER="1.5";       /* program version number */
CHAR *editorname;            /* the name of the Editor module */
INT bugineditor;             /* 1 if pester users in the Editor, 0 if don't */

VOID EXPORT init__elwdmpst( VOID )          /* the module initialization routine */
{
	shocst(spr("ELW Announcer %s", DMPST_VER), "Copyright 2021-2024 Elwynor Technologies - www.elwynor.com");
	stzcpy(dmpstmod.descrp, gmdnam("elwdmpst.mdf"),MNMSIZ);
	dmpststat=register_module(&dmpstmod);
	dmpstmbk=opnmsg("elwdmpst.mcv");
	dmpstsecs=numopt(PSTSEC, 30, 3600);
	beepusers=ynopt(DOBEEP);
	bugineditor=ynopt(EDITBUG);
	editorname=stgopt(EDTNAM);
	pesterkey=stgopt(PSTKEY);
	rtkick( dmpstsecs, dmpst );
}

GBOOL dmpstinput( VOID )                          /* module user input handler */
{
	return(0);
}

VOID clsdmpst( VOID )                           /* BBS shutdown routine */
{
	clsmsg(dmpstmbk);
}

VOID dmpst( VOID )                                                              /* bug those DEMO users! */
{
	setmbk(dmpstmbk);
	for ( othusn=0; othusn < nterms; othusn++ )	{       /* announce to everyone without key */
		othuap=uacoff(othusn);
      othusp=usroff(othusn);
		if ( ( ( othusp->usrcls == ACTUSR ) || ( othusp->usrcls == BBSPRV ) ) &&
		   ( isuidc(othuap->userid[0]) ) && ( !othkey(pesterkey) ) && ( bugineditor || !userineditor() ) )
			{      /* make sure someone is on channel, and not in editor */
			if ( beepusers )	dobeep(1);
			prfmsg(PSTTXT);
			injoth();
		}
	}
	rstmbk();
	rtkick( dmpstsecs, dmpst );
}

VOID dobeep( INT numbeeps )                              /* "beep" user's computer */
{
	INT beepcount;                  /* "beep" in loop we are making */

	for ( beepcount=0; beepcount < numbeeps; beepcount++ ) prf("\a");
}

INT userineditor( VOID )		    			/* returns 1 if othusn is in the Editor, 0 if not or if error */
{
	INT fsestate;					/* module number for Editor; usrptr->state when user is in the Editor */

	fsestate=findmod(editorname);
	if ( fsestate == -1 ) return(0);	/* no such module loaded */
	if ( fsestate == othusp->state ) return(1);	/* user is in the Editor */
	return(0);
}
