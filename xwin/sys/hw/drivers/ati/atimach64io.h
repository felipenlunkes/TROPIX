/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/ati/atimach64io.h,v 1.20 2007/01/01 16:08:16 tsi Exp $ */
/*
 * Copyright 2000 through 2007 by Marc Aurele La France (TSI @ UQV), tsi@xfree86.org
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of Marc Aurele La France not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  Marc Aurele La France makes no representations
 * about the suitability of this software for any purpose.  It is provided
 * "as-is" without express or implied warranty.
 *
 * MARC AURELE LA FRANCE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.  IN NO
 * EVENT SHALL MARC AURELE LA FRANCE BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef ___ATIMACH64IO_H___

#if !defined(___ATI_H___) && defined(XFree86Module)
# error Missing #include "ati.h" before #include "atimach64io.h"
# undef XFree86Module
#endif

#define ___ATIMACH64IO_H___ 1

#include "atiio.h"
#include "atistruct.h"

/*
 * A few important notes on some of the I/O statements provided:
 *
 * inl/outl     32-bit R/W through PIO space.  The register is specified as the
 *              actual PIO address.  These are actually defined in compiler.h.
 *
 * inw/outw     16-bit counterparts to inl/outl.  Not currently used for Mach64
 *              support.  Also defined in compiler.h.
 *
 * inb/outb     8-bit counterparts to inl/outl.  Defined in compiler.h.
 *
 * inm/outm     32-bit R/W through MMIO space.  The register is specified as
 *              the actual MMIO offset (with Block 1 following Block 0), which,
 *              in this case, is equivalent to the register's IOPortTag from
 *              atiregs.h.  Can be used for those few non-FIFO'ed registers
 *              outside of Block 0's first 256 bytes.  inm() can also be used
 *              for FIFO'ed registers if, and only if, it can be guaranteed to
 *              not have been previously FIFO'ed (e.g. when the engine is
 *              idle).  pATI->pBlock array elements must have been previously
 *              set up by ATIMapApertures().
 *
 * outf         32-bit write through MMIO cache.  Identical to outm() but
 *              intended for FIFO'ed registers.  There is no inf() provided.
 *
 * inr/outr     32-bit R/W through PIO or MMIO.  Which one depends on the
 *              machine architecture.  The register is specified as a IOPortTag
 *              from atiregs.h.  Can only be used for registers in the first
 *              256 bytes of MMIO space (in Block 0).  Note that all of these
 *              registers are non-FIFO'ed.
 *
 * inh/outh     16-bit counterparts to inr/outr.  Not currently used for Mach64
 *              support.
 *
 * in8/out8     8-bit counterparts to inr/outr.
 *
 * For portability reasons, inr/outr/inh/outh/in8/out8 should be used in
 * preference to inl/outl/inw/outw/inb/outb to/from any register space starting
 * with CRTC_H_TOTAL_DISP but before DST_OFF_PITCH (in the order defined by
 * atiregs.h).  None of inm/outm/outf should ever be used for these registers.
 * Also, all I/O from/to FIFO'ed registers must be 32-bit.
 *
 * outf()'s should be grouped together as much as possible, while respecting
 * any ordering constraints the engine might impose.  Groups larger than 16
 * outf()'s should be split up into two or more groups as needed (but not
 * necessarily wanted).  The outf() groups that result should be immediately
 * preceeded by an ATIMach64WaitForFIFO(n) call, where "n" is the number of
 * outf()'s in the group with the exception that groups containing a single
 * outf() should not be thus preceeded.  This means "n" should not be less than
 * 2, nor larger than 16.
 */

/*
 * Cave canem (or it WILL bite you):  All Mach64 non-VGA registers are
 * ================================   little-endian, no matter how they are
 *                                    accessed (nor by what).
 */

#define inm(_Register)                                                   \
    MMIO_IN32(pATI->pBlock[GetBits(_Register, BLOCK_SELECT)],            \
              (_Register) & MM_IO_SELECT)
#define outm(_Register, _Value)                                          \
    MMIO_OUT32(pATI->pBlock[GetBits(_Register, BLOCK_SELECT)],           \
               (_Register) & MM_IO_SELECT, _Value)

#define ATIIOPort(_PortTag)                                \
    (((pATI->IODecoding == SPARSE_IO) ?                    \
      ((_PortTag) & (SPARSE_IO_SELECT | IO_BYTE_SELECT)) : \
      ((_PortTag) & (BLOCK_IO_SELECT | IO_BYTE_SELECT))) + \
     pATI->CPIOBase)

#define inr(_Register)                                       \
    ((pATI->IODecoding != MEMORY_IO) ?                       \
     inl(ATIIOPort(_Register & IO_LONG_PORT)) :              \
     MMIO_IN32(pATI->pBlock[0], (_Register) & MM_IO_SELECT))
#define outr(_Register, _Value)                                               \
    do                                                                        \
    {                                                                         \
        CARD32 __Value = (_Value);                                            \
                                                                              \
        if (pATI->IODecoding != MEMORY_IO)                                    \
            outl(ATIIOPort(_Register & IO_LONG_PORT), __Value);               \
        else                                                                  \
            MMIO_OUT32(pATI->pBlock[0], (_Register) & MM_IO_SELECT, __Value); \
    } while (0)

#define inh(_Register)                                         \
    ((pATI->IODecoding != MEMORY_IO) ?                         \
     inw(ATIIOPort(_Register & IO_WORD_PORT)) :                \
     MMIO_IN16(pATI->pBlock[0],                                \
               (_Register) & (MM_IO_SELECT | IO_WORD_SELECT)))
#define outh(_Register, _Value)                                       \
    do                                                                \
    {                                                                 \
        CARD16 __Value = (_Value);                                    \
                                                                      \
        if (pATI->IODecoding != MEMORY_IO)                            \
            outw(ATIIOPort(_Register & IO_WORD_PORT), __Value);       \
        else                                                          \
            MMIO_OUT16(pATI->Block[0],                                \
                       (_Register) & (MM_IO_SELECT | IO_WORD_SELECT), \
                       __Value);                                      \
    } while (0)

#define in8(_Register)                                        \
    ((pATI->IODecoding != MEMORY_IO) ?                        \
     inb(ATIIOPort(_Register)) :                              \
     MMIO_IN8(pATI->pBlock[0],                                \
              (_Register) & (MM_IO_SELECT | IO_BYTE_SELECT)))
#define out8(_Register, _Value)                                      \
    do                                                               \
    {                                                                \
        CARD8 __Value = (_Value);                                    \
                                                                     \
        if (pATI->IODecoding != MEMORY_IO)                           \
            outb(ATIIOPort(_Register), __Value);                     \
        else                                                         \
            MMIO_OUT8(pATI->pBlock[0],                               \
                      (_Register) & (MM_IO_SELECT | IO_BYTE_SELECT), \
                      __Value);                                      \
    } while (0)

extern void ATIMach64PollEngineStatus FunctionPrototype((ATIPtr));

/*
 * MMIO cache definitions.
 *
 * Many FIFO'ed registers can be cached by the driver.  Registers that qualify
 * for caching must not contain values that can change without driver
 * intervention.  Thus registers that contain hardware counters, strobe lines,
 * etc., cannot be cached.  This caching is intended to minimise FIFO use.
 * There is therefore not much point to enable it for non-FIFO'ed registers.
 *
 * The cache for a particular 32-bit register is enabled by coding a
 * CacheRegister() line for that register in the ATIMach64Set() function.  The
 * integrity of the cache for a particular register should be verified by the
 * ATIMach64Sync() function.  This code should be kept in register order, as
 * defined in atiregs.h.
 */
#define CacheByte(___Register) pATI->MMIOCached[CacheSlotOf(___Register) >> 3]
#define CacheBit(___Register)  (0x80U >> (CacheSlotOf(___Register) & 0x07U))

#define RegisterIsCached(__Register) \
    (CacheByte(__Register) & CacheBit(__Register))
#define CacheSlot(__Register) pATI->MMIOCache[CacheSlotOf(__Register)]

#define CacheRegister(__Register) \
    CacheByte(__Register) |= CacheBit(__Register)
#define UncacheRegister(__Register) \
    CacheByte(__Register) &= ~CacheBit(__Register)

/* This would be quite a bit slower as a function */
#define outf(_Register, _Value)                                        \
    do                                                                 \
    {                                                                  \
        CARD32 _IOValue = (_Value);                                    \
                                                                       \
        if (!RegisterIsCached(_Register) ||                            \
            (_IOValue != CacheSlot(_Register)))                        \
        {                                                              \
            while (!pATI->nAvailableFIFOEntries--)                     \
                ATIMach64PollEngineStatus(pATI);                       \
            MMIO_OUT32(pATI->pBlock[GetBits(_Register, BLOCK_SELECT)], \
                       (_Register) & MM_IO_SELECT, _IOValue);          \
            CacheSlot(_Register) = _IOValue;                           \
            pATI->EngineIsBusy = TRUE;                                 \
        }                                                              \
    } while (0)

/*
 * This is no longer as critical, especially for _n == 1.  However,
 * there is still a need to ensure _n <= pATI->nFIFOEntries.
 */
#define ATIMach64WaitForFIFO(_pATI, _n)           \
    while ((_pATI)->nAvailableFIFOEntries < (_n)) \
        ATIMach64PollEngineStatus(_pATI)

#define ATIMach64WaitForIdle(_pATI)         \
    while ((_pATI)->EngineIsBusy)           \
        ATIMach64PollEngineStatus(_pATI)

/*
 * An outf() variant to write two registers such that the second register is
 * always written whenever either is to be changed.
 */
#define outq(_Register1, _Register2, _Value1, _Value2)                  \
    do                                                                  \
    {                                                                   \
        CARD32 _IOValue1 = (_Value1),                                   \
               _IOValue2 = (_Value2);                                   \
                                                                        \
        if (!RegisterIsCached(_Register1) ||                            \
            (_IOValue1 != CacheSlot(_Register1)))                       \
        {                                                               \
            ATIMach64WaitForFIFO(pATI, 2);                              \
            pATI->nAvailableFIFOEntries -= 2;                           \
            MMIO_OUT32(pATI->pBlock[GetBits(_Register1, BLOCK_SELECT)], \
                       (_Register1) & MM_IO_SELECT, _IOValue1);         \
            MMIO_OUT32(pATI->pBlock[GetBits(_Register2, BLOCK_SELECT)], \
                       (_Register2) & MM_IO_SELECT, _IOValue2);         \
            CacheSlot(_Register1) = _IOValue1;                          \
            CacheSlot(_Register2) = _IOValue2;                          \
            pATI->EngineIsBusy = TRUE;                                  \
        }                                                               \
        else if (!RegisterIsCached(_Register2) ||                       \
                 (_IOValue2 != CacheSlot(_Register2)))                  \
        {                                                               \
            while (!pATI->nAvailableFIFOEntries--)                      \
                ATIMach64PollEngineStatus(pATI);                        \
            MMIO_OUT32(pATI->pBlock[GetBits(_Register2, BLOCK_SELECT)], \
                       (_Register2) & MM_IO_SELECT, _IOValue2);         \
            CacheSlot(_Register2) = _IOValue2;                          \
            pATI->EngineIsBusy = TRUE;                                  \
        }                                                               \
    } while (0)

extern void ATIMach64AccessPLLReg FunctionPrototype((ATIPtr, const CARD8,
                                                     const Bool));

#define ATIMach64GetPLLReg(_Index)                  \
    (                                               \
        ATIMach64AccessPLLReg(pATI, _Index, FALSE), \
        in8(CLOCK_CNTL + 2)                         \
    )
#define ATIMach64PutPLLReg(_Index, _Value)          \
    do                                              \
    {                                               \
        ATIMach64AccessPLLReg(pATI, _Index, TRUE);  \
        out8(CLOCK_CNTL + 2, _Value);               \
    } while (0)

extern void ATIMach64AccessLCDReg FunctionPrototype((ATIPtr, const CARD8));

#define ATIMach64GetLCDReg(_Index)           \
    (                                        \
        ATIMach64AccessLCDReg(pATI, _Index), \
        inr(LCD_DATA)                        \
    )
#define ATIMach64PutLCDReg(_Index, _Value)   \
    do                                       \
    {                                        \
        ATIMach64AccessLCDReg(pATI, _Index); \
        outr(LCD_DATA, _Value);              \
    } while (0)

extern void ATIMach64AccessTVReg  FunctionPrototype((ATIPtr, const CARD8));

#define ATIMach64GetTVReg(_Index)           \
    (                                       \
        ATIMach64AccessTVReg(pATI, _Index), \
        inr(TV_OUT_DATA)                    \
    )
#define ATIMach64PutTVReg(_Index, _Value)   \
    do                                      \
    {                                       \
        ATIMach64AccessTVReg(pATI, _Index); \
        outr(TV_OUT_DATA, _Value);          \
    } while (0)

/*
 * Block transfer definitions.
 */

#if defined(GCCUSESGAS) && \
    (defined(i386) || defined(__i386) || defined(__i386__))

#ifdef	TROPIX
#define	ATIMove32(_pDst, _pSrc, _nCount) memcpy (_pDst, _pSrc, (_nCount) << 2)
#else
#define ATIMove32(_pDst, _pSrc, _nCount) \
    do                                   \
    {                                    \
        long d0, d1, d2;                 \
        __asm__ __volatile__             \
        (                                \
            "cld\n\t"                    \
            "rep ; movsl"                \
            : "=&c" (d0),                \
              "=&D" (d1),                \
              "=&S" (d2)                 \
            : "0" (_nCount),             \
              "1" (_pDst),               \
              "2" (_pSrc)                \
            : "memory"                   \
        );                               \
    } while (0)
#endif	TROPIX

#endif

#endif /* ___ATIMACH64IO_H___ */
