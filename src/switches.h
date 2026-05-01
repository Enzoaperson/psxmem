#ifndef SWITCHES
#define SWITCHES

/*First bank of 16 bytes affect how the program runs*/
#define EMPTY_SWITCHES  0
#define GRAPHICS_SWITCH 0x01
#define PALETTE_SWITCH 	0x02
#define DELETED_SWITCH  0x04
#define CORES_SWITCH 0x08

/*Second bank of 16 is for help and about things*/
#define HELP_SWITCH  	0x010000
#define ABOUT_SWITCH 	0x020000
#define QUIT_SWITCH     0x040000

#define DEFAULT_SWITCHES (QUIT_SWITCH | GRAPHICS_SWITCH | CORES_SWITCH)


int handle_switches(int argc, char *argv[], int *input_arg, int *output_arg);

#endif
