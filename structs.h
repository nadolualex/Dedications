#include<inttypes.h>

typedef struct head {
	unsigned char type; //tipul de date stocate
	unsigned int len;//lungimea totala
} head;//structura header

typedef struct data_structure {
	head *header; //header -ul datelor
	void *data;  //datele efective
} data_structure;//structura de pasare a datelor

typedef struct tip1 {
    char* cel_care_dedica;
    int8_t prima;
    int8_t doua;
    char* celui_care_dedica;

} tip1;

typedef struct tip2 {
    char * cel_care_dedica;
    int16_t prima;
    int32_t doua;
    char* celui_care_dedica;
} tip2;

typedef struct tip3 {
    char * cel_care_dedica;
    int32_t prima;
    int32_t doua;
    char* celui_care_dedica;
} tip3;