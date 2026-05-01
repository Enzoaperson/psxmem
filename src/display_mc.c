#include <stdio.h>
#include "datatypes.h"
#include "icondraw.h"
#include "shiftjis.h"
#include "switches.h"
#include "cores.h"

#define BLOCKS_TO_KB 8

#define DATA_OFFSET 0x2000

char calcu_size(mc_symbolic *mc, char starting_block);
void print_name(unsigned short *data);

void display_mc(mc_symbolic *mc, short parms){
	
	for(char b = 0; b <=MAX_NUMBER_OF_BLOCKS-1; b++){
		if((parms & DELETED_SWITCH) || mc->blocks[b].status & ACTIVE_BLOCK){
			if((mc->blocks[b].status & END_BLOCK) == STARTING_BLOCK){

				//Display Title
				printf("%2d. ", b+1);
				if(mc->blocks[b].status & DELETED_BLOCK){
					printf("\e[7m\e[1;31;47mDELETED\e[0m ");
				}
				print_name((unsigned short *)mc->blocks[b].data+2);

				//Display Icon
				if(parms & GRAPHICS_SWITCH){
					//Currently PocketStation Support isn't working :(
					//if(mc->blocks[b].pocket_station){
					//	printf("Regular Icon: \n");
					//}
					drawicon(mc->blocks[b].data + 0x80, mc->blocks[b].data + 0x60, parms);
					//if(mc->blocks[b].pocket_station){
					//	printf("Pocket Station Icon:\n");
					//	drawicon1bpp(mc->blocks[b].data + 0x200);	
					//}
				}
				
				//Display stats
				printf(" ID: ");
				for(char i = 0; i < LENGTH_OF_ID; i++){
					printf("%c", mc->blocks[b].id[i]);
				}
				printf("\n");

				//Calculate Size
				char size = 0;
				size = calcu_size(mc, b);
				printf(" Size: %d Blocks (%d KB)\n", size, size*BLOCKS_TO_KB);
				printf(" Country Code: ");
				switch(mc->blocks[b].region){
					case JAPAN:
						printf("Japan (BI)");
						break;
					case AMERICA:
						printf("America (BA)");
						break;
					case EUROPE:
						printf("Europe (BE)");
						break;
				}

				//printf("\nRegion = %c", mc->blocks[b].region);
				printf("\n");
				if(mc->blocks[b].core != UNKNOWN){
					printf(" Game Specific Details:\n");
					run_core(mc->blocks[b].core, mc->blocks[b].data);
				}
				printf("\n");


			}
		}
	}

}



char calcu_size(mc_symbolic *mc, char starting_block){
	char size = 1;
	if(starting_block >= MAX_NUMBER_OF_BLOCKS-1){
		return size;
	}
	for(char i = starting_block+1; i <=MAX_NUMBER_OF_BLOCKS-1; i++){
		//printf("%2d\n", mc->blocks[i].status);
		switch(mc->blocks[i].status & END_BLOCK){
			case END_BLOCK:
				size++;
				return size;
			case MIDDLE_BLOCK:
				size++;
				break;
			case STARTING_BLOCK:
				return size;
			default:
				return size;
		}
	}
}

void print_name(unsigned short *data){
	//printf("0x%x\n",  data[0]);
	for(char i = 0; i < 32; i++){
		//printf("0x%x = ",  data[i]);
		get_char(data[i]);
		//printf("\n");	
	}
	printf("\n");	
	return;
}
