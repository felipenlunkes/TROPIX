/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/xgi/xgi_common.h,v 1.1 2005/05/02 13:28:02 dawes Exp $ */
/*
 * Common header definitions for XGI 2D/3D/DRM suite
 *
 * Copyright (C) 2003 Eric Anholt
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appears in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * and that the name of the copyright holder not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. The copyright holder makes no representations
 * about the suitability of this software for any purpose.  It is provided
 * "as is" without expressed or implied warranty.
 *
 * THE COPYRIGHT HOLDER DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
 * EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * Author:
 *   	Eric Anholt <anholt@FreeBSD.org>
 *
 */

#ifndef _XGI_COMMON_H_
#define _XGI_COMMON_H_

#define DRM_XGI_FB_ALLOC	0x04
#define DRM_XGI_FB_FREE		0x05
#define DRM_XGI_FLIP		0x08
#define DRM_XGI_FLIP_INIT	0x09
#define DRM_XGI_FLIP_FINAL	0x10
#define DRM_XGI_AGP_INIT	0x13
#define DRM_XGI_AGP_ALLOC	0x14
#define DRM_XGI_AGP_FREE	0x15
#define DRM_XGI_FB_INIT		0x16

typedef struct {
  	int context;
  	unsigned long offset;
  	unsigned long size;
  	void *free;
} drm_xgi_mem_t;

typedef struct {
  	unsigned long offset, size;
} drm_xgi_agp_t;

typedef struct {
  	unsigned long offset, size;
} drm_xgi_fb_t;

typedef struct {
  	unsigned int left, right;
} drm_xgi_flip_t;

#endif /* _XGI_COMMON_H_ */

