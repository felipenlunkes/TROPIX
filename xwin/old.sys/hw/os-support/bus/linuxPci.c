/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/bus/linuxPci.c,v 1.13 2005/04/07 14:13:52 tsi Exp $ */
/*
 * Copyright 1998 by Concurrent Computer Corporation
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of Concurrent Computer Corporation not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.  Concurrent Computer Corporation makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * CONCURRENT COMPUTER CORPORATION DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
 * IN NO EVENT SHALL CONCURRENT COMPUTER CORPORATION BE LIABLE FOR ANY SPECIAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
/*
 * Copyright 1998 by Metro Link Incorporated
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of Metro Link Incorporated not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  Metro Link Incorporated makes no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * METRO LINK INCORPORATED DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
 * IN NO EVENT SHALL METRO LINK INCORPORATED BE LIABLE FOR ANY SPECIAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
/*
 * Copyright 2004 The XFree86 Project, Inc.
 *
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1.  Redistributions of source code must retain the above copyright notice,
 *     this list of conditions, and the following disclaimer.
 *
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution, and
 *     in the same place and form as other copyright, license and disclaimer
 *     information.
 *
 * 3.  The end-user documentation included with the redistribution, if any,
 *     must include the following acknowledgment:  "This product includes
 *     software developed by The XFree86 Project, Inc (http://www.xfree86.org/)
 *     and its contributors", in the same place and form as other third-party
 *     acknowledgments.  Alternately, this acknowledgment may appear in the
 *     software itself, in the same form and location as other such third-party
 *     acknowledgments.
 *
 * 4.  Except as contained in this notice, the name of The XFree86 Project, Inc
 *     shall not be used in advertising or otherwise to promote the sale, use
 *     or other dealings in this Software without prior written authorization
 *     from The XFree86 Project, Inc.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * XFREE86 PROJECT, INC OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <dirent.h>
#include "compiler.h"
#include "xf86.h"
#include "xf86Priv.h"
#include "xf86_OSlib.h"
#include "Pci.h"

/*
 * Linux specific PCI access functions -- using /proc/bus/pci
 * Needs kernel version 2.2.x
 */
static CARD32 linuxPciCfgRead(PCITAG tag, int off);
static void linuxPciCfgWrite(PCITAG, int off, CARD32 val);
static void linuxPciCfgSetBits(PCITAG tag, int off, CARD32 mask, CARD32 bits);
#ifdef __powerpc__
static ADDRESS linuxPpcBusAddrToHostAddr(PCITAG, PciAddrType, ADDRESS);
static ADDRESS linuxPpcHostAddrToBusAddr(PCITAG, PciAddrType, ADDRESS);
#endif /* __powerpc__ */

static pciBusFuncs_t linuxBusFuncs = {
/* pciReadLong      */	linuxPciCfgRead,
/* pciWriteLong     */	linuxPciCfgWrite,
/* pciSetBitsLong   */	linuxPciCfgSetBits,
#ifdef __powerpc__
/* pciAddrHostToBus */	linuxPpcHostAddrToBusAddr,
/* pciAddrBusToHost */	linuxPpcBusAddrToHostAddr
#else /* __powerpc__ */
/* pciAddrHostToBus */	pciAddrNOOP,
/* pciAddrBusToHost */	pciAddrNOOP
#endif /* __powerpc__ */
};

static pciBusInfo_t linuxBusInfo = {
/* configMech  */	PCI_CFG_MECH_OTHER,
/* numDevices  */	32,
/* secondary   */	FALSE,
/* primary_bus */	0,
#ifdef PowerMAX_OS
/* ppc_io_base */	0,
/* ppc_io_size */	0,
#endif /* PowerMAX_OS */
/* funcs       */	&linuxBusFuncs,
/* pciBusPriv  */	NULL,
/* bridge      */	NULL
};

static long int busDomain[MAX_PCI_BUSES];
static Bool useDomainInBus = FALSE;

static struct {
    PCITAG tag;
    signed char size[7];
    char empty;
} linuxSize[MAX_PCI_DEVICES];

void
linuxPciInit(void)
{
    pointer fp;
    struct dirent *direntp;
    long int busno, pcibus, domain;
    long int maxbus, Index;

    if ((xf86Info.pciFlags == PCIForceNone) ||
	(!(fp = opendir("/proc/bus/pci"))))
	return;

    maxbus = MAX_PCI_BUSES;
    (void)memset(busDomain, -1, sizeof(busDomain));
    (void)memset(linuxSize, -1, sizeof(linuxSize));

    /*
     * Rationalise the kernel's somewhat confused, but still evolving,
     * domain/bus numbering into something we can actually use, both presently
     * and in the foreseeable future.
     *
     * Scan /proc/bus/pci, beginning with the assumption that the kernel's bus
     * numbers are unique across all domains.  If this assumption is found to
     * not hold, switch to pre-pending domain numbers to bus numbers.  In the
     * unlikely event this still doesn't give us unique bus numbers, we
     * consider the kernel to be babbling and we refuse to use its PCI
     * framework.
     *
     * Note that our domain numbers are always one more than the kernel's, if
     * any.
     */
    while ((direntp = readdir(fp))) {
	const char *fname, *ename;

	if (!strcmp(direntp->d_name, ".") ||
	    !strcmp(direntp->d_name, "..") ||
	    !strcmp(direntp->d_name, "devices"))
	    continue;

	if (!(fname = strchr(direntp->d_name, ':'))) {
	    fname = direntp->d_name;
	    domain = 0;
	} else {
	    errno = 0;
	    domain = strtol(direntp->d_name, (pointer)&ename, 16);
	    if (errno || (domain < 0) ||
		(fname != ename) || (fname == direntp->d_name)) {
		xf86Msg(X_ERROR,
			"linuxPciInit:  Ignoring unexpected bus name:"
			"  \"/proc/bus/pci/%s\"\n", direntp->d_name);
		continue;
	    }

	    domain++;
	    fname++;
	}

	errno = 0;
	busno = strtol(fname, (pointer)&ename, 16);
	if (errno || (busno < 0) || (busno > 255) || *ename || !*fname) {
	    xf86Msg(X_ERROR,
		    "linuxPciInit:  Ignoring unexpected bus name:"
		    "  \"/proc/bus/pci/%s\"\n", direntp->d_name);
	    continue;
	}

	/* Possibly switch to pre-pending domain numbers */
	while (1) {
	    long int busCopy[MAX_PCI_BUSES];

	    if (useDomainInBus)
		pcibus = PCI_MAKE_BUS(domain, busno);
	    else
		pcibus = busno;

	    if (pcibus >= MAX_PCI_BUSES) {
		while (pcibus >= maxbus)
		    maxbus <<= 1;
		break;
	    }

	    if (busDomain[pcibus] < 0) {
		busDomain[pcibus] = domain;
		break;
	    }

	    /* useDomainInBus should still be FALSE here, but check anyway */
	    if (useDomainInBus) {
		if (pciNumBuses == 0)
		    xf86Msg(X_ERROR,
			    "linuxPciInit:  Duplicate bus found:"
			    "  \"/proc/bus/pci/%s\"\n", direntp->d_name);
		(void)closedir(fp);
		(void)memset(busDomain, -1, sizeof(busDomain));
		return;
	    }

	    /* Redo busDomain array with domains pre-pended to buses */
	    (void)memset(busCopy, -1, sizeof(busCopy));

	    for (Index = 0;  Index < MAX_PCI_BUSES;  Index++) {
		if (busDomain[Index] < 0)
		    continue;

		pcibus = PCI_MAKE_BUS(busDomain[Index], Index);
		if (pcibus >= MAX_PCI_BUSES) {
		    while (pcibus >= maxbus)
			maxbus <<= 1;
		    continue;
		}

		busCopy[pcibus] = busDomain[Index];
	    }

	    useDomainInBus = TRUE;
	    (void)memcpy(busDomain, busCopy, sizeof(busCopy));
	}
    }

    (void)closedir(fp);

    if (maxbus > MAX_PCI_BUSES)
	xf86Msg(X_ERROR,
		"linuxPciInit:  This system needs MAX_PCI_BUSES increased to"
		" %ld\n", maxbus);

#ifdef INCLUDE_XF86_NO_DOMAIN

    /*
     * When domain support is compiled out...
     *
     * On PowerPC's, PCI allocations are relocated into the host's view before
     * conflict checking, thus avoiding the bulk (if not, all) of the
     * re-allocations that would otherwise occur.
     *
     * But, among other things, this also means PowerPC kernels that don't make
     * bus numbers unique across all domains (and that are therefore not
     * limited to 256 buses) are not yet supported.
     *
     * Ensure all other architectures are mono-domain kernel-wise too.  Not
     * doing so would cause us to overly re-allocate resources, and thereby
     * interfere with the kernel's hotplug support.
     */
#ifndef __powerpc__

    if (!useDomainInBus) {
	domain = -1;
	for (pcibus = 0;  pcibus < MAX_PCI_BUSES;  pcibus++) {
	    if (busDomain[pcibus] < 0)
		continue;

	    if (domain < 0) {
		domain = busDomain[pcibus];
	    } else if (domain != busDomain[pcibus]) {
		useDomainInBus = TRUE;
		break;
	    }
	}
    }

#endif /* __powerpc__ */

    if (useDomainInBus) {
	xf86Msg(X_ERROR, "linuxPciInit:  This platform must not #define"
		" INCLUDE_XF86_NO_DOMAIN\n");
	(void)memset(busDomain, -1, sizeof(busDomain));
	return;
    }

#endif /* INCLUDE_XF86_NO_DOMAIN */

    /*
     * Look for PCI allocation sizes in /proc/bus/pci/devices.  Read them in if
     * found.
     */
    if ((fp = fopen("/proc/bus/pci/devices", "r"))) {
	long int iDevice = 0, maxdevice = MAX_PCI_DEVICES;
	char buffer[512];

	while (fgets(buffer, sizeof(buffer), fp)) {
	    static const char format[] =
		/* An optional domain, then bus+dev, vendorid, deviceid, irq */
		"%04lx:%02lx%02x\t%*04x%*04x\t%*x"
		/* 7 PCI resource bases */
		"\t%*x\t%*x\t%*x\t%*x\t%*x\t%*x\t%*x"
		/* 7 PCI resource sizes, then an optional driver name */
#ifdef __sparc__
		"\t%llx\t%llx\t%llx\t%llx\t%llx\t%llx\t%llx";
	    unsigned long long size[7];
#else
		"\t%lx\t%lx\t%lx\t%lx\t%lx\t%lx\t%lx";
	    unsigned long size[7];
#endif
	    unsigned int devfn;

	    if (!buffer[0])
		break;

	    if (buffer[strlen(buffer) - 1] != '\n') {
		xf86Msg(X_ERROR, "Line buffer for \"/proc/bus/pci/devices\""
			" not large enough\n");
		break;
	    }

	    /*
	     * First try matching the domain-less format, then the longer
	     * format.  The latter represents an educated guess at what the
	     * future might hold for /proc/bus/pci/devices.
	     */
	    domain = 0;
	    if (sscanf(buffer, format + 6, (unsigned long *)&busno, &devfn,
		       size + 0, size + 1, size + 2, size + 3, size + 4,
		       size + 5, size + 6) != 9) {
		if (sscanf(buffer, format, (unsigned long *)&domain,
			   (unsigned long *)&busno, &devfn,
			   size + 0, size + 1, size + 2, size + 3, size + 4,
			   size + 5, size + 6) != 10)
		    break;
		domain++;
	    }

	    if (useDomainInBus)
		pcibus = PCI_MAKE_BUS(domain, busno);
	    else
		pcibus = busno;

	    if ((iDevice >= MAX_PCI_DEVICES) || (pcibus >= MAX_PCI_BUSES) ||
		(busDomain[pcibus] < 0)) {
		while (iDevice >= maxdevice)
		    maxdevice <<= 1;
	    } else {
		linuxSize[iDevice].tag =
		    PCI_MAKE_TAG(pcibus, devfn >> 3, devfn & 7);
		for (Index = 0;  Index < 7;  Index++)
		    for (;  size[Index];  size[Index] >>= 1)
			linuxSize[iDevice].size[Index]++;
		linuxSize[iDevice].empty = FALSE;
	    }

	    iDevice++;
	}

	(void)fclose(fp);

	if (maxdevice > MAX_PCI_DEVICES)
	    xf86Msg(X_ERROR,
		    "linuxPciInit:  This system needs MAX_PCI_DEVICES"
		    " increased to %ld\n", maxdevice);
    }

    /* Always prefer a hardware-derived mechanism over an OS-provided one */
    if (pciNumBuses)
	return;

    pciFindFirstFP = pciGenFindFirst;
    pciFindNextFP = pciGenFindNext;

    /* Generate pciBusInfo_t's for all buses derived from the kernel */
    for (pcibus = 0;  pcibus < MAX_PCI_BUSES;  pcibus++) {
	if (busDomain[pcibus] < 0)
	    continue;

	pciBusInfo[pcibus] = xnfalloc(sizeof(pciBusInfo_t));
	/* The bus scan will re-initialise some fields */
	*pciBusInfo[pcibus] = linuxBusInfo;

	pciNumBuses = pcibus + 1;
    }
}

/* Return PCI allocation sizes linuxPciInit() retrieved */
Bool
xf86GetPciSizeFromOS(PCITAG tag, int Index, int *bits)
{
    unsigned int pcibus, device;

    if ((Index < 0) || (Index >= 7))
	return FALSE;

    pcibus = PCI_BUS_FROM_TAG(tag);
    if ((pcibus >= MAX_PCI_BUSES) || (busDomain[pcibus] < 0))
	return FALSE;

    for (device = 0;  device < MAX_PCI_DEVICES;  device++) {
	if (linuxSize[device].empty || (linuxSize[device].tag != tag))
	    continue;

	if (linuxSize[device].size[Index] < 2)
	    return FALSE;

	*bits = linuxSize[device].size[Index];
	return TRUE;
    }

    return FALSE;
}

static char *
linuxGetPciFileName(PCITAG tag)
{
	static PCITAG namedTag;
	static char pciName[32] = {0, };	/* Should be enough */

	if (!pciName[0] || (tag != namedTag)) {
		long int pcibus, bus, dev, func;

		pcibus = PCI_BUS_FROM_TAG(tag);
		if ((pcibus >= MAX_PCI_BUSES) || (busDomain[pcibus] < 0))
			return "";		/* Bad device */

		if (useDomainInBus)
			bus = PCI_BUS_NO_DOMAIN(pcibus);
		else
			bus = pcibus;

		dev = PCI_DEV_FROM_TAG(tag);
		func = PCI_FUNC_FROM_TAG(tag);

		if (busDomain[pcibus] == 0)
			sprintf(pciName, "/proc/bus/pci/%02lx/%02lx.%1lx",
				bus, dev, func);
		else
			sprintf(pciName, "/proc/bus/pci/%04lx:%02lx/%02lx.%1lx",
				busDomain[pcibus] - 1, bus, dev, func);

		namedTag = tag;
	}

	return pciName;
}

static int
linuxPciOpenFile(PCITAG tag)
{
	static PCITAG	openTag;
	static int	fd = -1;

	if ((fd < 0) || (tag != openTag)) {
		if (fd >= 0)
			close(fd);
		fd = open(linuxGetPciFileName(tag), O_RDWR);
		openTag = tag;
	}

	return fd;
}

static CARD32
linuxPciCfgRead(PCITAG tag, int off)
{
	int	fd;
	CARD32	val = 0xffffffff;

	if ((fd = linuxPciOpenFile(tag)) >= 0) {
		lseek(fd, off, SEEK_SET);
		read(fd, &val, 4);
	}

	return PCI_CPU(val);
}

static void
linuxPciCfgWrite(PCITAG tag, int off, CARD32 val)
{
	int	fd;

	if ((fd = linuxPciOpenFile(tag)) >= 0) {
		lseek(fd, off, SEEK_SET);
		val = PCI_CPU(val);
		write(fd, &val, 4);
	}
}

static void
linuxPciCfgSetBits(PCITAG tag, int off, CARD32 mask, CARD32 bits)
{
	int	fd;
	CARD32	val = 0xffffffff;

	if ((fd = linuxPciOpenFile(tag)) >= 0) {
		lseek(fd, off, SEEK_SET);
		read(fd, &val, 4);
		val = PCI_CPU(val);
		val = (val & ~mask) | (bits & mask);
		val = PCI_CPU(val);
		lseek(fd, off, SEEK_SET);
		write(fd, &val, 4);
	}
}

#if defined(__powerpc__)

#ifndef __NR_pciconfig_iobase
#define __NR_pciconfig_iobase   200
#endif

static ADDRESS
linuxPpcBusAddrToHostAddr(PCITAG tag, PciAddrType type, ADDRESS addr)
{
    if (type == PCI_MEM)
    {
	ADDRESS membase = syscall(__NR_pciconfig_iobase, 1,
		    PCI_BUS_FROM_TAG(tag), PCI_DFN_FROM_TAG(tag));
	return (addr + membase);
    }

    if (type == PCI_IO)
    {
	ADDRESS iobase = syscall(__NR_pciconfig_iobase, 2,
		    PCI_BUS_FROM_TAG(tag), PCI_DFN_FROM_TAG(tag));
	return (addr + iobase);
    }

    return addr;
}

static ADDRESS
linuxPpcHostAddrToBusAddr(PCITAG tag, PciAddrType type, ADDRESS addr)
{
    if (type == PCI_MEM)
    {
	ADDRESS membase = syscall(__NR_pciconfig_iobase, 1,
		    PCI_BUS_FROM_TAG(tag), PCI_DFN_FROM_TAG(tag));
	return (addr - membase);
    }

    if (type == PCI_IO)
    {
	ADDRESS iobase = syscall(__NR_pciconfig_iobase, 2,
		    PCI_BUS_FROM_TAG(tag), PCI_DFN_FROM_TAG(tag));
	return (addr - iobase);
    }

    return addr;
}

#endif /* __powerpc__ */

#ifndef INCLUDE_XF86_NO_DOMAIN

/*
 * Compiling the following simply requires the presence of <linux/pci.c>.
 * Actually running this is another matter altogether...
 *
 * This scheme requires that the kernel allow mmap()'ing of a host bridge's I/O
 * and memory spaces through its /proc/bus/pci/BUS/DFN entry.  Which one is
 * determined by a prior ioctl().
 *
 * For the sparc64 port, this means 2.4.12 or later.  For ppc, this
 * functionality is almost, but not quite there yet.  Alpha and other kernel
 * ports to multi-domain architectures still need to implement this.
 *
 * Obviously, for this to work, such host bridges must advertise themselves on
 * the root bus segment they provide.
 *
 * This scheme is also predicated on the use of an IOADDRESS compatible type to
 * designate I/O addresses.  Although IOADDRESS is defined as an unsigned
 * integral type, it is actually the virtual address of, i.e. a pointer to, the
 * I/O port to access.  And so, the inX/outX macros in "compiler.h" need to be
 * #define'd appropriately (as is done on SPARC's).
 *
 * Another requirement to port this scheme to another multi-domain architecture
 * is to add the appropriate entries in the pciControllerSizes array below.
 *
 * TO DO:  Address the deleterious reaction some host bridges have to master
 *         aborts.  This is already done for secondary PCI buses, but not yet
 *         for accesses to primary buses (except for the SPARC port, where
 *         master aborts are avoided during PCI scans).
 */

/* Workaround for kernel header breakage since 2.5.62 */
#undef  LINUX_MOD_DEVICETABLE_H
#define LINUX_MOD_DEVICETABLE_H 1
#include <linux/pci.h>

#ifndef PCIIOC_BASE		/* Ioctls for /proc/bus/pci/X/Y nodes. */
#define PCIIOC_BASE		(('P' << 24) | ('C' << 16) | ('I' << 8))

/* Get controller for PCI device. */
#define PCIIOC_CONTROLLER	(PCIIOC_BASE | 0x00)
/* Set mmap state to I/O space. */
#define PCIIOC_MMAP_IS_IO	(PCIIOC_BASE | 0x01)
/* Set mmap state to MEM space. */
#define PCIIOC_MMAP_IS_MEM	(PCIIOC_BASE | 0x02)
/* Enable/disable write-combining. */
#define PCIIOC_WRITE_COMBINE	(PCIIOC_BASE | 0x03)

#endif

/* This probably shouldn't be Linux-specific */
static pciConfigPtr
xf86GetPciHostConfigFromTag(PCITAG Tag)
{
    int bus = PCI_BUS_FROM_TAG(Tag);
    pciBusInfo_t *pBusInfo;

    while ((bus < pciNumBuses) && (pBusInfo = pciBusInfo[bus])) {
	if (bus == pBusInfo->primary_bus)
	    return pBusInfo->bridge;
	bus = pBusInfo->primary_bus;
    }

    return NULL;	/* Bad data */
}

/*
 * This is ugly, but until I can extract this information from the kernel,
 * it'll have to do.  The default I/O space size is 64K, and 4G for memory.
 * Anything else needs to go in this table.  (PowerPC folk take note.)
 *
 * Note that Linux/SPARC userland is 32-bit, so 4G overflows to zero here.
 *
 * Please keep this table in ascending vendor/device order.
 */
static struct pciSizes {
    unsigned short vendor, device;
    unsigned long io_size, mem_size;
} pciControllerSizes[] = {
    {
	PCI_VENDOR_SUN, PCI_CHIP_PSYCHO,
	1U << 16, 1U << 31
    },
    {
	PCI_VENDOR_SUN, PCI_CHIP_SCHIZO,
	1U << 24, 1U << 31	/* ??? */
    },
    {
	PCI_VENDOR_SUN, PCI_CHIP_SCHIZO_PLUS,
	1U << 24, 1U << 31	/* ??? */
    },
    {
	PCI_VENDOR_SUN, PCI_CHIP_SABRE,
	1U << 24, (unsigned long)(1ULL << 32)
    },
    {
	PCI_VENDOR_SUN, PCI_CHIP_HUMMINGBIRD,
	1U << 24, (unsigned long)(1ULL << 32)
    },
    {
	PCI_VENDOR_SUN, PCI_CHIP_TOMATILLO,
	1U << 24, 1U << 31	/* ??? */
    }
};
#define NUM_SIZES (sizeof(pciControllerSizes) / sizeof(pciControllerSizes[0]))

static unsigned long
linuxGetIOSize(PCITAG Tag)
{
    pciConfigPtr pPCI;
    int          i;

    /* Find host bridge */
    if ((pPCI = xf86GetPciHostConfigFromTag(Tag))) {
	/* Look up vendor/device */
	for (i = 0;  i < NUM_SIZES;  i++) {
	    if (pPCI->pci_vendor > pciControllerSizes[i].vendor)
		continue;
	    if (pPCI->pci_vendor < pciControllerSizes[i].vendor)
		break;
	    if (pPCI->pci_device > pciControllerSizes[i].device)
		continue;
	    if (pPCI->pci_device < pciControllerSizes[i].device)
		break;
	    return pciControllerSizes[i].io_size;
	}
    }

    return 1U << 16;			/* Default to 64K */
}

static void
linuxGetSizes(PCITAG Tag, unsigned long *io_size, unsigned long *mem_size)
{
    pciConfigPtr pPCI;
    int          i;

    *io_size  = (1U << 16);			/* Default to 64K */
    *mem_size = (unsigned long)(1ULL << 32);	/* Default to 4G */

    /* Find host bridge */
    if ((pPCI = xf86GetPciHostConfigFromTag(Tag))) {
	/* Look up vendor/device */
	for (i = 0;  i < NUM_SIZES;  i++) {
	    if (pPCI->pci_vendor > pciControllerSizes[i].vendor)
		continue;
	    if (pPCI->pci_vendor < pciControllerSizes[i].vendor)
		break;
	    if (pPCI->pci_device > pciControllerSizes[i].device)
		continue;
	    if (pPCI->pci_device < pciControllerSizes[i].device)
		break;
	    *io_size  = pciControllerSizes[i].io_size;
	    *mem_size = pciControllerSizes[i].mem_size;
	    break;
	}
    }
}

int
xf86GetPciDomain(PCITAG Tag)
{
    pciConfigPtr pPCI;
    int fd, result;

    pPCI = xf86GetPciHostConfigFromTag(Tag);

    if (pPCI && (result = PCI_DOM_FROM_BUS(pPCI->busnum)))
	return result;

    if ((fd = linuxPciOpenFile(pPCI ? pPCI->tag : 0)) < 0)
	return 0;

    if ((result = ioctl(fd, PCIIOC_CONTROLLER, 0)) < 0)
	return 0;

    return result + 1;		/* Domain 0 is reserved */
}

static pointer
linuxMapPci(int ScreenNum, int Flags, PCITAG Tag,
	    ADDRESS Base, unsigned long Size, int mmap_ioctl)
{
    do {
	pciConfigPtr pPCI;
	unsigned char *result;
	ADDRESS realBase, Offset;
	int fd, mmapflags, prot;

	xf86InitVidMem();

	pPCI = xf86GetPciHostConfigFromTag(Tag);

	if (((fd = linuxPciOpenFile(pPCI ? pPCI->tag : 0)) < 0) ||
	    (ioctl(fd, mmap_ioctl, 0) < 0))
	    break;

/* Note:  IA-64 doesn't compile this and doesn't need to */
#ifdef __ia64__

# ifndef  MAP_WRITECOMBINED
#  define MAP_WRITECOMBINED 0x00010000
# endif
# ifndef  MAP_NONCACHED
#  define MAP_NONCACHED     0x00020000
# endif

	if (Flags & VIDMEM_FRAMEBUFFER)
	    mmapflags = MAP_SHARED | MAP_WRITECOMBINED;
	else
	    mmapflags = MAP_SHARED | MAP_NONCACHED

#else /* !__ia64__ */

	mmapflags = (Flags & VIDMEM_FRAMEBUFFER) / VIDMEM_FRAMEBUFFER;

	if (ioctl(fd, PCIIOC_WRITE_COMBINE, mmapflags) < 0)
	    break;

	mmapflags = MAP_SHARED;

#endif /* ?__ia64__ */

	/* Align to page boundary */
	realBase = Base & ~(getpagesize() - 1);
	Offset = Base - realBase;

	if (Flags & VIDMEM_READONLY)
	    prot = PROT_READ;
	else
	    prot = PROT_READ | PROT_WRITE;

	result = mmap(NULL, Size + Offset, prot, mmapflags, fd, realBase);

	if (!result || ((pointer)result == MAP_FAILED))
	    FatalError("linuxMapPci() mmap failure:  %s\n", strerror(errno));

	xf86MakeNewMapping(ScreenNum, Flags, realBase, Size + Offset, result);

	return result + Offset;
    } while (0);

    if (mmap_ioctl == PCIIOC_MMAP_IS_MEM)
	return xf86MapVidMem(ScreenNum, Flags, Base, Size);

    return NULL;
}

pointer
xf86MapDomainMemory(int ScreenNum, int Flags, PCITAG Tag,
		    ADDRESS Base, unsigned long Size)
{
    return linuxMapPci(ScreenNum, Flags, Tag, Base, Size, PCIIOC_MMAP_IS_MEM);
}

#define MAX_DOMAINS 257
static pointer DomainMmappedIO[MAX_DOMAINS];

/* This has no means of returning failure, so all errors are fatal */
IOADDRESS
xf86MapDomainIO(int ScreenNum, int Flags, PCITAG Tag,
		IOADDRESS Base, unsigned long Size)
{
    int domain = xf86GetPciDomain(Tag);

    if ((domain <= 0) || (domain >= MAX_DOMAINS))
	FatalError("xf86MapDomainIO():  domain out of range\n");

    /* Permanently map all of I/O space */
    if (!DomainMmappedIO[domain]) {
	DomainMmappedIO[domain] = linuxMapPci(ScreenNum, Flags, Tag,
					      0, linuxGetIOSize(Tag),
					      PCIIOC_MMAP_IS_IO);
	if (!DomainMmappedIO[domain])
	    FatalError("xf86MapDomainIO():  mmap() failure\n");
    }

    return (IOADDRESS)DomainMmappedIO[domain] + Base;
}

int
xf86ReadDomainMemory(PCITAG Tag, ADDRESS Base, int Len, unsigned char *Buf)
{
    unsigned char *ptr, *src;
    ADDRESS offset;
    unsigned long size;
    int len, pagemask = getpagesize() - 1;

    /* Ensure page boundaries */
    offset = Base & ~pagemask;
    size = ((Base + Len + pagemask) & ~pagemask) - offset;

    ptr = xf86MapDomainMemory(-1, VIDMEM_READONLY, Tag, offset, size);

    if (!ptr)
	return -1;

    /* Using memcpy() here can hang the system */
    src = ptr + (Base - offset);
    for (len = Len;  len-- > 0;)
	*Buf++ = *src++;

    xf86UnMapVidMem(-1, ptr, size);

    return Len;
}

Bool
xf86LocatePciMemoryArea(PCITAG Tag, char **devName, unsigned int *devOffset,
			unsigned int *fbSize, unsigned int *fbOffset,
			unsigned int *flags)
{
    pciConfigPtr pPCI;
    unsigned int offset;

    if (!devName || !devOffset || devOffset[1])
	return FALSE;

    offset = devOffset[0];

    if (fbOffset) {
	if ((offset ^ (unsigned int)(-1L)) < *fbOffset)
	    return FALSE;

	offset += *fbOffset;
    }

    if (fbSize && ((offset ^ (unsigned int)(-1L)) < *fbSize))
	return FALSE;

    pPCI = xf86GetPciHostConfigFromTag(Tag);
    if (!pPCI)
	return TRUE;

    *devName = linuxGetPciFileName(pPCI->tag);
    if (flags)
	*flags = 0;

    return TRUE;
}

resPtr
xf86BusAccWindowsFromOS(void)
{
    pciConfigPtr  *ppPCI, pPCI;
    resPtr        pRes = NULL;
    resRange      range;
    unsigned long io_size, mem_size;
    int           domain;

    if ((ppPCI = xf86scanpci(0))) {
	for (;  (pPCI = *ppPCI);  ppPCI++) {
	    if ((pPCI->pci_base_class != PCI_CLASS_BRIDGE) ||
		(pPCI->pci_sub_class  != PCI_SUBCLASS_BRIDGE_HOST))
		continue;

	    domain = xf86GetPciDomain(pPCI->tag);
	    linuxGetSizes(pPCI->tag, &io_size, &mem_size);

	    RANGE(range, 0, (ADDRESS)(mem_size - 1),
		  RANGE_TYPE(ResExcMemBlock, domain));
	    pRes = xf86AddResToList(pRes, &range, -1);

	    RANGE(range, 0, (IOADDRESS)(io_size - 1),
		  RANGE_TYPE(ResExcIoBlock, domain));
	    pRes = xf86AddResToList(pRes, &range, -1);

	    if (domain <= 0)
		break;
	}
    }

    return pRes;
}

resPtr
xf86PciBusAccWindowsFromOS(void)
{
    pciConfigPtr  *ppPCI, pPCI;
    resPtr        pRes = NULL;
    resRange      range;
    unsigned long io_size, mem_size;
    int           domain;

    if ((ppPCI = xf86scanpci(0))) {
	for (;  (pPCI = *ppPCI);  ppPCI++) {
	    if ((pPCI->pci_base_class != PCI_CLASS_BRIDGE) ||
		(pPCI->pci_sub_class  != PCI_SUBCLASS_BRIDGE_HOST))
		continue;

	    domain = xf86GetPciDomain(pPCI->tag);
	    linuxGetSizes(pPCI->tag, &io_size, &mem_size);

	    RANGE(range, 0, (ADDRESS)(mem_size - 1),
		  RANGE_TYPE(ResExcMemBlock, domain));
	    pRes = xf86AddResToList(pRes, &range, -1);

	    RANGE(range, 0, (IOADDRESS)(io_size - 1),
		  RANGE_TYPE(ResExcIoBlock, domain));
	    pRes = xf86AddResToList(pRes, &range, -1);

	    if (domain <= 0)
		break;
	}
    }

    return pRes;
}


resPtr
xf86AccResFromOS(resPtr pRes)
{
    pciConfigPtr  *ppPCI, pPCI;
    resRange      range;
    unsigned long io_size, mem_size;
    int           domain;

    if ((ppPCI = xf86scanpci(0))) {
	for (;  (pPCI = *ppPCI);  ppPCI++) {
	    if ((pPCI->pci_base_class != PCI_CLASS_BRIDGE) ||
		(pPCI->pci_sub_class  != PCI_SUBCLASS_BRIDGE_HOST))
		continue;

	    domain = xf86GetPciDomain(pPCI->tag);
	    linuxGetSizes(pPCI->tag, &io_size, &mem_size);

	    /*
	     * At minimum, the top and bottom resources must be claimed, so
	     * that resources that are (or appear to be) unallocated can be
	     * relocated.
	     */
	    RANGE(range, 0x00000000u, 0x0009ffffu,
		  RANGE_TYPE(ResExcMemBlock, domain));
	    pRes = xf86AddResToList(pRes, &range, -1);
	    RANGE(range, 0x000c0000u, 0x000effffu,
		  RANGE_TYPE(ResExcMemBlock, domain));
	    pRes = xf86AddResToList(pRes, &range, -1);
	    RANGE(range, 0x000f0000u, 0x000fffffu,
		  RANGE_TYPE(ResExcMemBlock, domain));
	    pRes = xf86AddResToList(pRes, &range, -1);

	    RANGE(range, (ADDRESS)(mem_size - 1), (ADDRESS)(mem_size - 1),
		  RANGE_TYPE(ResExcMemBlock, domain));
	    pRes = xf86AddResToList(pRes, &range, -1);

	    RANGE(range, 0x00000000u, 0x00000000u,
		  RANGE_TYPE(ResExcIoBlock, domain));
	    pRes = xf86AddResToList(pRes, &range, -1);
	    RANGE(range, (IOADDRESS)(io_size - 1), (IOADDRESS)(io_size - 1),
		  RANGE_TYPE(ResExcIoBlock, domain));
	    pRes = xf86AddResToList(pRes, &range, -1);

	    if (domain <= 0)
		break;
	}
    }

    return pRes;
}

#endif /* !INCLUDE_XF86_NO_DOMAIN */
