#include <stdio.h>
#include "switches.h"
#include "icondraw.h"

#define VERSION 2
#define SUBVERSION 00

extern unsigned char enzo_icon[8*16];
extern unsigned char enzo_c_pal[32];

void help(){
	printf("Usage: psxmem [OPTIONS]\n");
	printf("  -i /path/to/file	Input file\n");
	printf("  -v, --version		Print version then quit\n");
	printf("  -h, --help		Show this screen\n");
	printf("  -ng, --no-graphics	Show no icons\n");
	printf("  -p --palette		Show the color palette in the terminal\n");
	printf("  -d --show-deleted     Show Memory Card blocks marked deleted\n");
	printf("  -nc, --no-cores	If a core exists to display more info about the save data, it will not\n");

}

void about(short parms){
	printf("PSXMem Version: %d.%d", VERSION, SUBVERSION);
	//Debug On
	#ifdef DEBUG_ON
	printf(" Debug");
	#endif
	printf("\n");
	if(parms & GRAPHICS_SWITCH){
		drawicon(&enzo_icon[0], &enzo_c_pal[0], parms);
	}
	printf("Written by Enzo_a_person\n\n");
//	printf("Memory Card Files and Blocks with this program are ");
	return;

}
