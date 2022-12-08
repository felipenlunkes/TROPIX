/*
 * Sun GX and Turbo GX acceleration support
 *
 * Copyright (C) 2005 Michael Lorenz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * MICHAEL LORENZ BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/suncg6/cg6_accel.c,v 1.1 2005/04/30 17:04:00 tsi Exp $ */

#include "cg6.h"


static CARD32 Cg6BlitROP[] = {
    ROP_BLIT(GX_ROP_CLEAR,  GX_ROP_CLEAR),	/* GXclear */
    ROP_BLIT(GX_ROP_CLEAR,  GX_ROP_NOOP),	/* GXand */
    ROP_BLIT(GX_ROP_CLEAR,  GX_ROP_INVERT),	/* GXandReverse */
    ROP_BLIT(GX_ROP_CLEAR,  GX_ROP_SET),	/* GXcopy */
    ROP_BLIT(GX_ROP_NOOP,   GX_ROP_CLEAR),	/* GXandInverted */
    ROP_BLIT(GX_ROP_NOOP,   GX_ROP_NOOP),	/* GXnoop */
    ROP_BLIT(GX_ROP_NOOP,   GX_ROP_INVERT),	/* GXxor */
    ROP_BLIT(GX_ROP_NOOP,   GX_ROP_SET),	/* GXor */
    ROP_BLIT(GX_ROP_INVERT, GX_ROP_CLEAR),	/* GXnor */
    ROP_BLIT(GX_ROP_INVERT, GX_ROP_NOOP),	/* GXequiv */
    ROP_BLIT(GX_ROP_INVERT, GX_ROP_INVERT),	/* GXinvert */
    ROP_BLIT(GX_ROP_INVERT, GX_ROP_SET),	/* GXorReverse */
    ROP_BLIT(GX_ROP_SET,    GX_ROP_CLEAR),	/* GXcopyInverted */
    ROP_BLIT(GX_ROP_SET,    GX_ROP_NOOP),	/* GXorInverted */
    ROP_BLIT(GX_ROP_SET,    GX_ROP_INVERT),	/* GXnand */
    ROP_BLIT(GX_ROP_SET,    GX_ROP_SET),	/* GXset */
};

static CARD32 Cg6DrawROP[] = {
    ROP_FILL(GX_ROP_CLEAR,  GX_ROP_CLEAR),	/* GXclear */
    ROP_FILL(GX_ROP_CLEAR,  GX_ROP_NOOP),	/* GXand */
    ROP_FILL(GX_ROP_CLEAR,  GX_ROP_INVERT),	/* GXandReverse */
    ROP_FILL(GX_ROP_CLEAR,  GX_ROP_SET),	/* GXcopy */
    ROP_FILL(GX_ROP_NOOP,   GX_ROP_CLEAR),	/* GXandInverted */
    ROP_FILL(GX_ROP_NOOP,   GX_ROP_NOOP),	/* GXnoop */
    ROP_FILL(GX_ROP_NOOP,   GX_ROP_INVERT),	/* GXxor */
    ROP_FILL(GX_ROP_NOOP,   GX_ROP_SET),	/* GXor */
    ROP_FILL(GX_ROP_INVERT, GX_ROP_CLEAR),	/* GXnor */
    ROP_FILL(GX_ROP_INVERT, GX_ROP_NOOP),	/* GXequiv */
    ROP_FILL(GX_ROP_INVERT, GX_ROP_INVERT),	/* GXinvert */
    ROP_FILL(GX_ROP_INVERT, GX_ROP_SET),	/* GXorReverse */
    ROP_FILL(GX_ROP_SET,    GX_ROP_CLEAR),	/* GXcopyInverted */
    ROP_FILL(GX_ROP_SET,    GX_ROP_NOOP),	/* GXorInverted */
    ROP_FILL(GX_ROP_SET,    GX_ROP_INVERT),	/* GXnand */
    ROP_FILL(GX_ROP_SET,    GX_ROP_SET),	/* GXset */
};

static CARD32 Cg6StippleROP[16]={
    ROP_STIP(GX_ROP_CLEAR,  GX_ROP_CLEAR),	/* GXclear */
    ROP_STIP(GX_ROP_CLEAR,  GX_ROP_NOOP),	/* GXand */
    ROP_STIP(GX_ROP_CLEAR,  GX_ROP_INVERT),	/* GXandReverse */
    ROP_STIP(GX_ROP_CLEAR,  GX_ROP_SET),	/* GXcopy */
    ROP_STIP(GX_ROP_NOOP,   GX_ROP_CLEAR),	/* GXandInverted */
    ROP_STIP(GX_ROP_NOOP,   GX_ROP_NOOP),	/* GXnoop */
    ROP_STIP(GX_ROP_NOOP,   GX_ROP_INVERT),	/* GXxor */
    ROP_STIP(GX_ROP_NOOP,   GX_ROP_SET),	/* GXor */
    ROP_STIP(GX_ROP_INVERT, GX_ROP_CLEAR),	/* GXnor */
    ROP_STIP(GX_ROP_INVERT, GX_ROP_NOOP),	/* GXequiv */
    ROP_STIP(GX_ROP_INVERT, GX_ROP_INVERT),	/* GXinvert */
    ROP_STIP(GX_ROP_INVERT, GX_ROP_SET),	/* GXorReverse */
    ROP_STIP(GX_ROP_SET,    GX_ROP_CLEAR),	/* GXcopyInverted */
    ROP_STIP(GX_ROP_SET,    GX_ROP_NOOP),	/* GXorInverted */
    ROP_STIP(GX_ROP_SET,    GX_ROP_INVERT),	/* GXnand */
    ROP_STIP(GX_ROP_SET,    GX_ROP_SET),	/* GXset */
};

static CARD32 Cg6OpaqueStippleROP[16]={
    ROP_OSTP(GX_ROP_CLEAR,  GX_ROP_CLEAR),	/* GXclear */
    ROP_OSTP(GX_ROP_CLEAR,  GX_ROP_NOOP),	/* GXand */
    ROP_OSTP(GX_ROP_CLEAR,  GX_ROP_INVERT),	/* GXandReverse */
    ROP_OSTP(GX_ROP_CLEAR,  GX_ROP_SET),	/* GXcopy */
    ROP_OSTP(GX_ROP_NOOP,   GX_ROP_CLEAR),	/* GXandInverted */
    ROP_OSTP(GX_ROP_NOOP,   GX_ROP_NOOP),	/* GXnoop */
    ROP_OSTP(GX_ROP_NOOP,   GX_ROP_INVERT),	/* GXxor */
    ROP_OSTP(GX_ROP_NOOP,   GX_ROP_SET),	/* GXor */
    ROP_OSTP(GX_ROP_INVERT, GX_ROP_CLEAR),	/* GXnor */
    ROP_OSTP(GX_ROP_INVERT, GX_ROP_NOOP),	/* GXequiv */
    ROP_OSTP(GX_ROP_INVERT, GX_ROP_INVERT),	/* GXinvert */
    ROP_OSTP(GX_ROP_INVERT, GX_ROP_SET),	/* GXorReverse */
    ROP_OSTP(GX_ROP_SET,    GX_ROP_CLEAR),	/* GXcopyInverted */
    ROP_OSTP(GX_ROP_SET,    GX_ROP_NOOP),	/* GXorInverted */
    ROP_OSTP(GX_ROP_SET,    GX_ROP_INVERT),	/* GXnand */
    ROP_OSTP(GX_ROP_SET,    GX_ROP_SET),	/* GXset */
};

/* wait until the engine is idle */
static void
Cg6Sync(ScrnInfoPtr pScrn)
{
    Cg6Ptr pCg6 = GET_CG6_FROM_SCRN(pScrn);

    while (pCg6->fbc->s & GX_INPROGRESS);
}

/* wait until the blitter is idle */
static void
Cg6SyncBlt(ScrnInfoPtr pScrn)
{
    Cg6Ptr pCg6 = GET_CG6_FROM_SCRN(pScrn);

    while (pCg6->fbc->blit & GX_BLT_INPROGRESS);
}

/* wait until the blitter is idle */
static void
Cg6SyncDraw(ScrnInfoPtr pScrn)
{
    Cg6Ptr pCg6 = GET_CG6_FROM_SCRN(pScrn);

    while (pCg6->fbc->draw & GX_FULL);
}

static void
unClip(Cg6Ptr pCg6)
{
    pCg6->fbc->clipminx = 0;
    pCg6->fbc->clipminy = 0;
    pCg6->fbc->clipmaxx = pCg6->width - 1;
    pCg6->fbc->clipmaxy = pCg6->maxheight - 1;
}

static void
Cg6InitEngine(Cg6Ptr pCg6)
{
    unClip(pCg6);
    pCg6->fbc->mode = GX_BLIT_SRC | GX_MODE_COLOR8 | GX_DRAW_RENDER |
	GX_BWRITE0_ENABLE | GX_BWRITE1_DISABLE | GX_BREAD_0 | GX_BDISP_0;

    pCg6->fbc->fg = 0xff;
    pCg6->fbc->bg = 0x00;
    pCg6->fbc->pixelm = ~0;
    pCg6->fbc->s = 0;
    pCg6->fbc->clip = 0;
    pCg6->fbc->offx = 0;
    pCg6->fbc->offy = 0;
}

static void
Cg6SetupForScreenToScreenCopy
(
    ScrnInfoPtr  pScrn,
    int          xdir,
    int          ydir,
    int          rop,
    unsigned int planemask,
    int          TransparencyColour
)
{
    Cg6Ptr pCg6 = GET_CG6_FROM_SCRN(pScrn);

    Cg6Sync(pScrn);
    unClip(pCg6);
    pCg6->fbc->mode = GX_BLIT_SRC | GX_MODE_COLOR8 | GX_DRAW_RENDER |
	GX_BWRITE0_ENABLE | GX_BWRITE1_DISABLE | GX_BREAD_0 | GX_BDISP_0;

    pCg6->fbc->incx = 0;
    pCg6->fbc->incy = 0;
    pCg6->fbc->fg = 0xff;
    pCg6->fbc->bg = 0x00;
    pCg6->fbc->pixelm = ~0;
    pCg6->fbc->s = 0;
    pCg6->fbc->alu = Cg6BlitROP[rop];
    pCg6->fbc->pm = planemask;
    pCg6->fbc->clip = 0;
}

static void
Cg6SubsequentScreenToScreenCopy
(
    ScrnInfoPtr pScrn,
    int         xSrc,
    int         ySrc,
    int         xDst,
    int         yDst,
    int         w,
    int         h
)
{
    Cg6Ptr pCg6 = GET_CG6_FROM_SCRN(pScrn);

    pCg6->fbc->x0 = xSrc;
    pCg6->fbc->y0 = ySrc;
    pCg6->fbc->x1 = xSrc + w - 1;
    pCg6->fbc->y1 = ySrc + h - 1;
    pCg6->fbc->x2 = xDst;
    pCg6->fbc->y2 = yDst;
    pCg6->fbc->x3 = xDst + w - 1;
    pCg6->fbc->y3 = yDst + h - 1;
    Cg6SyncBlt(pScrn);
}

static void
Cg6SetupForSolidFill
(
    ScrnInfoPtr  pScrn,
    int          colour,
    int          rop,
    unsigned int planemask
)
{
    Cg6Ptr pCg6 = GET_CG6_FROM_SCRN(pScrn);

    Cg6Sync(pScrn);
    unClip(pCg6);
    pCg6->fbc->mode = GX_BLIT_SRC | GX_MODE_COLOR8 | GX_DRAW_RENDER |
	GX_BWRITE0_ENABLE | GX_BWRITE1_DISABLE | GX_BREAD_0 | GX_BDISP_0;

    pCg6->fbc->incx = 0;
    pCg6->fbc->incy = 0;
    pCg6->fbc->fg = colour;
    pCg6->fbc->bg = 0x00;
    pCg6->fbc->pixelm = ~0;
    pCg6->fbc->s = 0;
    pCg6->fbc->alu = Cg6DrawROP[rop];
    pCg6->fbc->pm = planemask;
    pCg6->fbc->clip = 0;
}

static void
Cg6SubsequentSolidFillRect
(
    ScrnInfoPtr pScrn,
    int         x,
    int         y,
    int         w,
    int         h
)
{
    Cg6Ptr pCg6 = GET_CG6_FROM_SCRN(pScrn);

    pCg6->fbc->arecty = y;
    pCg6->fbc->arectx = x;
    pCg6->fbc->arecty = y + h - 1;
    pCg6->fbc->arectx = x + w - 1;
    Cg6SyncDraw(pScrn);
}

static void 
Cg6SetupForCPUToScreenColorExpandFill
(
    ScrnInfoPtr  pScrn,
    int          fg,
    int          bg,
    int          rop,
    unsigned int planemask
)
{
    Cg6Ptr pCg6 = GET_CG6_FROM_SCRN(pScrn);

    Cg6Sync(pScrn);
    pCg6->fbc->mode = GX_BLIT_NOSRC | GX_MODE_COLOR1;
    unClip(pCg6);

    if (bg == -1) {
	pCg6->fbc->alu = Cg6StippleROP[rop] | GX_PATTERN_ONES;
	pCg6->fbc->bg = 0xff;
    } else {
	pCg6->fbc->alu = Cg6OpaqueStippleROP[rop]|GX_PATTERN_ONES;
	pCg6->fbc->bg = bg;
    }	

    pCg6->fbc->fg = fg;
    pCg6->fbc->incx = 32;
    pCg6->fbc->incy = 0;
    pCg6->fbc->pixelm = ~0;
    pCg6->fbc->s = 0;
    pCg6->fbc->pm = planemask;
    pCg6->fbc->clip = 0;
}

#if 0
static void
Cg6SubsequentCPUToScreenColorExpandFill
(
    ScrnInfoPtr pScrn,
    int         x,
    int         y,
    int         w,
    int         h,
    int         skipleft
)
{
    Cg6Ptr pCg6 = GET_CG6_FROM_SCRN(pScrn);

    pCg6->fbc->x0 = x;
    pCg6->fbc->x1 = x + w - 1;
    pCg6->fbc->y0 = y;
    pCg6->fbc->patalign = (skipleft & 0xffff) << 16;
}
#endif

static void 
Cg6SubsequentScanlineCPUToScreenColorExpandFill
(
    ScrnInfoPtr pScrn,
    int         x,
    int         y,
    int         w,
    int         h,
    int         skipleft
)
{
    Cg6Ptr pCg6 = GET_CG6_FROM_SCRN(pScrn);

    pCg6->scan_x = x;
    pCg6->scan_xe = x + w - 1;
    pCg6->scan_y = y;
    pCg6->fbc->patalign = (skipleft & 0xffff) << 16;
    pCg6->fbc->clipminx = x;
    pCg6->fbc->clipmaxx = x + w - 1;
    pCg6->words_in_scanline = (w + 31) >> 5;
}

static void
Cg6SubsequentColorExpandScanline(ScrnInfoPtr pScrn, int bufno)
{
    Cg6Ptr pCg6 = GET_CG6_FROM_SCRN(pScrn);
    int i;

    /*
     * The GX is WEIRD.  If we tell it to draw in pixels it will fill the entire
     * line with whatever we feed into the font register.  When we write the
     * next word it draws the entire line AGAIN.  So we turn on clipping and
     * pretend to write only 32 pixels...
     */
    pCg6->fbc->x0 = pCg6->scan_x;
    pCg6->fbc->x1 = pCg6->scan_x + 31;
    pCg6->fbc->y0 = pCg6->scan_y;	

    for (i = 0;  i < pCg6->words_in_scanline;  i++) {
	pCg6->fbc->font = pCg6->scanline[i];
    }	

    pCg6->scan_y++;	
    Cg6Sync(pScrn);
}

int
CG6AccelInit(ScrnInfoPtr pScrn)
{
    Cg6Ptr pCg6 = GET_CG6_FROM_SCRN(pScrn);
    XAAInfoRecPtr pXAAInfo = pCg6->pXAA;

    pXAAInfo->Flags = LINEAR_FRAMEBUFFER | PIXMAP_CACHE | OFFSCREEN_PIXMAPS;
    pXAAInfo->maxOffPixWidth = pCg6->width;
    pXAAInfo->maxOffPixHeight = pCg6->maxheight;

    Cg6InitEngine(pCg6);

    /* Sync */
    pXAAInfo->Sync = Cg6Sync;
    /* Screen-to-screen copy */
    pXAAInfo->ScreenToScreenCopyFlags=NO_TRANSPARENCY;
    pXAAInfo->SetupForScreenToScreenCopy = Cg6SetupForScreenToScreenCopy;
    pXAAInfo->SubsequentScreenToScreenCopy =
	Cg6SubsequentScreenToScreenCopy;

    /* Solid fills */
    pXAAInfo->SetupForSolidFill = Cg6SetupForSolidFill;
    pXAAInfo->SubsequentSolidFillRect = Cg6SubsequentSolidFillRect;

	/* colour expansion */
#if 0
    pXAAInfo->CPUToScreenColorExpandFillFlags = SCANLINE_PAD_DWORD |
	CPU_TRANSFER_BASE_FIXED /* | LEFT_EDGE_CLIPPING */;
    pXAAInfo->ColorExpandBase = (unsigned char *)&pCg6->fbc->font;
    pXAAInfo->SetupForCPUToScreenColorExpandFill =
	Cg6SetupForCPUToScreenColorExpandFill;
    pXAAInfo->SubsequentCPUToScreenColorExpandFill =
	Cg6SubsequentCPUToScreenColorExpandFill;
#else
    pXAAInfo->ScanlineCPUToScreenColorExpandFillFlags =
	LEFT_EDGE_CLIPPING | SCANLINE_PAD_DWORD;
    pXAAInfo->NumScanlineColorExpandBuffers = 1;
    pCg6->buffers[0] = (unsigned char *)pCg6->scanline;
    pXAAInfo->ScanlineColorExpandBuffers = pCg6->buffers;
    pXAAInfo->SetupForScanlineCPUToScreenColorExpandFill =
	Cg6SetupForCPUToScreenColorExpandFill;
    pXAAInfo->SubsequentScanlineCPUToScreenColorExpandFill =
	Cg6SubsequentScanlineCPUToScreenColorExpandFill;
    pXAAInfo->SubsequentColorExpandScanline =
	Cg6SubsequentColorExpandScanline;
#endif
    return 0;
}
