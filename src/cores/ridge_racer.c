//Ridge Racer core by Enzo_a_person

#include <stdio.h>

#define START_OF_TIMES 0x100
#define LENGTH_OF_DATA 0x0c
#define NUMBER_OF_CARS 13
#define NUMBER_OF_COURSES 4
#define NUMBER_OF_SONGS 7
#define NUMBER_OF_CONTROL_SCHEMES 4
#define DEFAULT_CAR_OFFSET 0x1e0
#define DEFAULT_SONG_OFFSET 0x1e2
#define DEFAULT_CONTROLLER_OFFSET 0x1ca
#define DEFAULT_TRANSMISSION_OFFSET 0x1de
#define DEFAULT_COURSE_OFFSET 0x1dc
#define DEFAULT_MIRRORED_OFFSET 0x1dA

#define MINUTES_IN_MILLISEC 60000
#define SECONDS_IN_MINUTE 60
#define MILLISEC_IN_SECONDS 1000
#define CALCU_MINUTES(X) (X)/MINUTES_IN_MILLISEC
#define CALCU_SECONDS(X) ((X)/1000) - ((CALCU_MINUTES(X)) * SECONDS_IN_MINUTE)
#define CALCU_MILLISEC(X) (X) - (((X)/1000)*MILLISEC_IN_SECONDS)

char *car_names[NUMBER_OF_CARS] = {"F/A Racing", "RT Ryukyu", "RT Yellow Solvalou", "RT Blue Solvalou",
 "RT Pink Mappy", "RT Blue Mappy", "Galaga RT PLID's", "Galaga RT Carrot", "RT Bosconian", "RT Nebulasray", 
 "RT Xevious Red", "RT XEVIOUS GREEN", "13\" Racing"};
char *song_names[NUMBER_OF_SONGS] = {"Random Play", "Ridge Racer", "Rare Hero", 
	"Feeling Over", "Rotterdam Nation", "Speedster", "Rhythm Shift"};
char *courses[NUMBER_OF_COURSES] = {"Beginner", "Mid-Level", "High-Level", "T.T."};

char ridge_racer(unsigned char *data){
	printf("  Top Times:\n"); //Time Trial Data
	for(unsigned char s = 0; s <= 5; s++){
		printf("   ");
		for(unsigned char i = 0; i < 3; i++){ // Print the name first
			printf("%c", data[START_OF_TIMES + ((s)*LENGTH_OF_DATA) + i]);
		}
		//Figure out time then print
		int time = 0x30000 + data[START_OF_TIMES+(s*LENGTH_OF_DATA)+4] + (data[START_OF_TIMES+(s*LENGTH_OF_DATA)+5] << 8);
		printf("\t%d\'%02d\"%03d ", CALCU_MINUTES(time), CALCU_SECONDS(time), CALCU_MILLISEC(time));
		unsigned char car = data[(START_OF_TIMES+(s*LENGTH_OF_DATA))+8]; //Figure out which car it was with then print
		if(car < NUMBER_OF_CARS){
			printf("%s", car_names[car]);
		}
		printf("\n");
	}
	//Defaults data
	printf("  Defaults:\n");
	unsigned char default_song = data[DEFAULT_SONG_OFFSET];
	unsigned char default_car = data[DEFAULT_CAR_OFFSET];

	if(data[DEFAULT_COURSE_OFFSET] <= NUMBER_OF_COURSES){
		printf("   Course: %s ", courses[data[DEFAULT_COURSE_OFFSET] - 1]);
		if(data[DEFAULT_MIRRORED_OFFSET]){
			printf("Extra");
		}
		printf("\n");
	}

	if(data[DEFAULT_TRANSMISSION_OFFSET] <= 1){
		printf("   Transmission: "); 
		if(data[DEFAULT_TRANSMISSION_OFFSET]){
			printf("Manual\n");
		}else{
			printf("Automatic\n");
		}
	}	
	if(default_car < NUMBER_OF_CARS){
			printf("   Car: %s\n", car_names[default_car]);
	}

	if(default_song < NUMBER_OF_SONGS){
			printf("   Song: %s\n", song_names[default_song]);
		
	}
	if(data[DEFAULT_CONTROLLER_OFFSET] < NUMBER_OF_CONTROL_SCHEMES){
		printf("   Control Scheme: %c\n", 'A' + data[DEFAULT_CONTROLLER_OFFSET]);
	}
}
