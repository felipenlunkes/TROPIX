/*
 ****************************************************************
 *								*
 *			print.c					*
 *								*
 *	Imprime as informações obtidas				*
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

static const char *SVGA_Names[NUM_VENDORS+1][CHPS_PER_VENDOR] = 
{
/* dummy */	{ "" },	
/* Ahead */	{ "Ahead (chipset desconhecido)",
		  "Ahead V5000 Version A", "Ahead V5000 Version B" },
/* ATI */	{ "ATI (chipset desconhecido)", 
		  "ATI 18800", "ATI 18800-1",
		  "ATI 28800-2", "ATI 28800-4", "ATI 28800-5", "ATI 28800-6",
		  "ATI 68800-3", "ATI 68800-6", "ATI 68800LX", "ATI 68800AX",
		  "ATI 88800CX", "ATI 88800GX" },
/* AL */	{ "Avance Logic (chipset desconhecido)",
		  "Avance Logic 2101", "Avance Logic 2228" },
/* CT */	{ "Chips & Tech (chipset desconhecido)",
		  "Chips & Tech 82c450", "Chips & Tech 82c451", 
		  "Chips & Tech 82c452", "Chips & Tech 82c453",
		  "Chips & Tech 82c455", "Chips & Tech 82c456",
		  "Chips & Tech 82c457", "Chips & Tech F65510",
		  "Chips & Tech F65520", "Chips & Tech F65530",
		  "Chips & Tech F65540", "Chips & Tech F65545" },
/* Cirrus */	{ "Cirrus (chipset desconhecido)",
		  "Cirrus CL-GD 510/520", "Cirrus CL-GD 610/620",
		  "Cirrus Video7 OEM",
		  "Cirrus/AcuMos AVGA2",
		  "Cirrus CL-GD5402", "Cirrus CL-GD5402 Rev 1",
		  "Cirrus CL-GD5420", "Cirrus CL-GD5420 Rev 1",
		  "Cirrus CL-GD5422", "Cirrus CL-GD5424", 
		  "Cirrus CL-GD5426", "Cirrus CL-GD5428",
		  "Cirrus CL-GD5429",
		  "Cirrus CL-GD5430", "Cirrus CL-GD5434",
		  "Cirrus CL-GD6205", "Cirrus CL-GD6215",
		  "Cirrus CL-GD6225", "Cirrus CL-GD6235",
		  "Cirrus CL-GD5410",
		  "Cirrus CL-GD6410", "Cirrus CL-GD6412",
		  "Cirrus CL-GD6420A", "Cirrus CL-GD6420B" 
		  "Cirrus CL-GD6440",
		  "Cirrus CL-GD5436"},
/* Compaq */	{ "Compaq (chipset desconhecido)",
		  "Compaq Int. Vid. Graphics Sys.",
		  "Compaq Advanced VGA", 
		  "Compaq QVision/1024", "Compaq QVision/1280",
		  "Compaq Advanced VGA, Portable" },
/* Genoa */	{ "Genoa GVGA 6100",
		  "Genoa GVGA 6200/6300", "Genoa GVGA 6400/6600" },
/* HMC */	{ "HMC HM86304" },
/* MX */	{ "MX 68000", "MX 68010" },
/* NCR */	{ "NCR (chipset desconhecido)",
		  "NCR 77C21", "NCR 77C22", "NCR 77C22E", "NCR 77C22E+",
		  "NCR 77C32BLT" },
/* Oak */	{ "Oak (chipset desconhecido)",
		  "Oak OTI037C", 
		  "Oak OTI-057", "Oak OTI-067", "Oak OTI-077",
		  "Oak OTI-083", "Oak OTI-087" },
/* Primus */	{ "Primus P2000" },
/* Realtek */	{ "Realtek (chipset desconhecido)",
		  "Realtek RT-3103", "Realtek RT-3105", "Realtek RT-3106" },
/* S3 */	{ "S3 (chipset desconhecido)",
		  "S3 86C911", "S3 86C924",
		  "S3 86C801, A or B-step", 
		  "S3 86C801, C-step", "S3 86C801, D-step", 
		  "S3 86C801i",
		  "S3 86C805, A or B-step", 
		  "S3 86C805, C-step", "S3 86C805, D-step",
		  "S3 86C805i",
		  "S3 86C928, A,B,C, or D-step", "S3 86C928, E-step",
		  "S3 86C928PCI",
		  "S3 Vision864",
		  "S3 Vision964",
		  "S3 Vision866",
		  "S3 Vision868",
		  "S3 Vision968",
		  "S3 Trio32",
		  "S3 Trio64",
		  "S3 Trio64V+",
	       },
/* Trident */	{ "Trident (chipset desconhecido)",
		  "Trident LX8200",
		  "Trident 8800BR", "Trident 8800CS",
		  "Trident 8900B", "Trident 8900C", "Trident 8900CL/8900D",
		  "Trident 9000", "Trident 9000i",
		  "Trident LCD9100B", "Trident 9200CXr", "Trident LCD9320", 
		  "Trident 9400CXi", "Trident GUI 9420", "Trident GUI 9440AGi",
		  "Trident GUI 9660", "Trident GUI 9420DGi"},
/* Tseng */	{ "Tseng (chipset desconhecido)",
		  "Tseng ET3000", "Tseng ET4000", 
		  "Tseng ET4000/W32", "Tseng ET4000/W32i", 
		  "Tseng ET4000/W32p Rev A",
		  "Tseng ET4000/W32i Rev B",
		  "Tseng ET4000/W32i Rev C",
		  "Tseng ET4000/W32p Rev B",
		  "Tseng ET4000/W32p Rev C",
		  "Tseng ET4000/W32p Rev D",
		},
/* UMC */	{ "UMC 85c408" },
/* Video7 */	{ "Video7 (chipset desconhecido)",
		  "Video7 FastWrite/VRAM (HT208)", "Video7 1024i (HT208A)",
		  "Video7 VRAM II (HT208B)", "Video7 VRAM II (HT208C,D)",
		  "Video7 HT216B,C", "Video7 HT216D",
		  "Video7 HT216E", "Video7 HT216E",
		  "Video7 VEGA" },
/* WD */	{ "WD/Paradise (chipset desconhecido)",
		  "WD/Paradise PVGA1", "WD/Paradise 90C00", 
		  "WD/Paradise 90C10", "WD/Paradise 90C11",
		  "WD/Paradise 90C20", "WD/Paradise 90C20A",
		  "WD/Paradise 90C22", "WD/Paradise 90C24", 
		  "WD/Paradise 90C26", "WD/Paradise 90C27",
		  "WD/Paradise 90C30", "WD/Paradise 90C31",
		  "WD/Paradise 90C33" },
/* Weitek */	{ "Weitek (chipset desconhecido)",
		  "Weitek 5086", "Weitek 5186", "Weitek 5286" },
/* Yamaha */	{ "Yamaha 6388 VPDC" },
};

static const char *Herc_Names[] = 
{
	"",		/* indices start at 1 */
	"Standard",
	"Plus",
	"InColor",
};

struct RamDac_Name RamDac_Names[] =
{
	{ "Unknown", "Non-standard but unknown DAC" },
	{ "Generic", "Generic 8-bit pseudo-color DAC" },
	{ "ALG1101", "Avance Logc ALG1101" },
	{ "SS2410", "Diamond SS2410 15/16/24-bit DAC" },
	{ "Sierra15", "Sierra SC1148{1,6,8} 15-bit HiColor DAC" },
	{ "Sierra16", 
	  "Sierra SC1148{2,3,4} 15-bit ou SC1148{5,7,9} 15/16-bit HiColor" },
	{ "Sierra24", "Sierra 1502{5,6} 15/16/24-bit DAC" },
	{ "MU9C4870", "MUSIC MU9C4870 15/16-bit HiColor DAC" },
	{ "MU9C4910", "MUSIC MU9C4910 15/16/24-bit DAC" },
	{ "ADAC1", "AcuMos ADAC1 15/16/24-bit DAC" },
	{ "68830", "ATI 68830 15/16-bit HiColor DAC" },
	{ "68860", "ATI 68860 15/15/24-bit DAC w/pixel-mux" },
	{ "68875", "ATI-68875/Bt885/TLC34075 15/16/24-bit DAC w/pixel-mux" },
	{ "ATIMisc", 
	  "ATI Misc 3rd-party {AT&T, BT, Sierra} 15/16/24-bit DAC" },
	{ "Cirrus8", "Cirrus Logic Built-in 8-bit pseudo-color DAC" },
	{ "Cirrus24B", "Cirrus Logic Built-in 15/16/24-bit DAC" },
	{ "Cirrus24", "Cirrus Logic 15/16/24-bit DAC" },
	{ "20C490", "AT&T 20C490 15/16/24-bit DAC" },
	{ "20C491", "AT&T 20C491 15/16/24-bit DAC com correção gama" },
	{ "20C492", "AT&T 20C492 15/16/18-bit DAC com correção gama" },
	{ "20C493", "AT&T 20C493 15/16/18-bit DAC" },
	{ "20C497", "AT&T 20C497 24-bit wide, 8-bit pseudo-color DAC" },
	{ "Bt485", "BrookTree Bt485 24-bit TrueColor DAC w/cursor,pixel-mux" },
	{ "20C504", "AT&T 20C504 24-bit TrueColor DAC w/cursor,pixel-mux" },
	{ "20C505", "AT&T 20C505 24-bit TrueColor DAC w/cursor,pixel-mux" },
	{ "TVP3020",
	  "TI ViewPoint3020 24-bit TrueColor DAC w/cursor,pixel-mux" },
	{ "TVP3025",
	  "TI ViewPoint3025 24-bit TrueColor DAC w/cursor,pixel-mux,clock" },
	{ "EDSUN", "EDSUN CEG DAC" },
	{ "20C498", "AT&T 20C498/21C498 15/16/24-bit DAC w/pixel-mux" },
	{ "22C498", "AT&T 22C498 15/16/24-bit DAC w/pixel-mux" },
	{ "STG1700", "STG1700 15/16/24-bit DAC w/pixel-mux" },
	{ "S3_GENDAC", "S3 86C708 GENDAC 15/16/24-bit DAC w/clock-PLL" },
	{ "S3_SDAC", "S3 86C716 SDAC 15/16/24-bit DAC w/pixel-mux w/clock-PLL" },
	{ "TVP3026",
	  "TI ViewPoint3026 24-bit TrueColor DAC w/cursor,pixel-mux,clock" },
	{ "RGB524", 
	  "IBM RGB524 24-bit TrueColor DAC w/cursor,pixel-mux,clock" },
	{ "RGB514/525", 
	  "IBM RGB514/525 24-bit TrueColor DAC w/cursor,pixel-mux,clock" },
	{ "RGB528", 
	  "IBM RGB528 24-bit TrueColor DAC w/cursor,pixel-mux,clock" },
	{ "STG1703", "STG1703 15/16/24-bit DAC w/pixel-mux,clock" },
};

static const char *CoProc_Names[NUM_CP_TYPES][CHPS_PER_CPTYPE] = 
{
/* 8514 */	{ "8514/A (ou clone verdadeiro)",
		  "ATI Mach8", "ATI Mach32",
		  "Chips & Technologies 82C480 (8514/A clone)" },
/* XGA */	{ "" },
/* Mach64 */	{ "ATI Mach64" },
/* Number9 */	{ "Number Nine Imagine I128" },
};

void
Print_SVGA_Name (int Chipset)
{
	int vendor = SVGA_VENDOR (Chipset);
	int chip = SVGA_CHIP (Chipset);

	printf ("\tChipset: %s\n", SVGA_Names[vendor][chip]);

	if ((!chip) && (~Chip_data))
		printf ("\t\tAssinatura: %02x (please report)\n", Chip_data);
}

void
Print_Herc_Name (int Chipset)
{
	int chip = HERC_CHIP (Chipset);
	printf ("\tChipset: %s\n", Herc_Names[chip]);
}

void
Print_RamDac_Name (int RamDac)
{
	printf ("\tRAMDAC:  %s\n", RamDac_Names[DAC_CHIP(RamDac)].Long);

	if (RamDac & DAC_8BIT)
	{
		printf ("\t\t (com lookup table de 8 bits)\n");
	}
	else
	{
		printf ("\t\t (com lookup table de 6 bits ");
		printf ("(ou no modo de 6 bits))\n");
	}

	if (RamDac & DAC_6_8_PROGRAM)
		printf ("\t\t (programável para lookup tables de 6/8 bits)\n");
}

void
Print_CoProc_Name (int CoProc)
{
	int class = COPROC_CLASS (CoProc);
	int chip = COPROC_CHIP (CoProc);

	printf ("\t\tChipset: %s\n", CoProc_Names[class][chip]);
}
