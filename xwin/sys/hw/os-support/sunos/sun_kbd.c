/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/sunos/sun_kbd.c,v 1.5 2005/07/20 21:12:43 tsi Exp $ */
/*
 * Copyright 1990,91 by Thomas Roell, Dinkelscherben, Germany
 * Copyright 1993 by David Dawes <dawes@XFree86.org>
 * Copyright 1999 by David Holland <davidh@iquest.net)
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the names of Thomas Roell, David Dawes, and David Holland not be used
 * in advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.  Thomas Roell, David Dawes, and
 * David Holland make no representations about the suitability of this software
 * for any purpose.  It is provided "as is" without express or implied
 * warranty.
 *
 * THOMAS ROELL, DAVID DAWES, AND DAVID HOLLAND DISCLAIM ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL THOMAS ROELL, DAVID DAWES, OR DAVID HOLLAND
 * BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "xf86Priv.h"
#include "xf86_OSlib.h"
#include "xf86.h"

static int sun_otranslation = -1;
static int sun_odirect = -1;
int sun_ktype;

int
xf86GetKbdLeds()
{
	int leds;

	ioctl(xf86Info.kbdFd, KIOCGLED, &leds);
	return leds;
}

void
xf86SetKbdRepeat(char rad)
{
    /* Nothing to do */
}

/*
 * Save initial keyboard state.  This is called at the start of each server
 * generation.
 */

void
xf86KbdInit()
{
	const char *ktype_name;
	int	    klayout;

	if (xf86Info.kbdFd < 0) {
		xf86Info.kbdFd = open("/dev/kbd", O_RDWR|O_NONBLOCK);
		if(xf86Info.kbdFd < 0)
			FatalError("Unable to open keyboard: /dev/kbd.\n");
	}

	/*
	 * None of the following should ever fail.  If it does, something is
	 * broken (IMO) - DWH 8/21/99
	 */

	if (ioctl(xf86Info.kbdFd, KIOCTYPE, &sun_ktype) < 0)
		xf86Msg(X_ERROR,
			"Unable to determine keyboard type: %d.\n", errno);

	if (ioctl(xf86Info.kbdFd, KIOCLAYOUT, &klayout) < 0)
		xf86Msg(X_ERROR,
			"Unable to determine keyboard layout: %d.\n", errno);

	if (ioctl(xf86Info.kbdFd, KIOCGTRANS, &sun_otranslation) < 0)
		xf86Msg(X_ERROR,
			"Unable to determine keyboard translation mode.\n");

	if (ioctl(xf86Info.kbdFd, KIOCGDIRECT, &sun_odirect) < 0)
		xf86Msg(X_ERROR,
			"Unable to determine keyboard direct setting.\n");

	switch (sun_ktype) {
#ifdef KB_SUN3
	case KB_SUN3:
		ktype_name = "Sun Type 3";
		break;
#endif
#ifdef KB_SUN4
	case KB_SUN4:
		ktype_name = "Sun Type 4/5/6";
		break;
#endif
#ifdef KB_USB
	case KB_USB:
		ktype_name = "USB";
		break;
#endif
#ifdef KB_PC
	case KB_PC:
		ktype_name = "PC";
		break;
#endif
	default:
		ktype_name = "Unknown";
		break;
	}

	xf86Msg(X_PROBED, "Keyboard type: %s (%d)\n", ktype_name, sun_ktype);
	xf86Msg(X_PROBED, "Keyboard layout: %d\n", klayout);
}

int
xf86KbdOn(void)
{
	int	tmp = 1;

	if (ioctl(xf86Info.kbdFd, KIOCSDIRECT, &tmp) == -1)
		xf86Msg(X_ERROR, "Setting keyboard direct mode on.\n");

	/* Setup translation */

	tmp = TR_UNTRANS_EVENT;

	if (ioctl(xf86Info.kbdFd, KIOCTRANS, &tmp) == -1)
		xf86Msg(X_ERROR, "Setting keyboard translation.\n");

	return xf86Info.kbdFd;
}

int
xf86KbdOff()
{
	if ((sun_otranslation != -1) &&
	   (ioctl(xf86Info.kbdFd, KIOCTRANS, &sun_otranslation) < 0))
		xf86Msg(X_ERROR,
			"Unable to restore keyboard translation mode.\n");

	if ((sun_odirect != 0) &&
	   (ioctl(xf86Info.kbdFd, KIOCSDIRECT, &sun_odirect) < 0 ))
		xf86Msg(X_ERROR,
			"Unable to restore keyboard direct setting.\n");

	return xf86Info.kbdFd;
}
