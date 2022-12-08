/* $XFree86: xc/programs/Xserver/os/osinit.c,v 3.34 2006/03/16 21:44:00 dawes Exp $ */
/***********************************************************

Copyright 1987, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.


Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/
/*
 * Copyright (c) 1996-2006 by The XFree86 Project, Inc.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 *   1.  Redistributions of source code must retain the above copyright
 *       notice, this list of conditions, and the following disclaimer.
 *
 *   2.  Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer
 *       in the documentation and/or other materials provided with the
 *       distribution, and in the same place and form as other copyright,
 *       license and disclaimer information.
 *
 *   3.  The end-user documentation included with the redistribution,
 *       if any, must include the following acknowledgment: "This product
 *       includes software developed by The XFree86 Project, Inc
 *       (http://www.xfree86.org/) and its contributors", in the same
 *       place and form as other third-party acknowledgments.  Alternately,
 *       this acknowledgment may appear in the software itself, in the
 *       same form and location as other such third-party acknowledgments.
 *
 *   4.  Except as contained in this notice, the name of The XFree86
 *       Project, Inc shall not be used in advertising or otherwise to
 *       promote the sale, use or other dealings in this Software without
 *       prior written authorization from The XFree86 Project, Inc.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE XFREE86 PROJECT, INC OR ITS CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <signal.h>
#include <X11/X.h>
#include "os.h"
#include "osdep.h"
#include <X11/Xos.h>

#ifdef SMART_SCHEDULE
#include "dixstruct.h"
#endif

#ifndef	TROPIX

#ifndef PATH_MAX
#ifdef MAXPATHLEN
#define PATH_MAX MAXPATHLEN
#else
#define PATH_MAX 1024
#endif
#endif

#if defined(Lynx) || defined(__SCO__)
#include <sys/wait.h>
#endif

#if !defined(SYSV) && !defined(WIN32) && !defined(Lynx) && !defined(QNX4)
#include <sys/resource.h>
#endif

#ifndef ADMPATH
#define ADMPATH "/usr/adm/X%smsgs"
#endif

extern char *display;
#ifdef RLIMIT_DATA
int limitDataSpace = -1;
#endif
#ifdef RLIMIT_STACK
int limitStackSpace = -1;
#endif
#ifdef RLIMIT_NOFILE
int limitNoFile = -1;
#endif

Bool OsDelayInitColors = FALSE;

void
OsInit(void)
{
    static Bool been_here = FALSE;
    static char* admpath = ADMPATH;
    static char* devnull = "/dev/null";
    char fname[PATH_MAX];

#ifdef macII
    set42sig();
#endif

#ifdef DDXOSINIT
    OsVendorPreInit();
#endif

    if (!been_here) {
#if !defined(__SCO__) && !defined(__CYGWIN__)
	fclose(stdin);
	fclose(stdout);
#endif
	/* 
	 * If a write of zero bytes to stderr returns non-zero, i.e. -1, 
	 * then writing to stderr failed, and we'll write somewhere else 
	 * instead. (Apparently this never happens in the Real World.)
	 */
	if (write (2, fname, 0) == -1) 
	{
	    FILE *err;

	    if (strlen (display) + strlen (admpath) + 1 < sizeof fname)
		sprintf (fname, admpath, display);
	    else
		strcpy (fname, devnull);
	    /*
	     * uses stdio to avoid os dependencies here,
	     * a real os would use
 	     *  open (fname, O_WRONLY|O_APPEND|O_CREAT, 0666)
	     */
	    if (!(err = fopen (fname, "a+")))
		err = fopen (devnull, "w");
	    if (err && (fileno(err) != 2)) {
		dup2 (fileno (err), 2);
		fclose (err);
	    }
#if defined(SYSV) || defined(SVR4) || defined(__UNIXOS2__) || defined(WIN32) || defined(__CYGWIN__)
	    {
	    static char buf[BUFSIZ];
	    setvbuf (stderr, buf, _IOLBF, BUFSIZ);
	    }
#else
	    setlinebuf(stderr);
#endif
	}

#ifndef X_NOT_POSIX
	if (getpgrp () == 0)
	    setpgid (0, 0);
#else
#if !defined(SYSV) && !defined(WIN32)
	if (getpgrp (0) == 0)
	    setpgrp (0, getpid ());
#endif
#endif

#ifdef RLIMIT_DATA
	if (limitDataSpace >= 0)
	{
	    struct rlimit	rlim;

	    if (!getrlimit(RLIMIT_DATA, &rlim))
	    {
		if ((limitDataSpace > 0) && (limitDataSpace < rlim.rlim_max))
		    rlim.rlim_cur = limitDataSpace;
		else
		    rlim.rlim_cur = rlim.rlim_max;
		(void)setrlimit(RLIMIT_DATA, &rlim);
	    }
	}
#endif
#ifdef RLIMIT_STACK
	if (limitStackSpace >= 0)
	{
	    struct rlimit	rlim;

	    if (!getrlimit(RLIMIT_STACK, &rlim))
	    {
		if ((limitStackSpace > 0) && (limitStackSpace < rlim.rlim_max))
		    rlim.rlim_cur = limitStackSpace;
		else
		    rlim.rlim_cur = rlim.rlim_max;
		(void)setrlimit(RLIMIT_STACK, &rlim);
	    }
	}
#endif
#ifdef RLIMIT_NOFILE
	if (limitNoFile >= 0)
	{
	    struct rlimit	rlim;

	    if (!getrlimit(RLIMIT_NOFILE, &rlim))
	    {
		if ((limitNoFile > 0) && (limitNoFile < rlim.rlim_max))
		    rlim.rlim_cur = limitNoFile;
		else
		    rlim.rlim_cur = rlim.rlim_max;
#if 0
		if (rlim.rlim_cur > MAXSOCKS)
		    rlim.rlim_cur = MAXSOCKS;
#endif
		(void)setrlimit(RLIMIT_NOFILE, &rlim);
	    }
	}
#endif
#ifdef SERVER_LOCK
	LockServer();
#endif
	been_here = TRUE;
    }
    TimerInit();
#ifdef DDXOSINIT
    OsVendorInit();
#endif
    /*
     * No log file by default.  OsVendorInit() should call LogInit() with the
     * log file name if logging to a file is desired.
     */
    LogInit(NULL, NULL);
#ifdef SMART_SCHEDULE
    if (!SmartScheduleDisable)
	if (!SmartScheduleInit ())
	    SmartScheduleDisable = TRUE;
#endif
    OsInitAllocator();
    if (!OsDelayInitColors) OsInitColors();
}

void
OsCleanup(Bool terminating)
{
#ifdef SERVER_LOCK
    if (terminating)
    {
	UnlockServer();
    }
#endif
}

#else

const char	log_file[]	= "/var/log/xwin/xserver.log";
Bool		OsDelayInitColors = FALSE;

/*
 ****************************************************************
 *	Inicializa a Camada OS					*
 ****************************************************************
 */
void
OsInit (void)
{
	static Bool	been_here = FALSE;
	static char	buf[BUFSIZ];
	FILE		*err;
	int		stderrno;

	if (!been_here)
	{
		/* Primeira chamada a esta rotina */

		fclose (stdin);
		fclose (stdout);

		/*
		 *	Cria o arquivo de LOCK.
		 */
		LockServer ();

		stderrno = fileno (stderr);

		/*
		 *	Evita imprimir mensagens na tela.
		 */
		if ((err = fopen (log_file, "w")) == NOFILE)
		{
			err = fopen ("/dev/null", "w");
		}
		else
		{
			chown (log_file, getuid (), getgid ());
			chmod (log_file, 0644);
		}

		if (err != NOFILE && (fileno (err) != stderrno))
		{
			dup2 (fileno (err), stderrno);
			fclose (err);
		}

		setvbuf (stderr, buf, _IOLBF, BUFSIZ);

#if (0)	/*******************************************************/
		read_symtb ("/usr/xwin/bin/.X");
#endif	/*******************************************************/

		been_here = TRUE;

		if (nice (5 - nice (0)) < 0)
			Log ("N�o consegui alterar o valor do \"nice\"");
	}

	/*
	 *	Realiza diversas inicializa��es.
	 */
	TimerInit ();

#ifdef DDXOSINIT
	OsVendorInit ();
#endif

#ifdef SMART_SCHEDULE
	if (!SmartScheduleDisable && !SmartScheduleInit ())
		SmartScheduleDisable = TRUE;
#endif

	OsInitAllocator ();

	if (!OsDelayInitColors)
		OsInitColors ();

}	/* end OsInit */

/*
 ****************************************************************
 *	Finaliza o uso da camada OS				*
 ****************************************************************
 */
void
OsCleanup (Bool terminating)
{
	UnlockServer ();

}	/* end OsCleanup */

#endif	TROPIX

/* Make sure that signals don't cause re-entry during screen close. */
void
OsPrepareShutdown(Bool terminating)
{
    if (terminating) {
	OsSignal(SIGINT, SIG_IGN);
    } else {
	OsSignal(SIGINT, GiveUp);
    }
}

/* Reset signal disposition before reset. */
void
OsPrepareRestart()
{
    OsSignal(SIGINT, AbortServer);
}

