#include <stdio.h>
#include <stdlib.h>
#include "datatypes.h"

mc_type typecheck(char *data){
	if(data[0] == 'M' && data[1] == 'C'){
		printf("Type is RAW\n");
		return RAW;
	}
	if(data[0] == 0 && data[1] == 'P' && data[2] == 'M' && data[3] == 'V'){
		printf("Type is PSP\n");
		return PSP;
	}
	if(data[0] == '1' && data[1] == '2' && data[2] == '3' && data[3] == '-'){
		printf("Type is DexDrive\n");
		return DEX;
	}


	//all else fails!
	return UNKNOWN;
}
