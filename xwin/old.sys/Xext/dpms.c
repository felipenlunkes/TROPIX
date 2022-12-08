/*****************************************************************

Copyright (c) 1996 Digital Equipment Corporation, Maynard, Massachusetts.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
DIGITAL EQUIPMENT CORPORATION BE LIABLE FOR ANY CLAIM, DAMAGES, INCLUDING, 
BUT NOT LIMITED TO CONSEQUENTIAL OR INCIDENTAL DAMAGES, OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of Digital Equipment Corporation 
shall not be used in advertising or otherwise to promote the sale, use or other
dealings in this Software without prior written authorization from Digital 
Equipment Corporation.

******************************************************************/
/*
 * Copyright (c) 1996-2004 by The XFree86 Project, Inc.
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

/* $XFree86: xc/programs/Xserver/Xext/dpms.c,v 3.15 2005/10/14 15:16:11 tsi Exp $ */

#include <X11/X.h>
#include <X11/Xproto.h>
#include "misc.h"
#include "os.h"
#include "dixstruct.h"
#include "extnsionst.h"
#include "opaque.h"
#define DPMS_SERVER
#include <X11/extensions/dpms.h>
#include <X11/extensions/dpmsstr.h>
#include "dpmsproc.h"
#include "modinit.h"

#ifdef DPMSExtension
#if 0
static unsigned char DPMSCode;
#endif
static DISPATCH_PROC(ProcDPMSDispatch);
static DISPATCH_PROC(SProcDPMSDispatch);
static DISPATCH_PROC(ProcDPMSGetVersion);
static DISPATCH_PROC(SProcDPMSGetVersion);
static DISPATCH_PROC(ProcDPMSGetTimeouts);
static DISPATCH_PROC(SProcDPMSGetTimeouts);
static DISPATCH_PROC(ProcDPMSSetTimeouts);
static DISPATCH_PROC(SProcDPMSSetTimeouts);
static DISPATCH_PROC(ProcDPMSEnable);
static DISPATCH_PROC(SProcDPMSEnable);
static DISPATCH_PROC(ProcDPMSDisable);
static DISPATCH_PROC(SProcDPMSDisable);
static DISPATCH_PROC(ProcDPMSForceLevel);
static DISPATCH_PROC(SProcDPMSForceLevel);
static DISPATCH_PROC(ProcDPMSInfo);
static DISPATCH_PROC(SProcDPMSInfo);
static DISPATCH_PROC(ProcDPMSCapable);
static DISPATCH_PROC(SProcDPMSCapable);
static void DPMSResetProc(ExtensionEntry* extEntry);

void
DPMSExtensionInit(INITARGS)
{
#if 0
    ExtensionEntry *extEntry;
    
    if ((extEntry = AddExtension(DPMSExtensionName, 0, 0,
				ProcDPMSDispatch, SProcDPMSDispatch,
				DPMSResetProc, StandardMinorOpcode)))
	DPMSCode = (unsigned char)extEntry->base;
#else
    (void) AddExtension(DPMSExtensionName, 0, 0,
			ProcDPMSDispatch, SProcDPMSDispatch,
			DPMSResetProc, StandardMinorOpcode);
#endif
}

/*ARGSUSED*/
static void
DPMSResetProc(ExtensionEntry *extEntry)
{
}

static int
ProcDPMSGetVersion(ClientPtr client)
{
    /* REQUEST(xDPMSGetVersionReq); */
    xDPMSGetVersionReply rep;
    int n;

    REQUEST_SIZE_MATCH(xDPMSGetVersionReq);

    rep.type = X_Reply;
    rep.length = 0;
    rep.sequenceNumber = client->sequence;
    rep.majorVersion = DPMSMajorVersion;
    rep.minorVersion = DPMSMinorVersion;
    if (client->swapped) {
    	swaps(&rep.sequenceNumber, n);
	swaps(&rep.majorVersion, n);
	swaps(&rep.minorVersion, n);
    }
    WriteToClient(client, sizeof(xDPMSGetVersionReply), (char *)&rep);
    return(client->noClientException);
}

static int
ProcDPMSCapable(ClientPtr client)
{
    /* REQUEST(xDPMSCapableReq); */
    xDPMSCapableReply rep;
    int n;

    REQUEST_SIZE_MATCH(xDPMSCapableReq);

    rep.type = X_Reply;
    rep.length = 0;
    rep.sequenceNumber = client->sequence;
    rep.capable = DPMSCapableFlag;

    if (client->swapped) {
	swaps(&rep.sequenceNumber, n);
    }
    WriteToClient(client, sizeof(xDPMSCapableReply), (char *)&rep);
    return(client->noClientException);
}

static int
ProcDPMSGetTimeouts(ClientPtr client)
{
    /* REQUEST(xDPMSGetTimeoutsReq); */
    xDPMSGetTimeoutsReply rep;
    int n;

    REQUEST_SIZE_MATCH(xDPMSGetTimeoutsReq);

    rep.type = X_Reply;
    rep.length = 0;
    rep.sequenceNumber = client->sequence;
    rep.standby = DPMSStandbyTime / MILLI_PER_SECOND;
    rep.suspend = DPMSSuspendTime / MILLI_PER_SECOND;
    rep.off = DPMSOffTime / MILLI_PER_SECOND;

    if (client->swapped) {
    	swaps(&rep.sequenceNumber, n);
	swaps(&rep.standby, n);
	swaps(&rep.suspend, n);
	swaps(&rep.off, n);
    }
    WriteToClient(client, sizeof(xDPMSGetTimeoutsReply), (char *)&rep);
    return(client->noClientException);
}

static int
ProcDPMSSetTimeouts(ClientPtr client)
{
    REQUEST(xDPMSSetTimeoutsReq);

    REQUEST_SIZE_MATCH(xDPMSSetTimeoutsReq);

    if ((stuff->off != 0)&&(stuff->off < stuff->suspend)) 
    {
	client->errorValue = stuff->off;
	return BadValue;
    }
    if ((stuff->suspend != 0)&&(stuff->suspend < stuff->standby))
    {
	client->errorValue = stuff->suspend;
	return BadValue;
    }  
	
    DPMSStandbyTime = stuff->standby * MILLI_PER_SECOND;
    DPMSSuspendTime = stuff->suspend * MILLI_PER_SECOND;
    DPMSOffTime = stuff->off * MILLI_PER_SECOND;
    SetDPMSTimers();
    
    return(client->noClientException);
}

static int
ProcDPMSEnable(ClientPtr client)
{
    /* REQUEST(xDPMSEnableReq); */

    REQUEST_SIZE_MATCH(xDPMSEnableReq);

    if (DPMSCapableFlag)
	DPMSEnabled = TRUE;

    return(client->noClientException);
}

static int
ProcDPMSDisable(ClientPtr client)
{
    /* REQUEST(xDPMSDisableReq); */

    REQUEST_SIZE_MATCH(xDPMSDisableReq);

    DPMSSet(DPMSModeOn);

    DPMSEnabled = FALSE;

    return(client->noClientException);
}

static int
ProcDPMSForceLevel(ClientPtr client)
{
    REQUEST(xDPMSForceLevelReq);

    REQUEST_SIZE_MATCH(xDPMSForceLevelReq);

    if (!DPMSEnabled)
	return BadMatch;

    if (stuff->level == DPMSModeOn) {
      lastDeviceEventTime.milliseconds =
          GetTimeInMillis();
    } else if (stuff->level == DPMSModeStandby) {
      lastDeviceEventTime.milliseconds =
          GetTimeInMillis() -  DPMSStandbyTime;
    } else if (stuff->level == DPMSModeSuspend) {
      lastDeviceEventTime.milliseconds =
          GetTimeInMillis() -  DPMSSuspendTime;
    } else if (stuff->level == DPMSModeOff) {
      lastDeviceEventTime.milliseconds =
          GetTimeInMillis() -  DPMSOffTime;
    } else {
	client->errorValue = stuff->level;
	return BadValue;
    }

    DPMSSet(stuff->level);

    return(client->noClientException);
}

static int
ProcDPMSInfo(ClientPtr client)
{
    /* REQUEST(xDPMSInfoReq); */
    xDPMSInfoReply rep;
    int n;

    REQUEST_SIZE_MATCH(xDPMSInfoReq);

    rep.type = X_Reply;
    rep.length = 0;
    rep.sequenceNumber = client->sequence;
    rep.power_level = DPMSPowerLevel;
    rep.state = DPMSEnabled;

    if (client->swapped) {
    	swaps(&rep.sequenceNumber, n);
	swaps(&rep.power_level, n);
    }
    WriteToClient(client, sizeof(xDPMSInfoReply), (char *)&rep);
    return(client->noClientException);
}

static int
ProcDPMSDispatch(ClientPtr client)
{
    REQUEST(xReq);

    switch (stuff->data)
    {
    case X_DPMSGetVersion:
	return ProcDPMSGetVersion(client);
    case X_DPMSCapable:
	return ProcDPMSCapable(client);
    case X_DPMSGetTimeouts:
	return ProcDPMSGetTimeouts(client);
    case X_DPMSSetTimeouts:
	return ProcDPMSSetTimeouts(client);
    case X_DPMSEnable:
	return ProcDPMSEnable(client);
    case X_DPMSDisable:
	return ProcDPMSDisable(client);
    case X_DPMSForceLevel:
	return ProcDPMSForceLevel(client);
    case X_DPMSInfo:
	return ProcDPMSInfo(client);
    default:
	return BadRequest;
    }
}

static int
SProcDPMSGetVersion(ClientPtr client)
{
    int n;
    REQUEST(xDPMSGetVersionReq);

    swaps(&stuff->length, n);
    REQUEST_SIZE_MATCH(xDPMSGetVersionReq);
    swaps(&stuff->majorVersion, n);
    swaps(&stuff->minorVersion, n);
    return ProcDPMSGetVersion(client);
}

static int
SProcDPMSCapable(ClientPtr client)
{
    REQUEST(xDPMSCapableReq);
    int n;

    swaps(&stuff->length, n);
    REQUEST_SIZE_MATCH(xDPMSCapableReq);

    return ProcDPMSCapable(client);
}

static int
SProcDPMSGetTimeouts(ClientPtr client)
{
    REQUEST(xDPMSGetTimeoutsReq);
    int n;

    swaps(&stuff->length, n);
    REQUEST_SIZE_MATCH(xDPMSGetTimeoutsReq);

    return ProcDPMSGetTimeouts(client);
}

static int
SProcDPMSSetTimeouts(ClientPtr client)
{
    REQUEST(xDPMSSetTimeoutsReq);
    int n;

    swaps(&stuff->length, n);
    REQUEST_SIZE_MATCH(xDPMSSetTimeoutsReq);

    swaps(&stuff->standby, n);
    swaps(&stuff->suspend, n);
    swaps(&stuff->off, n);
    return ProcDPMSSetTimeouts(client);
}

static int
SProcDPMSEnable(ClientPtr client)
{
    REQUEST(xDPMSEnableReq);
    int n;

    swaps(&stuff->length, n);
    REQUEST_SIZE_MATCH(xDPMSEnableReq);

    return ProcDPMSEnable(client);
}

static int
SProcDPMSDisable(ClientPtr client)
{
    REQUEST(xDPMSDisableReq);
    int n;

    swaps(&stuff->length, n);
    REQUEST_SIZE_MATCH(xDPMSDisableReq);

    return ProcDPMSDisable(client);
}

static int
SProcDPMSForceLevel(ClientPtr client)
{
    REQUEST(xDPMSForceLevelReq);
    int n;

    swaps(&stuff->length, n);
    REQUEST_SIZE_MATCH(xDPMSForceLevelReq);

    swaps(&stuff->level, n);

    return ProcDPMSForceLevel(client);
}

static int
SProcDPMSInfo(ClientPtr client)
{
    REQUEST(xDPMSInfoReq);
    int n;

    swaps(&stuff->length, n);
    REQUEST_SIZE_MATCH(xDPMSInfoReq);

    return ProcDPMSInfo(client);
}

static int
SProcDPMSDispatch(ClientPtr client)
{
    REQUEST(xReq);
    switch (stuff->data)
    {
    case X_DPMSGetVersion:
	return SProcDPMSGetVersion(client);
    case X_DPMSCapable:
	return SProcDPMSCapable(client);
    case X_DPMSGetTimeouts:
	return SProcDPMSGetTimeouts(client);
    case X_DPMSSetTimeouts:
	return SProcDPMSSetTimeouts(client);
    case X_DPMSEnable:
	return SProcDPMSEnable(client);
    case X_DPMSDisable:
	return SProcDPMSDisable(client);
    case X_DPMSForceLevel:
	return SProcDPMSForceLevel(client);
    case X_DPMSInfo:
	return SProcDPMSInfo(client);
    default:
	return BadRequest;
    }
}
#endif
