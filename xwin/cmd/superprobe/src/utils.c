/*
 ****************************************************************
 *								*
 *			utils.c					*
 *								*
 *	Diversas rotinas de uso geral				*
 *								*
 *	Versão	1.0.0, de 03.01.97				*
 *								*
 *	Módulo: SuperProbe					*
 *		Baseado no software homônimo de David Wexelblat	*
 *		Categoria ?					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 * 								*
 ****************************************************************
 */

#include "../h/probe.h"

/*
 * Read byte register at 'port', index 'index'
 */
Byte
rdinx (Word port, Byte index)
{
	Byte tmp;
	Word Port[2] = {MISC_OUT_R, 0x000};

	if (port == ATR_IDX)
	{
		EnableIOPorts(1, Port);
		Port[1] = (inb (MISC_OUT_R) & 0x01) ? 0x3DA : 0x3BA;
		EnableIOPorts(2, Port);
		tmp = inb (Port[1]);	/* Reset Attribute Reg flip-flop */
		DisableIOPorts(2, Port);
	}

	outb (port, index);
	return (inb (port+1));
}

/*
 * Set the byte register 'port', index 'index' to 'val'
 */
void
wrinx (Word port, Byte index, Byte val)
{
	Byte tmp;
	Word Port[2] = {MISC_OUT_R, 0x000};

	if (port == ATR_REG_W)
	{
		EnableIOPorts(1, Port);
		Port[1] = (inb (MISC_OUT_R) & 0x01) ? 0x3DA : 0x3BA;
		EnableIOPorts(2, Port);
		tmp = inb (Port[1]);
		DisableIOPorts(2, Port);
		outb (port, index);
		outb (port, val);
	}
	else
	{
		outb (port, index);
		outb (port+1, val);
	}
}

/*
 * Set the word register 'port', index 'index' to 'val'
 */
void
wrinx2 (Word port, Byte index, Word val)
{
	wrinx (port, index,   (val) & 0xFF);
	wrinx (port, index+1, (val >> 8) & 0xFF);
}

/*
 * Set the longword register 'port', index 'index' to 'val' (3 bytes, actually)
 */
void
wrinx3 (Word port, Byte index, Long val)
{
	wrinx (port, index,   (val) & 0xFF);
	wrinx (port, index+1, (val >> 8) & 0xFF);
	wrinx (port, index+2, (val >> 16) & 0xFF);
}

/*
 * Set the word register 'port', index 'index' to 'val' (Motorola (big-endian)
 * byte order)
 */
void
wrinx2m (Word port, Byte index, Word val)
{
	wrinx (port, index,   (val >> 8) & 0xFF);
	wrinx (port, index+1, (val) & 0xFF);
}

/*
 * Set the longword register 'port', index 'index' to 'val' (3 bytes, actually)
 * (Motorola (big-endian) byte order)
 */
void
wrinx3m (Word port, Byte index, Long val)
{
	wrinx (port, index,   (val >> 16) & 0xFF);
	wrinx (port, index+1, (val >> 8) & 0xFF);
	wrinx (port, index+2, (val) & 0xFF);
}

/*
 * In byte register 'port', index 'index', set the bit that are 1 in 'mask'
 * to the value of the corresponding bits in 'mask'
 */
void
modinx (Word port, Byte index, Byte mask, Byte newval)
{
	Byte tmp;

	tmp = (rdinx(port, index) & ~mask) | (newval & mask);
	wrinx (port, index, tmp);
}

/*
 * In register 'port' sets the bits in 'mask' as in 'nvw'.  Other bits are
 * left unchanged.
 */
void
modreg (Word port, Byte mask, Byte nvw)
{
	Byte tmp;

	tmp = (inb (port) & (~mask)) | (nvw & mask);
	outb (port, tmp);
}

/*
 * Sets the bits in register 'port', index 'index' that are also set in 'val'
 */
void
setinx (Word port, Byte index, Byte val)
{
	Byte tmp;

	tmp = rdinx (port, index);
	wrinx (port, index, tmp | val);
}

/*
 * Clears the bits in register 'port', index 'index' that are set in 'val'
 */
void
clrinx (Word port, Byte index, Byte val)
{
	Byte tmp;

	tmp = rdinx (port, index);
	wrinx (port, index, tmp & ~val);
}

/*
 * Return TRUE iff the bits in 'mask' of register 'port' are read/write.
 */
Bool
tstrg (Word port, Byte mask)
{
	Byte old, new1, new2;

	old = inb (port);
	outb (port, (old & ~mask));
	new1 = inb (port) & mask;
	outb (port, (old | mask));
	new2 = inb (port) & mask;
	outb (port, old);

	return ((new1 == 0) && (new2 == mask));
}

/*
 * Returns true iff the bits in 'mask' of register 'port', index 'index'
 * are read/write.
 */
Bool
testinx2 (Word port, Byte index, Byte mask)
{
	Byte old, new1, new2;

	old = rdinx (port, index);
	wrinx (port, index, (old & ~mask));
	new1 = rdinx (port, index) & mask;
	wrinx (port, index, (old | mask));
	new2 = rdinx (port, index) & mask;
	wrinx (port, index, old);

	return ((new1 == 0) && (new2 == mask));
}

/*
 * Returns true iff all bits of register 'port', index 'index' are read/write
 */
Bool
testinx (Word port, Byte index)
{
	return (testinx2 (port, index, 0xFF));
}

/*
 * Force DAC back to PEL mode
 */
void
dactopel (void)
{
	(void)inb (0x3C8);
}

/*
 * Trigger HiColor DACs to change mode.
 */
Byte
trigdac (void)
{
	(void)inb (0x3C6);
	(void)inb (0x3C6);
	(void)inb (0x3C6);

	return (inb (0x3C6));
}

/*
 * Enter command mode of HiColor DACs.
 */
Byte
dactocomm (void)
{
	dactopel ();
	return (trigdac ());
}

/*
 * Get the HiColor DAC command register and return to PEL mode.
 */
Byte
getdaccomm (void)
{
	Byte ret;

	dactocomm ();
	ret = inb (0x3C6);
	dactopel ();

	return (ret);
}

/*
 * Wait for vertical retrace interval.
 */
void
waitforretrace (void)
{
	Word Port[2] = {MISC_OUT_R, 0x000};

	EnableIOPorts(1, Port);

	Port[1] = (inb (MISC_OUT_R) & 0x01) ? 0x3DA : 0x3BA;
	EnableIOPorts(2, Port);

	while ((inb (Port[1]) & 0x08) != 0)
		/* vazio */;

	while ((inb (Port[1]) & 0x08) == 0)
		/* vazio */;

	DisableIOPorts(2, Port);
	return;
}

/*
 * Check chip descriptor against exclusion list
 */
Bool
Excluded (Range *ExList, Chip_Descriptor *Chip, Bool Mask10)
{
	int i, j;
	Word mask = (Mask10 ? 0x3FF : 0xFFFF);

	if (Chip->num_ports == 0)
		return(FALSE);

	if (Chip->ports[0] == 0)
	{
		/* Fill in CRTC */
		Chip->ports[0] = CRTC_IDX;
		Chip->ports[1] = CRTC_REG;
	}

	for (i=0; i < Chip->num_ports; i++)
	{
		for (j=0; ExList[j].lo != (Word)-1; j++)
		{
			if (ExList[j].hi == (Word)-1)
			{
				/* single port */
				if ((Chip->ports[i] & mask) == ExList[j].lo)
					return(TRUE);
			}
			else
			{
				/* range */
				if (((Chip->ports[i]&mask) >= ExList[j].lo) &&
				    ((Chip->ports[i]&mask) <= ExList[j].hi))
					return(TRUE);
			}
		}
	}

	return(FALSE);
}

int
StrCaseCmp (char *s1, char *s2)
{
	char c1, c2;

	if (*s1 == 0)
		if (*s2 == 0)
			return(0);
		else
			return(1);

	c1 = (isupper(*s1) ? tolower(*s1) : *s1);
	c2 = (isupper(*s2) ? tolower(*s2) : *s2);

	while (c1 == c2)
	{
		if (c1 == '\0')
			return(0);
		s1++; 
		s2++;

		c1 = (isupper(*s1) ? tolower(*s1) : *s1);
		c2 = (isupper(*s2) ? tolower(*s2) : *s2);
	}

	return (c1 - c2);
}

unsigned int
StrToUL (const char *str)
{
	int base = 10;
	const char *p = str;
	unsigned int tot = 0;

	if (*p == '0')
	{
		p++;
		if (*p == 'x')
		{
			p++;
			base = 16;
		}
		else
		{
			base = 8;
		}
	}

	while (*p)
	{
		if ((*p >= '0') && (*p <= ((base == 8)?'7':'9')))
		{
			tot = tot * base + (*p - '0');
		}
		else if ((base == 16) && (*p >= 'a') && (*p <= 'f'))
		{
			tot = tot * base + 10 + (*p - 'a');
		}
		else if ((base == 16) && (*p >= 'A') && (*p <= 'F'))
		{
			tot = tot * base + 10 + (*p - 'A');
		}
		else
		{
			return(tot);
		}
		p++;
	}
	return(tot);
}
