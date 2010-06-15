#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/strsafe.h"

#define USAGE "Usage: %s UNIT TYPE WIDTH\n"\
              "  Where\n"\
              "    UNIT is\n"\
              "      ch if character counts are used and\n"\
              "      b if byte counts are used.\n"\
              "    TYPE is\n"\
              "      A if ordinary chars are used and\n"\
              "      W if wide chars are used.\n"\
              "    WIDTH is the capacity of the buffer used for testing.\n"

void StringCchEchoA(size_t width){
	HRESULT result = S_OK;
	char * buf = malloc(width);
	while(result != STRSAFE_E_END_OF_FILE){
		const char * res;
		result = StringCchGetsA(buf, width);
		switch(result){
			case S_OK:
				res = "OK";
				break;
			case STRSAFE_E_END_OF_FILE:
				res = "End of file";
				break;
			case STRSAFE_E_INVALID_PARAMETER:
				res = "Invalid parameter";
				break;
			case STRSAFE_E_INSUFFICIENT_BUFFER:
				res = "Insufficient buffer";
		}
		printf("\"%s\" - %s\n", buf, res);
	}
}

void StringCchEchoW(size_t width){
	HRESULT result;
	wchar_t * buf = malloc(width * sizeof(wchar_t));
	while(result != STRSAFE_E_END_OF_FILE){
		const char * res;
		result = StringCchGetsW(buf, width);
		switch(result){
			case S_OK:
				res = "OK";
				break;
			case STRSAFE_E_END_OF_FILE:
				res = "End of file";
				break;
			case STRSAFE_E_INVALID_PARAMETER:
				res = "Invalid parameter";
				break;
			case STRSAFE_E_INSUFFICIENT_BUFFER:
				res = "Insufficient buffer";
		}
		printf("\"%ls\" - %s\n", buf, res);
	}
}

void StringCbEchoA(size_t width){
	HRESULT result;
	char * buf = malloc(width);
	while(result != STRSAFE_E_END_OF_FILE){
		const char * res;
		result = StringCbGetsA(buf, width);
		switch(result){
			case S_OK:
				res = "OK";
				break;
			case STRSAFE_E_END_OF_FILE:
				res = "End of file";
				break;
			case STRSAFE_E_INVALID_PARAMETER:
				res = "Invalid parameter";
				break;
			case STRSAFE_E_INSUFFICIENT_BUFFER:
				res = "Insufficient buffer";
		}
		printf("\"%s\" - %s\n", buf, res);
	}
}

void StringCbEchoW(size_t width){
	HRESULT result;
	wchar_t * buf = malloc(width);
	while(result != STRSAFE_E_END_OF_FILE){
		const char * res;
		result = StringCbGetsW(buf, width);
		switch(result){
			case S_OK:
				res = "OK";
				break;
			case STRSAFE_E_END_OF_FILE:
				res = "End of file";
				break;
			case STRSAFE_E_INVALID_PARAMETER:
				res = "Invalid parameter";
				break;
			case STRSAFE_E_INSUFFICIENT_BUFFER:
				res = "Insufficient buffer";
		}
		printf("\"%ls\" - %s\n", buf, res);
	}
}

int main(int argc, const char * argv[]){
	const char * unit;
	const char * type;
	int width;

	if(argc != 4){
		printf("Wrong number of parameters.\n\n");
		printf(USAGE, argv[0]);
		return 1;
	}

	unit = argv[1];
	type = argv[2];
	width = atoi(argv[3]);

	if((strcmp(unit, "ch") && strcmp(unit, "b")) ||
			(strcmp(type, "A") && strcmp(type, "W")) ||
			(width == 0 && strcmp(argv[3], "0")) ||
			width == INT_MIN || width == INT_MAX){ 
		printf("Wrong data in parameters.\n\n");
		printf(USAGE, argv[0]);
		return 2;
	}

	if(strcmp(unit, "b")){
		if(strcmp(type, "W")){
			StringCchEchoA(width);
		} else {
			StringCchEchoW(width);
		}
	} else {
		if(strcmp(type, "W")){
			StringCbEchoA(width);
		} else {
			StringCbEchoW(width);
		}
	}

	return 0;
}
