#include <stdio.h>
#include <string.h>
#include "switches.h"

#define CHECK_ARGU(x, y) (!strcmp((x), argv[i])) || (!strcmp((y), argv[i])) 

int handle_switches(int argc, char *argv[], int *input_arg, int *output_arg){
	int switches = DEFAULT_SWITCHES;
	for(int i = 1; i < argc; i++){
		//printf("Handling switch: %s\n", argv[i]);
		if(argv[i][0] != '-'){ // Non dashed arg
			*input_arg = i;
			switches &= (0xffffffffffffff ^ QUIT_SWITCH);
			continue;
		}else{ //Dashed arg
			if(!strcmp("-v", argv[i]) || !strcmp("--version", argv[i])){
				switches ^= ABOUT_SWITCH;
			}else if(!strcmp("-h", argv[i]) || !strcmp("--help", argv[i])){
				switches ^= HELP_SWITCH;
			}else if(CHECK_ARGU("-ng", "--no-graphics")){
				switches ^= GRAPHICS_SWITCH;
			}else if(CHECK_ARGU("-p", "--palette")){
				switches ^= PALETTE_SWITCH;
			}else if(CHECK_ARGU("-d", "--show-deleted")){
				switches ^= DELETED_SWITCH;
			}else if(CHECK_ARGU("-nc", "--no-cores")){
				switches ^= CORES_SWITCH;
			}else if(!strcmp("-i", argv[i])){ //Grab input file
				*input_arg = (i+1);
				switches &= (0xffffffffffffff ^ QUIT_SWITCH);
				i++;
			}else{
				printf("Error: Argument %s is invalid!\n", argv[i]);
				return (QUIT_SWITCH | HELP_SWITCH);
			}
		}
	}
	//printf("Parms: %x\n", switches);
	//printf("Path: %s\n", input_path);
	return switches;
}
