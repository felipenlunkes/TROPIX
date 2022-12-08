/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/bus/sparcPci.c,v 1.31 2007/07/10 19:08:42 tsi Exp $ */
/*
 * Copyright (C) 2001-2007 The XFree86 Project, Inc.
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

#include "xf86.h"
#include "xf86Priv.h"
#define NEED_OS_RAC_PROTOS
#include "xf86_OSlib.h"
#include "Pci.h"
#include "xf86sbusBus.h"

#if defined(sun) || defined(__OpenBSD__)

#if defined(__OpenBSD__)
#define apertureDevName "/dev/mem"
#else
extern char *apertureDevName;
#endif

static unsigned long long pagemask;
static int apertureFd = -1;

/*
 * A version of xf86MapVidMem() that allows for 64-bit displacements (but not
 * sizes).  Areas thus mapped can be unmapped by xf86UnMapVidMem().
 */
static pointer
sparcMapAperture(int iScreen, int Flags,
		 unsigned long long Base, unsigned long Size)
{
    pointer result;
    static int lastFlags = 0;

    /* Assume both Base & Size are multiples of the page size */

    if ((apertureFd < 0) || (Flags != lastFlags)) {
	if (apertureFd >= 0)
	    close(apertureFd);
	lastFlags = Flags;
	apertureFd = open(apertureDevName,
	    (Flags & VIDMEM_READONLY) ? O_RDONLY : O_RDWR);
	if (apertureFd < 0) {
	    ErrorF("sparcMapAperture:  open failure:  %s\n", strerror(errno));
	    return MAP_FAILED;
	}
    }

    result = mmap(NULL, Size,
		  (Flags & VIDMEM_READONLY) ?
		      PROT_READ : (PROT_READ | PROT_WRITE),
		  MAP_SHARED, apertureFd, (off_t)Base);

    if (result == MAP_FAILED) {
	ErrorF("sparcMapAperture:  mmap failure:  %s\n", strerror(errno));
	return MAP_FAILED;
    }

#if !defined(sun) && !defined(__bsdi__) && \
    !(defined(MACH) && defined(__GNU__))
    /* Register this mapping */
    xf86MakeNewMapping(iScreen, Flags, Base, Size, result);
#endif

    return result;
}

/*
 * Platform-specific bus privates.
 */
typedef struct _sparcDomainRec {
    unsigned long long io_addr, io_size;
    unsigned long long mem_addr, mem_size;
    pointer pci, io;
    int bus_min, bus_max;
    int tagMultiplier, maxOffset;
    unsigned char dfn_mask[256 / 8];
} sparcDomainRec, *sparcDomainPtr;

#define SetBitInMap(bit, map) \
    do { \
	int _bit = (bit); \
	(map)[_bit >> 3] |= 1 << (_bit & 7); \
    } while (0)

#define IsBitSetInMap(bit, map) \
    ((map)[(bit) >> 3] & (1 << ((bit) & 7)))

/*
 * Domain 0 is reserved for the one that represents the system as a whole, i.e.
 * the one without any resource relocations.
 */
#define MAX_DOMAINS (MAX_PCI_BUSES / 256)
static sparcDomainPtr xf86DomainInfo[MAX_DOMAINS];
static int            pciNumDomains = 1;

/* Variables to which this is assigned must be declared volatile */
#define PciReg(domain, tag, off, type) \
    *(volatile type *)(pointer)((char *)((domain)->pci) + \
	((PCI_TAG_NO_DOMAIN(tag) * (domain)->tagMultiplier) | (off)))

/* Generic SPARC PCI access functions */
static CARD32
sparcPciCfgRead32(PCITAG tag, int off)
{
    pciBusInfo_t    *pBusInfo;
    sparcDomainPtr  pDomain;
    volatile CARD32 result = (CARD32)(-1);	/* Must be volatile */
    int             bus;

    if ((off >= 0) && !(off & 3) &&
	((bus = PCI_BUS_FROM_TAG(tag)) < pciNumBuses) &&
	(pBusInfo = pciBusInfo[bus]) && (pDomain = pBusInfo->pciBusPriv) &&
	(off < pDomain->maxOffset) &&
	(bus >= pDomain->bus_min) && (bus < pDomain->bus_max) &&
	((bus > pDomain->bus_min) ||
	 IsBitSetInMap(PCI_DFN_FROM_TAG(tag), pDomain->dfn_mask))) {
	result = PciReg(pDomain, tag, off, CARD32);

	result = PCI_CPU(result);
    }

    return result;
}

static void
sparcPciCfgWrite32(PCITAG tag, int off, CARD32 val)
{
    pciBusInfo_t   *pBusInfo;
    sparcDomainPtr pDomain;
    int            bus;

    if ((off < 0) || (off & 3) ||
	((bus = PCI_BUS_FROM_TAG(tag)) >= pciNumBuses) ||
	!(pBusInfo = pciBusInfo[bus]) || !(pDomain = pBusInfo->pciBusPriv) ||
	(off >= pDomain->maxOffset) ||
	(bus < pDomain->bus_min) || (bus >= pDomain->bus_max) ||
	((bus == pDomain->bus_min) &&
	 !IsBitSetInMap(PCI_DFN_FROM_TAG(tag), pDomain->dfn_mask)))
	return;

    val = PCI_CPU(val);
    PciReg(pDomain, tag, off, CARD32) = val;
}

static void
sparcPciCfgSetBits32(PCITAG tag, int off, CARD32 mask, CARD32 bits)
{
    CARD32 PciVal;

    PciVal = sparcPciCfgRead32(tag, off);
    PciVal &= ~mask;
    PciVal |= bits;
    sparcPciCfgWrite32(tag, off, PciVal);
}

static pciBusFuncs_t sparcPCIFunctions =
{
    sparcPciCfgRead32,
    sparcPciCfgWrite32,
    sparcPciCfgSetBits32,
    pciAddrNOOP,
    pciAddrNOOP
};

/*
 * Sabre-specific versions of the above because of its peculiar access size
 * requirements.
 */
static CARD32
sabrePciCfgRead32(PCITAG tag, int off)
{
    pciBusInfo_t    *pBusInfo;
    sparcDomainPtr  pDomain;
    volatile CARD32 result;			/* Must be volatile */
    int             bus;

    if (PCI_BDEV_FROM_TAG(tag))
	return sparcPciCfgRead32(tag, off);

    if (PCI_FUNC_FROM_TAG(tag) || (off < 0) || (off > 252) || (off & 3) ||
	((bus = PCI_BUS_FROM_TAG(tag)) >= pciNumBuses) ||
	!(pBusInfo = pciBusInfo[bus]) || !(pDomain = pBusInfo->pciBusPriv) ||
	(bus != pDomain->bus_min))
	return (CARD32)(-1);

    if (off < 8) {
	result = (PciReg(pDomain, tag, off, CARD16) << 16) |
		  PciReg(pDomain, tag, off + 2, CARD16);
	return PCI_CPU(result);
    }

    result = (PciReg(pDomain, tag, off + 3, CARD8) << 24) |
	     (PciReg(pDomain, tag, off + 2, CARD8) << 16) |
	     (PciReg(pDomain, tag, off + 1, CARD8) <<  8) |
	     (PciReg(pDomain, tag, off    , CARD8)      );
    return result;
}

static void
sabrePciCfgWrite32(PCITAG tag, int off, CARD32 val)
{
    pciBusInfo_t   *pBusInfo;
    sparcDomainPtr pDomain;
    int            bus;

    if (PCI_BDEV_FROM_TAG(tag))
	sparcPciCfgWrite32(tag, off, val);
    else if (!PCI_FUNC_FROM_TAG(tag) &&
	     (off >= 0) && (off <= 252) && !(off & 3) &&
	     ((bus = PCI_BUS_FROM_TAG(tag)) < pciNumBuses) &&
	     (pBusInfo = pciBusInfo[bus]) &&
	     (pDomain = pBusInfo->pciBusPriv) &&
	     (bus == pDomain->bus_min)) {
	if (off < 8) {
	    val = PCI_CPU(val);
	    PciReg(pDomain, tag, off    , CARD16) = val >> 16;
	    PciReg(pDomain, tag, off + 2, CARD16) = val;
	} else {
	    PciReg(pDomain, tag, off    , CARD8) = val;
	    PciReg(pDomain, tag, off + 1, CARD8) = val >> 8;
	    PciReg(pDomain, tag, off + 2, CARD8) = val >> 16;
	    PciReg(pDomain, tag, off + 3, CARD8) = val >> 24;
	}
    }
}

static void
sabrePciCfgSetBits32(PCITAG tag, int off, CARD32 mask, CARD32 bits)
{
    CARD32 PciVal;

    PciVal = sabrePciCfgRead32(tag, off);
    PciVal &= ~mask;
    PciVal |= bits;
    sabrePciCfgWrite32(tag, off, PciVal);
}

static pciBusFuncs_t sabrePCIFunctions =
{
    sabrePciCfgRead32,
    sabrePciCfgWrite32,
    sabrePciCfgSetBits32,
    pciAddrNOOP,
    pciAddrNOOP
};


static struct {
    CARD32 tag;
    int size;
} *pAddressSizes = NULL;
static int nAddressSizes = 0;

/*
 * Extract base size information from "assigned-addresses" properties.
 */

static void
sparcAssignedAddresses(sparcDomainPtr pDomain, int node)
{
    char *prop_val;
    int prop_len;

    /* Retrieve and validate "assigned-addresses" property */
    prop_val = promGetProperty("assigned-addresses", &prop_len);
    if (prop_val && !(prop_len % 20)) {
	prop_len /= 20;
	for (;  prop_len--;  prop_val += 20) {
	    if (((unsigned char)prop_val[1] < pDomain->bus_min) ||
		((unsigned char)prop_val[1] > pDomain->bus_max) ||
		(prop_val[3] & 0x3) || (prop_val[3] < PCI_MAP_REG_START) ||
		((CARD32 *)prop_val)[1] || ((CARD32 *)prop_val)[3] ||
		(((CARD32 *)prop_val)[4] < 4) ||
		(((CARD32 *)prop_val)[4] & (((CARD32 *)prop_val)[4] - 1)) ||
		(((CARD32 *)prop_val)[2] & (((CARD32 *)prop_val)[4] - 1)))
		continue;

	    if ((prop_val[3] >= PCI_MAP_REG_END) &&
		(prop_val[3] != PCI_MAP_ROM_REG) &&
		(prop_val[3] != PCI_PCI_BRIDGE_ROM_REG))
		continue;

	    prop_val[0] = pciNumDomains;
	    pAddressSizes = xnfrealloc(pAddressSizes,
		sizeof(*pAddressSizes) * (nAddressSizes + 1));
	    pAddressSizes[nAddressSizes].tag = ((CARD32 *)prop_val)[0];
	    for (pAddressSizes[nAddressSizes].size = -1;
		 ((CARD32 *)prop_val)[4];
		 ((CARD32 *)prop_val)[4] >>= 1)
		pAddressSizes[nAddressSizes].size++;
	    nAddressSizes++;
	}
    }

    /* Retrieve and validate "class-code" property */
    prop_val = promGetProperty("class-code", &prop_len);
    if (prop_val && (prop_len == 4) &&
	(prop_val[0] == 0) && (prop_val[1] == PCI_CLASS_BRIDGE) &&
	((prop_val[2] == PCI_SUBCLASS_BRIDGE_PCI) ||
	 (prop_val[2] == PCI_SUBCLASS_BRIDGE_CARDBUS)))
	for (node = promGetChild(node);  node;  node = promGetSibling(node))
	    sparcAssignedAddresses(pDomain, node);
}

/* Return the PCI allocation sizes derived above */
Bool
xf86GetPciSizeFromOS(PCITAG tag, int Index, int *bits)
{
    int i;

    if ((Index < 0) || (Index > 7) || !pAddressSizes || (tag != (CARD32)tag))
	return FALSE;

    switch (Index) {
    case 6:
	tag |= PCI_MAP_ROM_REG;
	break;
    case 7:
	tag |= PCI_PCI_BRIDGE_ROM_REG;
	break;
    default:
	tag |= PCI_MAP_REG_START + (Index * 4);
	break;
    }

    for (i = 0;  i < nAddressSizes;  i++) {
	if (tag == pAddressSizes[i].tag) {
	    *bits = pAddressSizes[i].size;
	    return TRUE;
	}
    }

    return FALSE;
}

/* Scan PROM for all PCI host bridges in the system */
void
sparcPciInit(void)
{
    int node, node2;

    if (!xf86LinearVidMem())
	return;

    apertureFd = open(apertureDevName, O_RDWR);
    if (apertureFd < 0) {
	xf86Msg(X_ERROR,
	    "sparcPciInit:  open failure:  %s\n", strerror(errno));
	return;
    }

    sparcPromInit();
    pagemask = xf86getpagesize() - 1;

    for (node = promGetChild(promRootNode);
	 node;
	 node = promGetSibling(node)) {
	unsigned long long pci_addr, pci_size, phys_addr, phys_size;
	sparcDomainRec     domain;
	sparcDomainPtr     pDomain;
	pciBusFuncs_p      pFunctions;
	char               *prop_val;
	int                prop_len, bus;
	char               shared_pci;

	prop_val = promGetProperty("name", &prop_len);
	if (!prop_val || (prop_len < 3))
	    continue;

	prop_val[prop_len] = '\0';
	if (strcmp(prop_val, "pci") && strcmp(prop_val, "pciex"))
	    continue;

	prop_val = promGetProperty("model", &prop_len);
	if (!prop_val || (prop_len <= 0)) {
	    prop_val = promGetProperty("compatible", &prop_len);
	    if (!prop_val || (prop_len <= 0))
		continue;
	}

	/* Ensure NUL-termination and only check the first name */
	prop_val[prop_len] = '\0';
	if (!strlen(prop_val))
	    continue;

	if (strcmp("SUNW,sabre",   prop_val) &&
	    strcmp("pci108e,a000", prop_val) &&
	    strcmp("pci108e,a001", prop_val))
	    pFunctions = &sparcPCIFunctions;
	else
	    pFunctions = &sabrePCIFunctions;

	if (strcmp("SUNW,psycho", prop_val) &&
	    strcmp("pci108e,8000", prop_val))
	    shared_pci = 0;
	else
	    shared_pci = 1;

	xf86Msg(X_INFO, "PCI host bridge found (\"%s\")\n", prop_val);

	/* Get "bus-range" property */
	prop_val = promGetProperty("bus-range", &prop_len);
	if (!prop_val || (prop_len != 8) ||
	    (((unsigned int *)prop_val)[1] >= 256) ||
	    (((unsigned int *)prop_val)[0] > ((unsigned int *)prop_val)[1]))
	    continue;

	(void)memset(&domain, 0, sizeof(domain));

	domain.bus_min = ((int *)prop_val)[0];
	domain.bus_max = ((int *)prop_val)[1];

	/* Retrieve and validate "ranges" property */
	prop_val = promGetProperty("ranges", &prop_len);
	if (!prop_val || (prop_len <= 0) || (prop_len % 28))
	    continue;

	/* Extract address space location and size from "ranges" property */
	pci_addr = pci_size = 0;
	for (prop_len /= 28;  prop_len--;  prop_val += 28) {
	   /* Address space size must be a power of two */
	   phys_size =
		((unsigned long long)((unsigned int *)prop_val)[5] << 32) |
		(unsigned long long)((unsigned int *)prop_val)[6];
	   if (!phys_size || (phys_size & (phys_size - 1)))
		goto nextNode;

	   /* Address space must be size-aligned */
	   phys_addr =
		((unsigned long long)((unsigned int *)prop_val)[3] << 32) |
		(unsigned long long)((unsigned int *)prop_val)[4];
	   if (phys_addr % phys_size)
		goto nextNode;

	   switch (prop_val[0] & 0x03) {
	   case 0:	/* PCI configuration space */
		if ((pci_addr == phys_addr) && (pci_size == phys_size))
		    break;

		if (pci_size)
		    goto nextNode;
		if (shared_pci) {
		    phys_size <<= 1;
		    if (!phys_size)
			goto nextNode;
		}
		pci_addr = phys_addr;
		pci_size = phys_size;
		break;

	   case 1:	/* I/O space */
		if ((domain.io_addr == phys_addr) &&
		    (domain.io_size == phys_size))
		    break;

		if (domain.io_size)
		    goto nextNode;
		domain.io_addr = phys_addr;
		domain.io_size = phys_size;
		break;

	   case 2:	/* 32-bit memory space */
	   case 3:	/* 64-bit memory space */
	   default:	/* Muffle compiler */
		if ((domain.mem_addr == phys_addr) &&
		    (domain.mem_size == phys_size))
		    break;

		if (domain.mem_size)
		    goto nextNode;
		domain.mem_addr = phys_addr;
		domain.mem_size = phys_size;
		break;
	   }
	}

	/* Enforce minimum address space sizes */
	if (!domain.mem_size ||
	    (domain.io_size < 0x00010000ull) ||
	    (pci_size < 0x01000000ull))
	    continue;

	if (pciNumDomains >= MAX_DOMAINS) {
	    xf86Msg(X_ERROR, "MAX_PCI_BUSES needs to be increased to"
		    " accomodate this host bridge\n");
	    pciNumDomains++;
	    continue;
	}

	domain.tagMultiplier = pci_size >> 24;
	domain.maxOffset = domain.tagMultiplier << 8;

	/* Only mmap as much PCI configuration as we need */
	phys_addr = pci_addr +
	    (PCI_MAKE_TAG(domain.bus_min, 0, 0) * domain.tagMultiplier);
	phys_addr &= ~pagemask;
	phys_size = pci_addr +
	    (PCI_MAKE_TAG(domain.bus_max + 1, 0, 0) * domain.tagMultiplier);
	phys_size += pagemask;
	phys_size &= ~pagemask;
	phys_size -= phys_addr;

	domain.pci = sparcMapAperture(-1, VIDMEM_MMIO, phys_addr, phys_size);
	if (domain.pci == MAP_FAILED)
	    continue;

	domain.pci = (char *)domain.pci - (phys_addr - pci_addr);

	xf86MsgVerb(X_INFO, 4, "Adding PCI domain %d:\n", pciNumDomains);
	xf86MsgVerb(X_INFO, 4,
	    "PCI Configuration space: 0x%016llx, size: 0x%09llx\n",
	    pci_addr, pci_size);
	xf86MsgVerb(X_INFO, 4,
	    "PCI Input/Output space:  0x%016llx, size: 0x%09llx\n",
	    domain.io_addr, domain.io_size);
	xf86MsgVerb(X_INFO, 4,
	    "PCI Memory space:        0x%016llx, size: 0x%09llx\n",
	    domain.mem_addr, domain.mem_size);
	xf86MsgVerb(X_INFO, 4, "PCI Bus range:           %d-%d\n",
	    domain.bus_min, domain.bus_max);

	/* Allocate a domain record */
	pDomain = xnfalloc(sizeof(sparcDomainRec));
	*pDomain = domain;

	/*
	 * Allocate and prime pciBusInfo records.  These are allocated one at a
	 * time because those for empty buses are eventually released.
	 */
	bus = pDomain->bus_min =
	    PCI_MAKE_BUS(pciNumDomains, domain.bus_min);
	pciNumBuses = pDomain->bus_max =
	    PCI_MAKE_BUS(pciNumDomains, domain.bus_max) + 1;

	pciBusInfo[bus] = xnfcalloc(1, sizeof(pciBusInfo_t));
	pciBusInfo[bus]->configMech = PCI_CFG_MECH_OTHER;
	pciBusInfo[bus]->numDevices = 32;
	pciBusInfo[bus]->funcs = pFunctions;
	pciBusInfo[bus]->pciBusPriv = pDomain;
	while (++bus < pciNumBuses) {
	    pciBusInfo[bus] = xnfalloc(sizeof(pciBusInfo_t));
	    *(pciBusInfo[bus]) = *(pciBusInfo[bus - 1]);
	    pciBusInfo[bus]->funcs = &sparcPCIFunctions;
	}

	/* Next domain, please... */
	xf86DomainInfo[pciNumDomains] = pDomain;

	/*
	 * OK, enough of the straight-forward stuff.  Time to deal with some
	 * brokenness...
	 *
	 * The PCI specs require that when a bus transaction remains unclaimed
	 * for too long, the master entity on that bus is to cancel the
	 * transaction it issued, or passed on, with a master abort.  Two
	 * outcomes are possible:
	 *
	 * - the master abort can be treated as an error that is propogated
	 *   back through the bus tree to the entity that ultimately originated
	 *   the transaction; or
	 * - the transaction can be allowed to complete normally, which means
	 *   that writes are ignored and reads return all ones.
	 *
	 * In the first case, if the CPU happens to be at the tail end of the
	 * tree path through one of its host bridges, it will be told there is
	 * a hardware mal-function, despite being generated by software.
	 *
	 * For a software function (be it firmware, OS or userland application)
	 * to determine how a PCI bus tree is populated, it must be able to
	 * detect when master aborts occur.  Obviously, PCI discovery is much
	 * simpler when master aborts are allowed to complete normally.
	 *
	 * Unfortunately, a number of PCI implementations have chosen to treat
	 * master aborts as severe errors.  The net effect is to cripple PCI
	 * discovery algorithms in userland.
	 *
	 * On SPARCs, master aborts cause a number of different behaviours,
	 * including delivering a signal to the userland application, rebooting
	 * the system, "dropping down" to firmware, or, worst of all, bus
	 * lockouts.  Even in the first case, the SIGBUS signal that is
	 * eventually generated isn't delivered in a timely enough fashion to
	 * allow an application to reliably detect the master abort that
	 * ultimately caused it.
	 *
	 * This can be somewhat mitigated.  On all architectures, master aborts
	 * that occur on secondary buses can be forced to complete normally
	 * because the PCI-to-PCI bridges that serve them are governed by an
	 * industry-wide specification.  (This is just another way of saying
	 * that whatever justification there might be for erroring out master
	 * aborts is deemed by the industry as insufficient to generate more
	 * PCI non-compliance than there already is...)
	 *
	 * This leaves us with master aborts that occur on primary buses.
	 * There is no specification for host-to-PCI bridges.  Bridges used in
	 * SPARCs can be told to ignore all PCI errors, but not specifically
	 * master aborts.  Not only is this too coarse-grained, but
	 * master-aborted read transactions on the primary bus end up returning
	 * garbage rather than all ones.
	 *
	 * I have elected to work around this the only way I can think of doing
	 * so right now.  The following scans an additional PROM level and
	 * builds a device/function map for the primary bus.  I can only hope
	 * this PROM information represents all devices on the primary bus,
	 * rather than only a subset of them.
	 *
	 * Master aborts are useful in other ways too, that are not addressed
	 * here.  These include determining whether or not a domain provides
	 * VGA, or if a PCI device actually implements PCI disablement.
	 *
	 * ---  TSI @ UQV  2001.09.19
	 */
	for (node2 = promGetChild(node);
	     node2;
	     node2 = promGetSibling(node2)) {
	    /* Get "reg" property */
	    prop_val = promGetProperty("reg", &prop_len);
	    if (prop_val && !(prop_len % 20)) {

		/*
		 * It's unnecessary to scan the entire "reg" property, but I'll
		 * do so anyway.
		 */
		prop_len /= 20;
		for (;  prop_len--;  prop_val += 20)
		    SetBitInMap(PCI_DFN_FROM_TAG(*(CARD32 *)prop_val),
			pDomain->dfn_mask);
	    }

	    /* Scan "assigned-addresses" properties for resource sizes */
	    sparcAssignedAddresses(&domain, node2);
	}

	/* Assume the host bridge is device 0, function 0 on its bus */
	SetBitInMap(0, pDomain->dfn_mask);

	pciNumDomains++;

nextNode:;
    }

    sparcPromClose();

    if (pciNumDomains >= MAX_DOMAINS)
	xf86Msg(X_ERROR, "MAX_PCI_BUSES needs to be increased to %d to"
		" accomodate all host bridges in this system\n",
		pciNumDomains * 256);

    close(apertureFd);
    apertureFd = -1;
}

#ifndef INCLUDE_XF86_NO_DOMAIN

int
xf86GetPciDomain(PCITAG Tag)
{
    return PCI_DOM_FROM_TAG(Tag);
}

pointer
xf86MapDomainMemory(int ScreenNum, int Flags, PCITAG Tag,
		    ADDRESS Base, unsigned long Size)
{
    sparcDomainPtr pDomain;
    pointer        result;
    int            domain = PCI_DOM_FROM_TAG(Tag);

    if ((domain <= 0) || (domain >= pciNumDomains) ||
	!(pDomain = xf86DomainInfo[domain]) ||
	(((unsigned long long)Base + Size) > pDomain->mem_size))
	FatalError("xf86MapDomainMemory() called with invalid parameters.\n");

    result = sparcMapAperture(ScreenNum, Flags, pDomain->mem_addr + Base, Size);

    if (result == MAP_FAILED)
	FatalError("xf86MapDomainMemory():  sparcMapAperture() failure.\n");

    if (apertureFd >= 0) {
	close(apertureFd);
	apertureFd = -1;
    }

    return result;
}

IOADDRESS
xf86MapDomainIO(int ScreenNum, int Flags, PCITAG Tag,
		IOADDRESS Base, unsigned long Size)
{
    sparcDomainPtr pDomain;
    int            domain = PCI_DOM_FROM_TAG(Tag);

    if ((domain <= 0) || (domain >= pciNumDomains) ||
	!(pDomain = xf86DomainInfo[domain]) ||
	(((unsigned long long)Base + Size) > pDomain->io_size))
	FatalError("xf86MapDomainIO() called with invalid parameters.\n");

    /* Permanently map all of I/O space */
    if (!pDomain->io) {
	pDomain->io = sparcMapAperture(ScreenNum, Flags,
	    pDomain->io_addr, pDomain->io_size);

	if (pDomain->io == MAP_FAILED)
	    FatalError("xf86MapDomainIO():  sparcMapAperture() failure.\n");

	if (apertureFd >= 0) {
	    close(apertureFd);
	    apertureFd = -1;
	}
    }

    return (IOADDRESS)pDomain->io + Base;
}

int
xf86ReadDomainMemory(PCITAG Tag, ADDRESS Base, int Len, unsigned char *Buf)
{
    unsigned char *ptr, *src;
    ADDRESS offset;
    unsigned long size;
    int len;

    /* Ensure page boundaries */
    offset = Base & ~pagemask;
    size = ((Base + Len + pagemask) & ~pagemask) - offset;

    ptr = xf86MapDomainMemory(-1, VIDMEM_READONLY, Tag, offset, size);

    /* Using memcpy() here hangs the system */
    src = ptr + (Base - offset);
    for (len = Len;  len-- > 0;)
	    *Buf++ = *src++;

    xf86UnMapVidMem(-1, ptr, size);

    return Len;
}

resPtr
xf86BusAccWindowsFromOS(void)
{
    sparcDomainPtr pDomain;
    resPtr         pRes = NULL;
    resRange       range;
    int            domain;

    for (domain = 1;  domain < pciNumDomains;  domain++) {
	if (!(pDomain = xf86DomainInfo[domain]))
	    continue;

	RANGE(range, 0, pDomain->mem_size - 1,
	      RANGE_TYPE(ResExcMemBlock, domain));
	pRes = xf86AddResToList(pRes, &range, -1);

	RANGE(range, 0, pDomain->io_size - 1,
	      RANGE_TYPE(ResExcIoBlock, domain));
	pRes = xf86AddResToList(pRes, &range, -1);
    }

    return pRes;
}

resPtr
xf86PciBusAccWindowsFromOS(void)
{
    sparcDomainPtr pDomain;
    resPtr         pRes = NULL;
    resRange       range;
    int            domain;

    for (domain = 1;  domain < pciNumDomains;  domain++) {
	if (!(pDomain = xf86DomainInfo[domain]))
	    continue;

	RANGE(range, 0, pDomain->mem_size - 1,
	      RANGE_TYPE(ResExcMemBlock, domain));
	pRes = xf86AddResToList(pRes, &range, -1);

	RANGE(range, 0, pDomain->io_size - 1,
	      RANGE_TYPE(ResExcIoBlock, domain));
	pRes = xf86AddResToList(pRes, &range, -1);
    }

    return pRes;
}

resPtr
xf86AccResFromOS(resPtr pRes)
{
    sparcDomainPtr pDomain;
    resRange       range;
    int            domain;

    for (domain = 1;  domain < pciNumDomains;  domain++) {
	if (!(pDomain = xf86DomainInfo[domain]))
	    continue;

	/*
	 * At minimum, the top and bottom resources must be claimed, so that
	 * resources that are (or appear to be) unallocated can be relocated.
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

	RANGE(range, pDomain->mem_size - 1, pDomain->mem_size - 1,
	      RANGE_TYPE(ResExcMemBlock, domain));
	pRes = xf86AddResToList(pRes, &range, -1);

	RANGE(range, 0x00000000u, 0x00000000u,
	      RANGE_TYPE(ResExcIoBlock, domain));
	pRes = xf86AddResToList(pRes, &range, -1);
	RANGE(range, pDomain->io_size - 1, pDomain->io_size - 1,
	      RANGE_TYPE(ResExcIoBlock, domain));
	pRes = xf86AddResToList(pRes, &range, -1);
    }

    return pRes;
}

/* Remap a PCI framebuffer (or portion thereof) */
Bool
xf86LocatePciMemoryArea(PCITAG Tag, char **devName, unsigned int *devOffset,
			unsigned int *fbSize, unsigned int *fbOffset,
			unsigned int *flags)
{
    unsigned long long offset, offset2;
    sparcDomainPtr     pDomain;
    int                domain;

    if (!devName || !devOffset)
	return FALSE;

    domain = PCI_DOM_FROM_TAG(Tag);
    if ((domain <= 0) || (domain >= pciNumDomains) ||
	!(pDomain = xf86DomainInfo[domain]))
	return FALSE;

    offset = (((unsigned long long)devOffset[1]) << 32) | devOffset[0];
    if (offset > pDomain->mem_size)
	return FALSE;

    offset2 = offset;
    if (fbOffset)
	offset2 += *fbOffset;
    if (*fbSize)
	offset2 += *fbSize;
    if (offset2 > pDomain->mem_size)
	return FALSE;

    *devName = NULL;			/* mmap(2) CPU address space */
    offset += pDomain->mem_addr;	/* Relocate address */

    devOffset[0] = (unsigned int)offset;
    devOffset[1] = (unsigned int)(offset >> 32);

    if (flags)
	*flags = 0;

    return TRUE;
}

#endif /* !defined(INCLUDE_XF86_NO_DOMAIN) */

#endif /* defined(sun) || defined(__OpenBSD__) */

#if defined(ARCH_PCI_PCI_BRIDGE)

/* Definitions specific to Sun's APB P2P bridge (a.k.a. Simba) */
#define APB_IO_ADDRESS_MAP	0xDE
#define APB_MEM_ADDRESS_MAP	0xDF

/*
 * Simba's can only occur on bus 0.  Furthermore, Simba's must have a non-zero
 * device/function number because the Sabre interface they must connect to
 * occupies the 0:0:0 slot.  Also, there can be only one Sabre interface in the
 * system, and therefore, only one Simba function can route any particular
 * resource.  Thus, it is appropriate to use a single set of static variables
 * to hold the tag of the Simba function routing a VGA resource range at any
 * one time, and to test these variables for non-zero to determine whether or
 * not the Sabre would master-abort a VGA access (and kill the system).
 *
 * The trick is to determine when it is safe to re-route VGA, because doing so
 * re-routes much more.
 */
static PCITAG simbavgaIOTag = 0, simbavgaMemTag = 0;
static PCITAG simbadefaultIOTag = 0, simbadefaultMemTag = 0;
static Bool simbavgaRoutingAllow = TRUE;

/*
 * Scan the bus subtree rooted at 'bus' for a non-display device that might be
 * decoding any resource in the bottom 2 MB of I/O space and/or the bottom 512
 * MB of memory space.  Reset simbavgaRoutingAllow if such a device is found.
 * Also, ensure the ranges always remain forwarded by some Simba in the system.
 *
 * XXX For now, this is very conservative and should be made less so as the
 *     need arises.
 */
static void
simbaCheckBus(CARD16 pcicommand, int bus)
{
    pciConfigPtr pPCI, *ppPCI = xf86scanpci(0);
    CARD16 savecmd = pcicommand;

    while ((pPCI = *ppPCI++)) {
	if (pPCI->busnum < bus)
	    continue;
	if (pPCI->busnum > bus)
	    break;

	/* XXX Assume all devices respect PCI disablement */
	pcicommand = savecmd & pPCI->pci_command;
	if (!pcicommand)
	    continue;

	/* XXX This doesn't deal with mis-advertised classes ... */
	switch (pPCI->pci_base_class) {
	case PCI_CLASS_PREHISTORIC:
	    if ((pPCI->pci_sub_class != PCI_SUBCLASS_PREHISTORIC_VGA) ||
		/* ... except for known cases */
		(pPCI->pci_vendor == PCI_VENDOR_CREATIVE) ||
		(pPCI->pci_vendor == PCI_VENDOR_ENSONIQ))
		break;
	    /* Fall through */

	case PCI_CLASS_DISPLAY:
	    continue;

	case PCI_CLASS_BRIDGE:
	    switch (pPCI->pci_sub_class) {
	    case PCI_SUBCLASS_BRIDGE_PCI:
	    case PCI_SUBCLASS_BRIDGE_CARDBUS:
		/* Scan secondary bus */
		/* XXX First check bridge routing? */
		simbaCheckBus(pcicommand,
		    PCI_SECONDARY_BUS_EXTRACT(pPCI->pci_pp_bus_register,
			pPCI->tag));
		if (!simbavgaRoutingAllow)
		    return;

	    default:
		break;
	    }

	default:
	    break;
	}

	/*
	 * XXX We could check the device's bases here, but PCI doesn't limit
	 *     the device's decoding to them.
	 */

	simbavgaRoutingAllow = FALSE;
	break;
    }
}

static pciConfigPtr
simbaVerifyBus(int bus)
{
    pciConfigPtr pPCI;
    if ((bus < 0) || (bus >= pciNumBuses) ||
	!pciBusInfo[bus] || !(pPCI = pciBusInfo[bus]->bridge) ||
	(pPCI->pci_device_vendor != DEVID(VENDOR_SUN, CHIP_SIMBA)))
	return NULL;

    return pPCI;
}

static CARD16
simbaControlBridge(int bus, CARD16 mask, CARD16 value)
{
    pciConfigPtr pPCI;
    CARD16 current = 0, tmp;
    CARD8 iomap, memmap;

    if ((pPCI = simbaVerifyBus(bus))) {
	/*
	 * The Simba does not implement VGA enablement as described in the P2P
	 * spec.  It does however route I/O and memory in large enough chunks
	 * so that we can determine were VGA resources would be routed
	 * (including ISA VGA I/O aliases).  We can allow changes to that
	 * routing only under certain circumstances.
	 */
	iomap = pciReadByte(pPCI->tag, APB_IO_ADDRESS_MAP);
	memmap = pciReadByte(pPCI->tag, APB_MEM_ADDRESS_MAP);
	if (iomap & memmap & 0x01) {
	    current |= PCI_PCI_BRIDGE_VGA_EN;
	    if ((mask & PCI_PCI_BRIDGE_VGA_EN) &&
		!(value & PCI_PCI_BRIDGE_VGA_EN)) {
		if (!simbavgaRoutingAllow) {
		    xf86MsgVerb(X_WARNING, 3, "Attempt to disable VGA routing"
				" through Simba at %x:%x:%x disallowed.\n",
				pPCI->busnum, pPCI->devnum, pPCI->funcnum);
		    value |= PCI_PCI_BRIDGE_VGA_EN;
		} else {
		    if (pPCI->tag != simbadefaultIOTag) {
			pciWriteByte(pPCI->tag, APB_IO_ADDRESS_MAP,
				     iomap & ~0x01);
			if ((simbavgaIOTag = simbadefaultIOTag)) {
			    iomap = pciReadByte(simbavgaIOTag,
						APB_IO_ADDRESS_MAP);
			    pciWriteByte(simbavgaIOTag, APB_IO_ADDRESS_MAP,
					 iomap | 0x01);
			}
		    }

		    if (pPCI->tag != simbadefaultMemTag) {
			pciWriteByte(pPCI->tag, APB_MEM_ADDRESS_MAP,
				     memmap & ~0x01);
			if ((simbavgaMemTag = simbadefaultMemTag)) {
			    memmap = pciReadByte(simbavgaMemTag,
						 APB_MEM_ADDRESS_MAP);
			    pciWriteByte(simbavgaMemTag, APB_MEM_ADDRESS_MAP,
					 memmap | 0x01);
			}
		    }
		}
	    }
	} else {
	    if (mask & value & PCI_PCI_BRIDGE_VGA_EN) {
		if (!simbavgaRoutingAllow) {
		    xf86MsgVerb(X_WARNING, 3, "Attempt to enable VGA routing"
				" through Simba at %x:%x:%x disallowed.\n",
				pPCI->busnum, pPCI->devnum, pPCI->funcnum);
		    value &= ~PCI_PCI_BRIDGE_VGA_EN;
		} else {
		    if (pPCI->tag != simbavgaIOTag) {
			if (simbavgaIOTag) {
			    tmp = pciReadByte(simbavgaIOTag,
					      APB_IO_ADDRESS_MAP);
			    pciWriteByte(simbavgaIOTag, APB_IO_ADDRESS_MAP,
					 tmp & ~0x01);
			}

			pciWriteByte(pPCI->tag, APB_IO_ADDRESS_MAP,
				     iomap | 0x01);
			simbavgaIOTag = pPCI->tag;
		    }

		    if (pPCI->tag != simbavgaMemTag) {
			if (simbavgaMemTag) {
			    tmp = pciReadByte(simbavgaMemTag,
					      APB_MEM_ADDRESS_MAP);
			    pciWriteByte(simbavgaMemTag, APB_MEM_ADDRESS_MAP,
					 tmp & ~0x01);
			}

			pciWriteByte(pPCI->tag, APB_MEM_ADDRESS_MAP,
				     memmap | 0x01);
			simbavgaMemTag = pPCI->tag;
		    }
		}
	    }
	}

	/* Move on to master abort failure enablement (as per P2P spec) */
	tmp = pciReadWord(pPCI->tag, PCI_PCI_BRIDGE_CONTROL_REG);
	current |= tmp;
	if (tmp & PCI_PCI_BRIDGE_MASTER_ABORT_EN) {
	    if ((mask & PCI_PCI_BRIDGE_MASTER_ABORT_EN) &&
		!(value & PCI_PCI_BRIDGE_MASTER_ABORT_EN))
		pciWriteWord(pPCI->tag, PCI_PCI_BRIDGE_CONTROL_REG,
			     tmp & ~PCI_PCI_BRIDGE_MASTER_ABORT_EN);
	} else {
	    if (mask & value & PCI_PCI_BRIDGE_MASTER_ABORT_EN)
		pciWriteWord(pPCI->tag, PCI_PCI_BRIDGE_CONTROL_REG,
			     tmp | PCI_PCI_BRIDGE_MASTER_ABORT_EN);
	}

	/* Insert emulation of other P2P controls here */
    }

    return (current & ~mask) | (value & mask);
}

static void
simbaGetBridgeResources(int bus,
			pointer *ppIoRes,
			pointer *ppMemRes,
			pointer *ppPmemRes)
{
    pciConfigPtr pPCI = simbaVerifyBus(bus);
    resRange range;
    int i;

    if (!pPCI)
	return;

    if (ppIoRes) {
	xf86FreeResList(*ppIoRes);
	*ppIoRes = NULL;

	if (pPCI->pci_command & PCI_CMD_IO_ENABLE) {
	    unsigned char iomap = pciReadByte(pPCI->tag, APB_IO_ADDRESS_MAP);
	    if (simbavgaRoutingAllow)
		iomap |= 0x01;
	    for (i = 0;  i < 8;  i++) {
		if (iomap & (1 << i)) {
		    RANGE(range, i << 21, ((i + 1) << 21) - 1,
			  RANGE_TYPE(ResExcIoBlock,
				     xf86GetPciDomain(pPCI->tag)));
		    *ppIoRes = xf86AddResToList(*ppIoRes, &range, -1);
		}
	    }
	}
    }

    if (ppMemRes) {
	xf86FreeResList(*ppMemRes);
	*ppMemRes = NULL;

	if (pPCI->pci_command & PCI_CMD_MEM_ENABLE) {
	    unsigned char memmap = pciReadByte(pPCI->tag, APB_MEM_ADDRESS_MAP);
	    if (simbavgaRoutingAllow)
		memmap |= 0x01;
	    for (i = 0;  i < 8;  i++) {
		if (memmap & (1 << i)) {
		    RANGE(range, i << 29, ((i + 1) << 29) - 1,
			  RANGE_TYPE(ResExcMemBlock,
				     xf86GetPciDomain(pPCI->tag)));
		    *ppMemRes = xf86AddResToList(*ppMemRes, &range, -1);
		}
	    }
	}
    }

    if (ppPmemRes) {
	xf86FreeResList(*ppPmemRes);
	*ppPmemRes = NULL;
    }
}

void ARCH_PCI_PCI_BRIDGE(pciConfigPtr pPCI)
{
    static pciBusFuncs_t simbaBusFuncs;
    pciBusInfo_t *pBusInfo;
    CARD16 pcicommand;

    if (pPCI->pci_device_vendor != DEVID(VENDOR_SUN, CHIP_SIMBA))
	return;

    pBusInfo = pPCI->businfo;

    simbaBusFuncs = *(pBusInfo->funcs);
    simbaBusFuncs.pciControlBridge = simbaControlBridge;
    simbaBusFuncs.pciGetBridgeResources = simbaGetBridgeResources;

    pBusInfo->funcs = &simbaBusFuncs;

    if (!simbavgaRoutingAllow)
	return;

    pcicommand = 0;

    if (pciReadByte(pPCI->tag, APB_IO_ADDRESS_MAP) & 0x01) {
	pcicommand |= PCI_CMD_IO_ENABLE;
	simbavgaIOTag = simbadefaultIOTag = pPCI->tag;
    }

    if (pciReadByte(pPCI->tag, APB_MEM_ADDRESS_MAP) & 0x01) {
	pcicommand |= PCI_CMD_MEM_ENABLE;
	simbavgaMemTag = simbadefaultMemTag = pPCI->tag;
    }

    if (!pcicommand)
	return;

    simbaCheckBus(pcicommand,
	PCI_SECONDARY_BUS_EXTRACT(pPCI->pci_pp_bus_register, pPCI->tag));
}

#endif /* defined(ARCH_PCI_PCI_BRIDGE) */
