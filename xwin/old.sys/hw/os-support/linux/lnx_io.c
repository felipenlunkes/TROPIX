/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/linux/lnx_io.c,v 3.30 2005/10/14 15:17:03 tsi Exp $ */
/*
 * Copyright 1992 by Orest Zborowski <obz@Kodak.com>
 * Copyright 1993 by David Dawes <dawes@xfree86.org>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the names of Orest Zborowski and David Dawes 
 * not be used in advertising or publicity pertaining to distribution of 
 * the software without specific, written prior permission.  Orest Zborowski
 * and David Dawes make no representations about the suitability of this 
 * software for any purpose.  It is provided "as is" without express or 
 * implied warranty.
 *
 * OREST ZBOROWSKI AND DAVID DAWES DISCLAIMS ALL WARRANTIES WITH REGARD 
 * TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS, IN NO EVENT SHALL OREST ZBOROWSKI OR DAVID DAWES BE LIABLE 
 * FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES 
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN 
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF 
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */
/*
 * Copyright (c) 1994-2004 by The XFree86 Project, Inc.
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

#define NEED_EVENTS
#include <X11/X.h>

#include "compiler.h"

#include "xf86.h"
#include "xf86Priv.h"
#include "xf86_OSlib.h"

#define KBC_TIMEOUT 250        /* Timeout in ms for sending to keyboard controller */

#ifndef KBD_DIRECTHW
#define KBD_DIRECTHW 0
#endif

#if !(defined(__alpha__) || defined (__i386__) || defined(__ia64__))
#undef KBD_DIRECTHW
#define KBD_DIRECTHW 0
#endif

void
xf86SoundKbdBell(int loudness, int pitch, int duration)
{
	if (loudness && pitch)
	{
		ioctl(xf86Info.consoleFd, KDMKTONE,
		      ((1193190 / pitch) & 0xffff) |
		      (((unsigned long)duration *
			loudness / 50) << 16));
	}
}

void
xf86SetKbdLeds(int leds)
{
 	ioctl(xf86Info.consoleFd, KDSETLED, leds);
}

int
xf86GetKbdLeds()
{
	int leds = 0;

 	ioctl(xf86Info.consoleFd, KDGETLED, &leds);
	return(leds);
}

/* kbd rate stuff based on kbdrate.c from Rik Faith <faith@cs.unc.edu> et.al.
 * from util-linux-2.9t package */

#include <linux/kd.h>
#include <linux/version.h>
#ifdef __sparc__
#include <asm/param.h>
#include <asm/kbio.h>
#endif

/* Deal with spurious kernel header change */
#if defined(LINUX_VERSION_CODE) && defined(KERNEL_VERSION)
# if LINUX_VERSION_CODE >= KERNEL_VERSION(2,5,42)
#  define rate period
# endif
#endif

static int
KDKBDREP_ioctl_ok(int fd, int rate, int delay) {
#if defined(KDKBDREP) && !defined(__sparc__)
     /* This ioctl is defined in <linux/kd.h> but is not
	implemented anywhere - must be in some m68k patches. */
   struct kbd_repeat kbdrep_s;

   /* don't change, just test */
   kbdrep_s.rate = -1;
   kbdrep_s.delay = -1;
   if (ioctl( fd, KDKBDREP, &kbdrep_s )) {
       return 0;
   }

   /* do the change */
   if (rate == 0)				/* switch repeat off */
     kbdrep_s.rate = 0;
   else
     kbdrep_s.rate  = 10000 / rate;		/* convert cps to msec */
   if (kbdrep_s.rate < 1)
     kbdrep_s.rate = 1;
   kbdrep_s.delay = delay;
   if (kbdrep_s.delay < 1)
     kbdrep_s.delay = 1;
   
   if (ioctl( fd, KDKBDREP, &kbdrep_s )) {
     return 0;
   }

   return 1;			/* success! */
#else /* no KDKBDREP */
   return 0;
#endif /* KDKBDREP */
}

static int
KIOCSRATE_ioctl_ok(int rate, int delay) {
#ifdef KIOCSRATE
   struct kbd_rate kbdrate_s;
   int fd;

   fd = open("/dev/kbd", O_RDONLY);
   if (fd == -1) 
     return 0;   

   kbdrate_s.rate = (rate + 5) / 10;  /* must be integer, so round up */
   kbdrate_s.delay = delay * HZ / 1000;  /* convert ms to Hz */
   if (kbdrate_s.rate > 50)
     kbdrate_s.rate = 50;

   if (ioctl( fd, KIOCSRATE, &kbdrate_s ))
     return 0;

   close( fd );

   return 1;
#else /* no KIOCSRATE */
   return 0;
#endif /* KIOCSRATE */
}

#undef rate

void xf86SetKbdRepeat(char rad)
{
#ifdef __sparc__
  int         rate  = 500;     /* Default rate */
  int         delay = 200;     /* Default delay */
#else
  int         rate  = 300;     /* Default rate */
  int         delay = 250;     /* Default delay */
#endif

#if KBD_DIRECTHW
  int i;
  int timeout;
  int         value = 0x7f;    /* Maximum delay with slowest rate */

  static int valid_rates[] = { 300, 267, 240, 218, 200, 185, 171, 160, 150,
			       133, 120, 109, 100, 92, 86, 80, 75, 67,
			       60, 55, 50, 46, 43, 40, 37, 33, 30, 27,
			       25, 23, 21, 20 };
#define RATE_COUNT (sizeof( valid_rates ) / sizeof( int ))

  static int valid_delays[] = { 250, 500, 750, 1000 };
#define DELAY_COUNT (sizeof( valid_delays ) / sizeof( int ))
#endif

  if (xf86Info.kbdRate >= 0) 
    rate = xf86Info.kbdRate * 10;
  if (xf86Info.kbdDelay >= 0)
    delay = xf86Info.kbdDelay;


  if(KDKBDREP_ioctl_ok(xf86Info.consoleFd, rate, delay)) 	/* m68k? */
    return;

  if(KIOCSRATE_ioctl_ok(rate, delay))	/* sparc? */
    return;

  if (xf86IsPc98())
    return;

#if KBD_DIRECTHW

  /* The ioport way */

  for (i = 0; i < RATE_COUNT; i++)
    if (rate >= valid_rates[i]) {
      value &= 0x60;
      value |= i;
      break;
    }

  for (i = 0; i < DELAY_COUNT; i++)
    if (delay <= valid_delays[i]) {
      value &= 0x1f;
      value |= i << 5;
      break;
    }

  timeout = KBC_TIMEOUT;
  while (((inb(0x64) & 2) == 2) && --timeout)
       usleep(1000); /* wait */

  if (timeout == 0)
      return;

  outb(0x60, 0xf3);             /* set typematic rate */
  while (((inb(0x64) & 2) == 2) && --timeout)
       usleep(1000); /* wait */

  usleep(10000);
  outb(0x60, value);

#endif /* KBD_DIRECTHW */
}

static int kbdtrans;
static struct termios kbdtty;

void
xf86KbdInit()
{
	ioctl (xf86Info.consoleFd, KDGKBMODE, &kbdtrans);
	tcgetattr (xf86Info.consoleFd, &kbdtty);
}

int
xf86KbdOn()
{
	struct termios nTty;

#ifdef __powerpc__
	if (xf86Info.kbdCustomKeycodes)
		ioctl(xf86Info.consoleFd, KDSKBMODE, K_MEDIUMRAW);
	else
#endif
	ioctl(xf86Info.consoleFd, KDSKBMODE, K_RAW);

	nTty = kbdtty;
	nTty.c_iflag = (IGNPAR | IGNBRK) & (~PARMRK) & (~ISTRIP);
	nTty.c_oflag = 0;
	nTty.c_cflag = CREAD | CS8;
	nTty.c_lflag = 0;
	nTty.c_cc[VTIME]=0;
	nTty.c_cc[VMIN]=1;
	cfsetispeed(&nTty, 9600);
	cfsetospeed(&nTty, 9600);
	tcsetattr(xf86Info.consoleFd, TCSANOW, &nTty);
	return(xf86Info.consoleFd);
}

int
xf86KbdOff()
{
	ioctl(xf86Info.consoleFd, KDSKBMODE, kbdtrans);
	tcsetattr(xf86Info.consoleFd, TCSANOW, &kbdtty);
	return(xf86Info.consoleFd);
}

