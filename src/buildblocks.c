#include <stdio.h>
#include "datatypes.h"
#include "cores.h"
#include "switches.h"

#define REGION_OFFSET 0x0b

unsigned char *find_pocketstation_icon(unsigned char *data){

	unsigned char *offset = (data + 0x80);

	return offset;
}

void buildblocks(mc_symbolic *mc, short parms){
	//Add the Offsets for PSP Memory Card Files
	int offset = 0;
	if(mc->type == PSP){ //Add PSP Offset
		offset = 0x80;
	
	}else if(mc->type == DEX){ //Add DexDrive Offset
		offset = 0xf40;
	}

	for(int b = 1; b <= MAX_NUMBER_OF_BLOCKS; b++){
		//printf("Block %d: %x\n", b, mc->data[b*0x80]);
		//Set the Block up
		mc->blocks[b-1].number = b-1;
		mc->blocks[b-1].status = (mc->data[(b*0x80) + offset]);
		mc->blocks[b-1].data = (mc->data + (b*0x2000) + offset);
		mc->blocks[b-1].id = (mc->data + (b*0x80) + 10 + offset);
		mc->blocks[b-1].region = (mc->data[(b*0x80) + REGION_OFFSET + offset]); 
		if(mc->blocks[b-1].id[6] == 'P'){
			mc->blocks[b-1].pocket_station = 1;
		}else{
			mc->blocks[b-1].pocket_station = 0;
		}
		if(parms & CORES_SWITCH){
			mc->blocks[b-1].core = find_core(mc->blocks[b-1].id);
		}else{
			mc->blocks[b-1].core = UNKNOWN;
		}

	}
	//printf("%c\n", mc->blocks[0].data[1]);
	//printf("%x", mc->blocks[0].status);
	//for(int i = 0; i < LENGTH_OF_ID; i++){
	//	printf("%c", mc->blocks[0].id[i]);
	//}
	printf("\n");

}
