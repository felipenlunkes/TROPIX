/* $XFree86: xc/programs/Xserver/Xext/extmod/modinit.h,v 1.6 2007/01/04 02:48:11 tsi Exp $ */

#include "extnsionst.h"

#ifdef SHAPE
extern void ShapeExtensionInit(INITARGS);
#define _SHAPE_SERVER_  /* don't want Xlib structures */
#include <X11/extensions/shapestr.h>
#endif

#ifdef MULTIBUFFER
extern void MultibufferExtensionInit(INITARGS);
#define _MULTIBUF_SERVER_	/* don't want Xlib structures */
#include <X11/extensions/multibufst.h>
#endif

#ifdef MITMISC
extern void MITMiscExtensionInit(INITARGS);
#define _MITMISC_SERVER_
#include <X11/extensions/mitmiscstr.h>
#endif

#ifdef XTEST
extern void XTestExtensionInit(INITARGS);
#define _XTEST_SERVER_
#include <X11/extensions/XTest.h>
#include <X11/extensions/xteststr.h>
#endif

#if 1
extern void XTestExtension1Init(INITARGS);
#endif

#ifdef BIGREQS
extern void BigReqExtensionInit(INITARGS);
#include <X11/extensions/bigreqstr.h>
#endif

#ifdef XSYNC
extern void SyncExtensionInit(INITARGS);
#define _SYNC_SERVER
#include <X11/extensions/sync.h>
#include <X11/extensions/syncstr.h>
#endif

#ifdef SCREENSAVER
extern void ScreenSaverExtensionInit (INITARGS);
#include <X11/extensions/saver.h>
#endif

#ifdef XCMISC
extern void XCMiscExtensionInit(INITARGS);
#include <X11/extensions/xcmiscstr.h>
#endif

#ifdef XF86VIDMODE
extern void XFree86VidModeExtensionInit(INITARGS);
#define _XF86VIDMODE_SERVER_
#include <X11/extensions/xf86vmstr.h>
#endif

#ifdef XF86MISC
extern void XFree86MiscExtensionInit(INITARGS);
#define _XF86MISC_SERVER_
#define _XF86MISC_SAVER_COMPAT_
#include <X11/extensions/xf86mscstr.h>
#endif

#ifdef XFreeXDGA
extern void XFree86DGAExtensionInit(INITARGS);
extern void XFree86DGARegister(INITARGS);
#define _XF86DGA_SERVER_
#include <X11/extensions/xf86dgastr.h>
#endif

#ifdef DPMSExtension
extern void DPMSExtensionInit(INITARGS);
#include <X11/extensions/dpmsstr.h>
#endif

#ifdef FONTCACHE
extern void FontCacheExtensionInit(INITARGS);
#define _FONTCACHE_SERVER_
#include <X11/extensions/fontcacheP.h>
#include <X11/extensions/fontcachstr.h>
#endif

#ifdef TOGCUP
extern void XcupExtensionInit(INITARGS);
#define _XCUP_SERVER_
#include <X11/extensions/Xcupstr.h>
#endif

#ifdef EVI
extern void EVIExtensionInit(INITARGS);
#define _XEVI_SERVER_
#include <X11/extensions/XEVIstr.h>
#endif

#ifdef XV
extern void XvExtensionInit(INITARGS);
extern void XvRegister(INITARGS);
#include <X11/extensions/Xv.h>
#endif
#ifdef XVMC
extern void XvMCExtensionInit(INITARGS);
#include <X11/extensions/XvMC.h>
#endif

#ifdef RES
extern void ResExtensionInit(INITARGS);
#include <X11/extensions/XResproto.h>
#endif

#ifdef MITSHM
extern void ShmExtensionInit(INITARGS);
#define _XSHM_SERVER_
#include <X11/extensions/shmstr.h>
extern void ShmSetPixmapFormat(
    ScreenPtr pScreen,
    int format);
#endif

#if 1
extern void SecurityExtensionInit(INITARGS);
#endif

#if 1
extern void XagExtensionInit(INITARGS);
#endif

#if 1
extern void XpExtensionInit(INITARGS);
#endif

#if 1
extern void PanoramiXExtensionInit(INITARGS);
#endif

#if 1
extern void XkbExtensionInit(INITARGS);
#endif
