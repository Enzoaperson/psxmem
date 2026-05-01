#ifndef DATATYPES
#define DATATYPES

#include "cores.h"

#define UNKNOWN -1

#define ACTIVE_BLOCK    0x50
#define DELETED_BLOCK   0xA0
#define UNDEFINED_BLOCK 0x00

#define STARTING_BLOCK 1
#define MIDDLE_BLOCK 2
#define END_BLOCK 3

//MAXES
#define MAX_NUMBER_OF_BLOCKS 15
#define LENGTH_OF_ID 0x14

//Regions
#define JAPAN 'I'
#define AMERICA 'A'
#define EUROPE 'E'


//POINTER - union that lets you access a pointer in 1 or 2 byte chunks (char * + short *)
typedef union{
	unsigned char *u8;
	unsigned short *u16;
}pointer;


//MC_TYPE - The format of the memory card
typedef enum{
	RAW,
	PSP,
	DEX
}mc_type;


//BLOCK - A Memory Card Block
typedef struct{
	unsigned char number, status, region, pocket_station;
	unsigned char *data, *id, *pocket_station_icon;
	enum CORE_TYPE core;
}block;

//MC - A Data structure representing a Memory Card
typedef struct{
	mc_type type;
	int length;
	unsigned char *data;
	block blocks[15];
}mc_symbolic;


#endif
