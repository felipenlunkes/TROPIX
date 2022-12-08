/* $XFree86: xc/programs/Xserver/include/os.h,v 3.71 2007/04/03 00:21:13 tsi Exp $ */
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

#ifndef OS_H
#define OS_H

#include "misc.h"
#define ALLOCATE_LOCAL_FALLBACK(_size) Xalloc((unsigned long)(_size))
#define DEALLOCATE_LOCAL_FALLBACK(_ptr) Xfree((pointer)(_ptr))
#include <X11/Xalloca.h>
#ifndef IN_MODULE
#include <stdarg.h>
#else
#include "xf86_ansic.h"
#endif

#define NullFID ((FID) 0)

#define SCREEN_SAVER_ON   0
#define SCREEN_SAVER_OFF  1
#define SCREEN_SAVER_FORCER 2
#define SCREEN_SAVER_CYCLE  3

#ifndef MAX_REQUEST_SIZE
#define MAX_REQUEST_SIZE 65535
#endif
#ifndef MAX_BIG_REQUEST_SIZE
#define MAX_BIG_REQUEST_SIZE 4194303
#endif

/*
 * Verbosity level used for log functions where the verbosity isn't
 * specified explicitly.
 */
#ifndef X_LOG_DEFAULT_VERB
#define X_LOG_DEFAULT_VERB 1
#endif

typedef pointer	FID;
typedef struct _FontPathRec *FontPathPtr;
typedef struct _NewClientRec *NewClientPtr;

#ifndef xalloc
#define xnfalloc(size) XNFalloc((unsigned long)(size))
#define xnfcalloc(_num, _size) XNFcalloc((unsigned long)(_num)*(unsigned long)(_size))
#define xnfrealloc(ptr, size) XNFrealloc((pointer)(ptr), (unsigned long)(size))

#define xalloc(size) Xalloc((unsigned long)(size))
#define xcalloc(_num, _size) Xcalloc((unsigned long)(_num)*(unsigned long)(_size))
#define xrealloc(ptr, size) Xrealloc((pointer)(ptr), (unsigned long)(size))
#define xfree(ptr) Xfree((pointer)(ptr))
#define xstrdup(s) Xstrdup(s)
#define xnfstrdup(s) XNFstrdup(s)
#define xasprintf Xasprintf
#endif

#ifndef IN_MODULE
#ifdef __SCO__
#include <stdio.h>
#endif
#include <string.h>
#endif

/* have to put $(SIGNAL_DEFINES) in DEFINES in Imakefile to get this right */
#ifdef SIGNALRETURNSINT
#define SIGVAL int
#else
#define SIGVAL void
#endif

extern Bool OsDelayInitColors;
extern void (*OsVendorVErrorFProc)(const char *, va_list args);

extern int WaitForSomething(
    int* /*pClientsReady*/
);

#ifdef LBX
#define ReadRequestFromClient(client)   ((client)->readRequest(client))
extern int StandardReadRequestFromClient(ClientPtr /*client*/);

extern int ClientConnectionNumber(ClientPtr /*client*/);
#else
extern int ReadRequestFromClient(ClientPtr /*client*/);
#endif /* LBX */

extern Bool InsertFakeRequest(
    ClientPtr /*client*/, 
    char* /*data*/, 
    int /*count*/);

extern void ResetCurrentRequest(ClientPtr /*client*/);

extern void FlushAllOutput(void);

extern void FlushIfCriticalOutputPending(void);

extern void SetCriticalOutputPending(void);

extern int WriteToClient(ClientPtr /*who*/, int /*count*/, char* /*buf*/);

extern void ResetOsBuffers(void);

extern void InitConnectionLimits(void);

extern void CreateWellKnownSockets(void);

extern void ResetWellKnownSockets(void);

extern void CloseWellKnownConnections(void);

extern XID AuthorizationIDOfClient(ClientPtr /*client*/);

extern char *ClientAuthorized(
    ClientPtr /*client*/,
    unsigned int /*proto_n*/,
    char* /*auth_proto*/,
    unsigned int /*string_n*/,
    char* /*auth_string*/);

extern Bool EstablishNewConnections(
    ClientPtr /*clientUnused*/,
    pointer /*closure*/);

extern void CheckConnections(void);

extern void CloseDownConnection(ClientPtr /*client*/);

extern void AddEnabledDevice(int /*fd*/);

extern void RemoveEnabledDevice(int /*fd*/);

extern void OnlyListenToOneClient(ClientPtr /*client*/);

extern void ListenToAllClients(void);

extern void IgnoreClient(ClientPtr /*client*/);

extern void AttendClient(ClientPtr /*client*/);

extern void MakeClientGrabImpervious(ClientPtr /*client*/);

extern void MakeClientGrabPervious(ClientPtr /*client*/);

#ifdef LBX
extern void CloseDownFileDescriptor(ClientPtr /* client */);
#endif

extern void AvailableClientInput(ClientPtr /* client */);

extern CARD32 GetTimeInMillis(void);

extern void AdjustWaitForDelay(
    pointer /*waitTime*/,
    unsigned long /*newdelay*/);

typedef	struct _OsTimerRec *OsTimerPtr;

typedef CARD32 (*OsTimerCallback)(
    OsTimerPtr /* timer */,
    CARD32 /* time */,
    pointer /* arg */);

extern void TimerInit(void);

extern Bool TimerForce(OsTimerPtr /* timer */);

#define TimerAbsolute (1<<0)
#define TimerForceOld (1<<1)

extern OsTimerPtr TimerSet(
    OsTimerPtr /* timer */,
    int /* flags */,
    CARD32 /* millis */,
    OsTimerCallback /* func */,
    pointer /* arg */);

extern void TimerCheck(void);
extern void TimerCancel(OsTimerPtr /* pTimer */);
extern void TimerFree(OsTimerPtr /* pTimer */);

extern void SetScreenSaverTimer(void);
extern void FreeScreenSaverTimer(void);

#ifdef DPMSExtension
extern void SetDPMSTimers(void);
extern void FreeDPMSTimers(void);
#endif

#ifdef __GNUC__
#define NORET __attribute__((noreturn))
#else
#define NORET /**/
#endif

extern SIGVAL AutoResetServer(int /*sig*/);

#ifdef	TROPIX
extern SIGVAL GiveUp(int, ...);
#else
extern SIGVAL GiveUp(int /*sig*/);
#endif	TROPIX

extern SIGVAL AbortServer(int /*sig*/) NORET;


extern void UseMsg(void);

extern void ProcessCommandLine(const int /*argc*/, const char* /*argv*/[]);

extern int set_font_authorizations(
    char ** /* authorizations */, 
    int * /*authlen */, 
    pointer /* client */);

#ifndef _HAVE_XALLOC_DECLS
#define _HAVE_XALLOC_DECLS
extern pointer Xalloc(unsigned long /*amount*/);
extern pointer Xcalloc(unsigned long /*amount*/);
extern pointer Xrealloc(pointer /*ptr*/, unsigned long /*amount*/);
#if !defined(WORD64) && !defined(LONG64)
extern pointer Xllalloc(unsigned long long /*amount*/);
extern pointer Xllrealloc(pointer, unsigned long long /*amount*/);
extern pointer Xllcalloc(unsigned long long /*amount*/);
#endif
extern void Xfree(pointer /*ptr*/);
#endif

extern pointer XNFalloc(unsigned long /*amount*/);
extern pointer XNFcalloc(unsigned long /*amount*/);
extern pointer XNFrealloc(pointer /*ptr*/, unsigned long /*amount*/);

extern void OsInitAllocator(void);

extern char *Xstrdup(const char *s);
extern char *XNFstrdup(const char *s);

#ifdef	TROPIX
typedef void (*OsSigHandlerPtr)(int,...);
#else
typedef SIGVAL (*OsSigHandlerPtr)(int /* sig */);
#endif	TROPIX

extern OsSigHandlerPtr OsSignal(int /* sig */, OsSigHandlerPtr /* handler */);

extern int auditTrailLevel;

#ifdef SERVER_LOCK
extern void LockServer(void);
extern void UnlockServer(void);
#endif

extern int OsLookupColor(
    int	/*screen*/,
    char * /*name*/,
    unsigned /*len*/,
    unsigned short * /*pred*/,
    unsigned short * /*pgreen*/,
    unsigned short * /*pblue*/);

extern void OsInit(void);

extern void OsCleanup(Bool);
extern void OsPrepareShutdown(Bool);
extern void OsPrepareRestart(void);

extern void OsVendorFatalError(void);

extern void OsVendorPreInit(void);
extern void OsVendorInit(void);

extern int OsInitColors(void);

void OsBlockSignals (void);

void OsReleaseSignals (void);

#if !defined(WIN32) && !defined(__UNIXOS2__)
extern int System(const char *);
extern pointer Popen(const char *, const char *);
extern int Pclose(pointer);
extern pointer Fopen(const char *, const char *);
extern int Fclose(pointer);
#else
#define System(a) system(a)
#define Popen(a,b) popen(a,b)
#define Pclose(a) pclose(a)
#define Fopen(a,b) fopen(a,b)
#define Fclose(a) fclose(a)
#endif

extern void CheckUserParameters(const int argc, const char **argv, char **envp);
extern void CheckUserAuthorization(void);

extern int AddHost(
    ClientPtr	/*client*/,
    int         /*family*/,
    unsigned    /*length*/,
    pointer     /*pAddr*/);

extern Bool ForEachHostInFamily (
    int	    /*family*/,
    Bool    (* /*func*/ )(
            unsigned char * /* addr */,
            short           /* len */,
            pointer         /* closure */),
    pointer /*closure*/);

extern int RemoveHost(
    ClientPtr	/*client*/,
    int         /*family*/,
    unsigned    /*length*/,
    pointer     /*pAddr*/);

extern int GetHosts(
    pointer * /*data*/,
    int	    * /*pnHosts*/,
    int	    * /*pLen*/,
    BOOL    * /*pEnabled*/);

typedef struct sockaddr * sockaddrPtr;

extern int InvalidHost(sockaddrPtr /*saddr*/, int /*len*/);

extern int LocalClient(ClientPtr /* client */);

extern int LocalClientCred(ClientPtr, int *, int *);

extern int ChangeAccessControl(ClientPtr /*client*/, int /*fEnabled*/);

extern int GetAccessControl(void);


extern void AddLocalHosts(void);

extern void ResetHosts(const char *display);

extern void EnableLocalHost(void);

extern void DisableLocalHost(void);

extern void AccessUsingXdmcp(void);

extern void DefineSelf(int /*fd*/);

extern void AugmentSelf(pointer /*from*/, int /*len*/);

extern void InitAuthorization(const char * /*filename*/);

/* extern int LoadAuthorization(void); */

extern void RegisterAuthorizations(void);

extern XID AuthorizationToID (
	unsigned short	name_length,
	char		*name,
	unsigned short	data_length,
	char		*data);

extern int AuthorizationFromID (
	XID 		id,
	unsigned short	*name_lenp,
	char		**namep,
	unsigned short	*data_lenp,
	char		**datap);

extern XID CheckAuthorization(
    unsigned int /*namelength*/,
    char * /*name*/,
    unsigned int /*datalength*/,
    char * /*data*/,
    ClientPtr /*client*/,
    char ** /*reason*/
);

extern void ResetAuthorization(void);

extern int RemoveAuthorization (
    unsigned short	name_length,
    char		*name,
    unsigned short	data_length,
    char		*data);

extern int AddAuthorization(
    unsigned int	/*name_length*/,
    char *		/*name*/,
    unsigned int	/*data_length*/,
    char *		/*data*/);

extern XID GenerateAuthorization(
    unsigned int   /* name_length */,
    char	*  /* name */,
    unsigned int   /* data_length */,
    char	*  /* data */,
    unsigned int * /* data_length_return */,
    char	** /* data_return */);

#ifdef COMMANDLINE_CHALLENGED_OPERATING_SYSTEMS
extern void ExpandCommandLine(int * /*pargc*/, char *** /*pargv*/);
#endif

extern int ddxProcessArgument(int /*argc*/, const char * /*argv*/ [], int /*i*/);

extern void ddxUseMsg(void);

/*
 *  idiom processing stuff
 */

extern xReqPtr PeekNextRequest(xReqPtr req, ClientPtr client, Bool readmore);

extern void SkipRequests(xReqPtr req, ClientPtr client, int numskipped);

/* int ReqLen(xReq *req, ClientPtr client)
 * Given a pointer to a *complete* request, return its length in bytes.
 * Note that if the request is a big request (as defined in the Big
 * Requests extension), the macro lies by returning 4 less than the
 * length that it actually occupies in the request buffer.  This is so you
 * can blindly compare the length with the various sz_<request> constants
 * in Xproto.h without having to know/care about big requests.
 */
#define ReqLen(_pxReq, _client) \
 ((_pxReq->length ? \
     (_client->swapped ? lswaps(_pxReq->length) : _pxReq->length) \
  : ((_client->swapped ? \
	lswapl(((CARD32*)_pxReq)[1]) : ((CARD32*)_pxReq)[1])-1) \
  ) << 2)

/* otherReqTypePtr CastxReq(xReq *req, otherReqTypePtr)
 * Cast the given request to one of type otherReqTypePtr to access
 * fields beyond the length field.
 */
#define CastxReq(_pxReq, otherReqTypePtr) \
    (_pxReq->length ? (otherReqTypePtr)_pxReq \
		    : (otherReqTypePtr)(((CARD32*)_pxReq)+1))

/* stuff for SkippedRequestsCallback */
extern CallbackListPtr SkippedRequestsCallback;
typedef struct {
    xReqPtr req;
    ClientPtr client;
    int numskipped;
} SkippedRequestInfoRec;

/* stuff for ReplyCallback */
extern CallbackListPtr ReplyCallback;
typedef struct {
    ClientPtr client;
    pointer replyData;
    unsigned long dataLenBytes;
    unsigned long bytesRemaining;
    Bool startOfReply;
} ReplyInfoRec;

/* stuff for FlushCallback */
extern CallbackListPtr FlushCallback;

extern void AbortDDX(void);
extern void ddxGiveUp(void);
extern int TimeSinceLastInputEvent(void);

/* Logging. */
typedef enum _LogParameter {
    XLOG_FLUSH,
    XLOG_SYNC,
    XLOG_VERBOSITY,
    XLOG_FILE_VERBOSITY
} LogParameter;

/* Flags for log messages. */
typedef enum {
    X_PROBED,			/* Value was probed */
    X_CONFIG,			/* Value was given in the config file */
    X_DEFAULT,			/* Value is a default */
    X_CMDLINE,			/* Value was given on the command line */
    X_NOTICE,			/* Notice */
    X_ERROR,			/* Error message */
    X_WARNING,			/* Warning message */
    X_INFO,			/* Informational message */
    X_NONE,			/* No prefix */
    X_NOT_IMPLEMENTED,		/* Not implemented */
    X_UNKNOWN = -1		/* unknown -- this must always be last */
} MessageType;

/* XXX Need to check which GCC versions have the format(printf) attribute. */
#if (!defined(printf) || defined(printf_is_xf86printf)) && \
    defined(__GNUC__) && \
    ((__GNUC__ > 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ > 4)))
# define _printf_attribute(a,b) __attribute((format(printf,a,b)))
# undef printf
#else
# define _printf_attribute(a,b) /**/
#endif

extern const char *LogInit(const char *fname, const char *backup);
extern void LogClose(void);
extern Bool LogSetParameter(LogParameter param, int value);
extern void LogVWrite(int verb, const char *f, va_list args);
extern void LogWrite(int verb, const char *f, ...) _printf_attribute(2,3);
extern void LogVMessageVerb(MessageType type, int verb, const char *format,
			    va_list args);
extern void LogMessageVerb(MessageType type, int verb, const char *format,
			   ...) _printf_attribute(3,4);
extern void LogMessage(MessageType type, const char *format, ...)
			_printf_attribute(2,3);
extern void FreeAuditTimer(void);
extern void AuditF(const char *f, ...) _printf_attribute(1,2);
extern void VAuditF(const char *f, va_list args);
extern void FatalError(const char *f, ...) _printf_attribute(1,2)
#if defined(__GNUC__) && \
    ((__GNUC__ > 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ > 4)))
__attribute((noreturn))
#endif
;

#ifdef __GNUC__
#define FatalAlloc()	FatalError("Out of Memory: %s() %s:%d", __FUNCTION__, __FILE__, __LINE__); 
#else
#define FatalAlloc()	FatalError("Out of Memory: %s:%d", __FILE__, __LINE__); 
#endif

extern void VErrorF(const char *f, va_list args);
extern void ErrorF(const char *f, ...) _printf_attribute(1,2);
extern void Error(char *str);
extern const char *LogTypeToTxt(MessageType type);
extern void LogPrintMarkers(void);

#ifndef IN_MODULE
#if defined(NEED_SNPRINTF)
extern int snprintf(char *str, size_t size, const char *format, ...)
	_printf_attribute(3,4);
extern int vsnprintf(char *str, size_t size, const char *format, va_list ap);
#endif
#if defined(NEED_STRLCAT)
#include "strlcat.h"
#include "strlcpy.h"
#endif
#endif

/* utils.c */
extern int Xasprintf(char **ret, const char *format, ...)
	_printf_attribute(2,3);

#undef _printf_attribute
#if defined(printf_is_xf86printf) && !defined(printf)
#define printf xf86printf
#endif

extern int getArgc(void);
extern const char **getArgvp(void);
extern const char *getArgv(int i);

#ifdef __DARWIN__
extern void DarwinHandleGUI(int argc, const char *argv[], char *envp[]);
#endif

#endif /* OS_H */
