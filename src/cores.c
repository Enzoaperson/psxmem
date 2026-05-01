#include <stdio.h>
#include <string.h>
#include "datatypes.h"
#include "cores.h"

#define SIZE_OF_SERIAL 5

char run_core(enum CORE_TYPE core, unsigned char *data){
	switch(core){
		case UNKNOWN:
			return 0;
		case RIDGE_RACER:
			return ridge_racer(data);
	}
}

enum CORE_TYPE find_core(unsigned char *id){
	//I do want to figure out some sort of hash at somepoint, however for now this is ok I guess
	if(!(memcmp((id+7), "94300", SIZE_OF_SERIAL))){ //Ridge Racer 
		return RIDGE_RACER;
	}else{
		return UNKNOWN;
	}

}
