#include <stdio.h>

#define LOW_BYTE(x) (x) >> 8

int get_char(unsigned short character){
	switch(character & 0xff){
		case 0x81: //Symbols
			 switch((character & 0xff00) >> 8){
			 	case 0x40:
					printf(" ");
					break;
				case 0x43:
					printf(",");
					break;
				case 0x44:
					printf(".");
					break;
				case 0x45:
					printf("");
					break;
				case 0x46:
					printf(":");
					break;
				case 0x47:
					printf(";");
					break;
				case 0x48:
					printf("?");
					break;
				case 0x49:
					printf("!");
					break;
				case 0x51:
					printf("_");
					break;
				case 0x5e:
					printf("/");
					break;
				case 0x5f:
					printf("\\");
					break;
				case 0x6d:
					printf("[");
					break;
				case 0x6e:
					printf("]");
					break;
				case 0x71:
					printf("<");
					break;
				case 0x72:
					printf(">");
					break;
				case 0x7c:
					printf("-");
					break;
				case 0x90:
					printf("$");
					break;
				case 0x93:
					printf("%%");
					break;
				break;
			 }
			 break;
		case 0x82:
			 if(LOW_BYTE(character & 0xff00) < 0x80){ //Capital Letters & Numbers
			 	printf("%c", (unsigned char)(((character & 0xff00) >> 8)  - 0x1f));
				break;
			 }
			 if(((character & 0xff) >> 8) < 0x9c){ //Lowercase Letters
			 	printf("%c", (unsigned char)(((character & 0xff00) >> 8) - 0x20));
				break;
			 }
			 break;
		case 0x83:
			 break;
	}
	return 0;

}
