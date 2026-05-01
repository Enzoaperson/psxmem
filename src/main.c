#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "datatypes.h"
#include "typecheck.h"
#include "buildblocks.h"
#include "display_mc.h"
#include "switches.h"
#include "help.h"

void handle_signals(int signal){
	if(signal == SIGTERM || signal == SIGABRT){
		printf("\e[0m");
	}
	exit(0);
}



int main(int argc, char *argv[]){

	//Init Signal handler
	if (signal(SIGINT, handle_signals) == SIG_ERR){
		printf("Error occured while setting up Signal Handle\n");
		return 1;
	}
	short parms = 0;
	int input_arg = 0, output_arg = 0, switches = 0;
	char *input_path = NULL;
	char *output_path = NULL;

	if(argc <= 1){
		printf("I need arguments to work :( \n");
		help();
		printf("\n");
		return 0;
	}

	switches = handle_switches(argc, argv, &input_arg, &output_arg);
	parms = (switches & 0xffff);
	//printf("%x", switches);
	input_path = argv[input_arg];
	//printf("%s\n", input_path);
	if(switches & HELP_SWITCH){
		help();	
	}

	if(switches & ABOUT_SWITCH){
		about(parms);
	}

	if(switches & QUIT_SWITCH){
		return 0;
	}

	if(input_path == NULL){
		printf("Error: I need a file to work!");
		return 0;
	}
	FILE *Memcard_file;

	//Check if it exists
	Memcard_file = fopen(input_path, "rb");
	if(Memcard_file == NULL){
		printf("Error: File does not exist!\n");
		return 0;
	}
	mc_symbolic mc;

	//Get length
	fseek(Memcard_file, 0, SEEK_END);
	mc.length = ftell(Memcard_file);
	fseek(Memcard_file, 0, SEEK_SET);
	
	//Open File
	mc.data = (unsigned char*)malloc(mc.length);
	if(mc.data == NULL){
		printf("Error: Could not allocate enough memory to load the MC into ram");
		return 1;
	}
	fread(mc.data, 1, mc.length, Memcard_file);
	if(mc.data == NULL){
		//Todo change errors to fprintf(stderr)
		printf("Error: Couldn't load the Memory card into RAM");
		return 1;
	}

	mc.type = typecheck(mc.data);
	if(mc.type == UNKNOWN){
		printf("Error: File \"%s\" is not a known Playstation Memory Card Format.\n", argv[1]);
		return 0;
	}

	//printf("Type: %d\n", mc.type);
	buildblocks(&mc, parms);
	display_mc(&mc, parms);

}
