/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/xgi/vgatypes.h,v 1.1 2005/05/02 13:28:02 dawes Exp $ */
/*
 * General type definitions for universal mode switching modules
 *
 * Copyright (C) 2001-2004 by Thomas Winischhofer, Vienna, Austria
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License as published by
 * * the Free Software Foundation; either version 2 of the named License,
 * * or any later version.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) The name of the author may not be used to endorse or promote products
 * *    derived from this software without specific prior written permission.
 * *
 * * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESSED OR
 * * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: 	Thomas Winischhofer <thomas@winischhofer.net>
 *
 */

#ifndef _VGATYPES_
#define _VGATYPES_

#ifdef LINUX_XF86
#include "xf86Version.h"
#include "xf86Pci.h"
#endif

#ifdef LINUX_KERNEL  /* We don't want the X driver to depend on kernel source */
#include <linux/ioctl.h>
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef NULL
#define NULL    0
#endif

#ifndef CHAR
typedef char CHAR;
#endif

#ifndef SHORT
typedef short SHORT;
#endif

#ifndef LONG
typedef long  LONG;
#endif

#ifndef UCHAR
typedef unsigned char UCHAR;
#endif

#ifndef USHORT
typedef unsigned short USHORT;
#endif

#ifndef ULONG
typedef unsigned long ULONG;
#endif

#ifndef PUCHAR
typedef UCHAR *PUCHAR;
#endif

#ifndef PUSHORT
typedef USHORT *PUSHORT;
#endif

#ifndef PLONGU
typedef ULONG *PULONG;
#endif

#ifndef VOID
typedef void VOID;
#endif

#ifndef PVOID
typedef void *PVOID;
#endif

#ifndef BOOLEAN
typedef UCHAR BOOLEAN;
#endif

#ifndef bool
typedef UCHAR bool;
#endif

#ifdef LINUX_KERNEL
typedef unsigned long XGIIOADDRESS;
#endif

#ifdef LINUX_XF86
#if XF86_VERSION_CURRENT < XF86_VERSION_NUMERIC(4,2,0,0,0)
typedef unsigned char IOADDRESS;
typedef unsigned char XGIIOADDRESS;
#else
typedef IOADDRESS XGIIOADDRESS;
#endif
#endif

#ifndef VBIOS_VER_MAX_LENGTH
#define VBIOS_VER_MAX_LENGTH    4
#endif

#ifndef LINUX_KERNEL   /* For the linux kernel, this is defined in xgifb.h */
#ifndef XGI_CHIP_TYPE
typedef enum _XGI_CHIP_TYPE {
    XGI_VGALegacy = 0,
#ifdef LINUX_XF86
    XGI_530,
    XGI_OLD,
#endif
    XGI_300,
    XGI_630,
    XGI_640,
    XGI_315H,
    XGI_315,
    XGI_315PRO,
    XGI_550,
    XGI_650,
    XGI_650M,
    XGI_740,
    XGI_330,
    XGI_661,
    XGI_660,
    XGI_760,
    XG40 = 32,
    XG41,
    XG42,
    XG45,
    XG20 = 48,
    MAX_XGI_CHIP
} XGI_CHIP_TYPE;
#endif
#endif

#ifndef XGI_VB_CHIP_TYPE
typedef enum _XGI_VB_CHIP_TYPE {
    VB_CHIP_Legacy = 0,
    VB_CHIP_301,
    VB_CHIP_301B,
    VB_CHIP_301LV,
    VB_CHIP_302,
    VB_CHIP_302B,
    VB_CHIP_302LV,
    VB_CHIP_301C,
    VB_CHIP_302ELV,
    VB_CHIP_UNKNOWN, /* other video bridge or no video bridge */
    MAX_VB_CHIP
} XGI_VB_CHIP_TYPE;
#endif

#ifndef XGI_LCD_TYPE
typedef enum _XGI_LCD_TYPE {
    LCD_INVALID = 0,
    LCD_800x600,
    LCD_1024x768,
    LCD_1280x1024,
    LCD_1280x960,
    LCD_640x480,
    LCD_1600x1200,
    LCD_1920x1440,
    LCD_2048x1536,
    LCD_320x480,       /* FSTN, DSTN */
    LCD_1400x1050,
    LCD_1152x864,
    LCD_1152x768,
    LCD_1280x768,
    LCD_1024x600,
    LCD_640x480_2,     /* FSTN, DSTN */
    LCD_640x480_3,     /* FSTN, DSTN */
    LCD_848x480,
    LCD_1280x800,
    LCD_1680x1050,
    LCD_1280x720,
    LCD_CUSTOM,
    LCD_UNKNOWN
} XGI_LCD_TYPE;
#endif

#ifndef PXGI_DSReg
typedef struct _XGI_DSReg
{
  UCHAR  jIdx;
  UCHAR  jVal;
} XGI_DSReg, *PXGI_DSReg;
#endif

#ifndef XGI_HW_DEVICE_INFO

typedef struct _XGI_HW_DEVICE_INFO  XGI_HW_DEVICE_INFO, *PXGI_HW_DEVICE_INFO;

typedef BOOLEAN (*PXGI_QUERYSPACE)   (PXGI_HW_DEVICE_INFO, ULONG, ULONG, ULONG *);

struct _XGI_HW_DEVICE_INFO
{
    ULONG  ulExternalChip;       /* NO VB or other video bridge*/
                                 /* if ujVBChipID = VB_CHIP_UNKNOWN, */
#ifdef LINUX_XF86
    PCITAG PciTag;		 /* PCI Tag */
#endif

    PUCHAR  pjVirtualRomBase;    /* ROM image */

    BOOLEAN UseROM;		 /* Use the ROM image if provided */

    PVOID   pDevice;

    PUCHAR  pjVideoMemoryAddress;/* base virtual memory address */
                                 /* of Linear VGA memory */

    ULONG  ulVideoMemorySize;    /* size, in bytes, of the memory on the board */

    PUCHAR pjCustomizedROMImage;

/*    PUCHAR pj2ndIOAddress; */
    ULONG  pj2ndIOAddress;

    XGIIOADDRESS pjIOAddress;    /* base I/O address of VGA ports (0x3B0) */

    UCHAR  jChipType;            /* Used to Identify Graphics Chip */
                                 /* defined in the data structure type  */
                                 /* "XGI_CHIP_TYPE" */

    UCHAR  jChipRevision;        /* Used to Identify Graphics Chip Revision */

    UCHAR  ujVBChipID;           /* the ID of video bridge */
                                 /* defined in the data structure type */
                                 /* "XGI_VB_CHIP_TYPE" */
/*
#ifdef LINUX_KERNEL
    BOOLEAN Is301BDH;
    ULONG  ulCRT2LCDType;        / * defined in the data structure type * /
                                 / * "XGI_LCD_TYPE" * /
#endif
*/
    ULONG  ulCRT2LCDType;        /* defined in the data structure type */

    ULONG usExternalChip;       /* NO VB or other video bridge (other than  */
                                 /*  video bridge) */

    BOOLEAN bIntegratedMMEnabled;/* supporting integration MM enable */

    BOOLEAN bSkipDramSizing;     /* True: Skip video memory sizing. */

    BOOLEAN bSkipSense;
/*
#ifdef LINUX_KERNEL
*/
    PXGI_DSReg  pSR;             /* restore SR registers in initial function. */
                                 /* end data :(idx, val) =  (FF, FF). */
                                 /* Note : restore SR registers if  */
                                 /* bSkipDramSizing = TRUE */

    PXGI_DSReg  pCR;             /* restore CR registers in initial function. */
                                 /* end data :(idx, val) =  (FF, FF) */
                                 /* Note : restore cR registers if  */
                                 /* bSkipDramSizing = TRUE */
/*
#endif
*/

    PXGI_QUERYSPACE  pQueryVGAConfigSpace;

    PXGI_QUERYSPACE  pQueryNorthBridgeSpace;

    UCHAR  szVBIOSVer[VBIOS_VER_MAX_LENGTH];

};
#endif

/* Addtional IOCTL for communication xgifb <> X driver        */
/* If changing this, xgifb.h must also be changed (for xgifb) */

#ifdef LINUX_XF86  /* We don't want the X driver to depend on the kernel source */

/* ioctl for identifying and giving some info (esp. memory heap start) */
#define XGIFB_GET_INFO    0x80046ef8  /* Wow, what a terrible hack... */

/* Structure argument for XGIFB_GET_INFO ioctl  */
typedef struct _XGIFB_INFO xgifb_info, *pxgifb_info;

struct _XGIFB_INFO {
	CARD32 	xgifb_id;         	/* for identifying xgifb */
#ifndef XGIFB_ID
#define XGIFB_ID	  0x53495346    /* Identify myself with 'XGIF' */
#endif
 	CARD32 	chip_id;		/* PCI ID of detected chip */
	CARD32	memory;			/* video memory in KB which xgifb manages */
	CARD32	heapstart;             	/* heap start (= xgifb "mem" argument) in KB */
	CARD8 	fbvidmode;		/* current xgifb mode */

	CARD8 	xgifb_version;
	CARD8	xgifb_revision;
	CARD8 	xgifb_patchlevel;

	CARD8 	xgifb_caps;		/* xgifb's capabilities */

	CARD32 	xgifb_tqlen;		/* turbo queue length (in KB) */

	CARD32 	xgifb_pcibus;      	/* The card's PCI ID */
	CARD32 	xgifb_pcislot;
	CARD32 	xgifb_pcifunc;

	CARD8 	xgifb_lcdpdc;

	CARD8	xgifb_lcda;

	CARD32	xgifb_vbflags;
	CARD32	xgifb_currentvbflags;

	CARD32 	xgifb_scalelcd;
	CARD32 	xgifb_specialtiming;

	CARD8 	xgifb_haveemi;
	CARD8 	xgifb_emi30,xgifb_emi31,xgifb_emi32,xgifb_emi33;
	CARD8 	xgifb_haveemilcd;

	CARD8 	xgifb_lcdpdca;

	CARD8 reserved[212]; 		/* for future use */
};
#endif

#endif

