#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	FILE* target = fopen(argv[1], "rb+");
	fseek(target, 0x3C, SEEK_SET);
	char pointer[3];
	fread(pointer, 1, 2, target);
	
	if (argc > 2) {
		if (strcmp(argv[2], "b")) {
			char destination[strlen(argv[1])+7];
			strcpy(destination, argv[1]);
			strcat(destination, ".BACKUP");
			
			fseek(target, 0, SEEK_END);
			long length = ftell(target);
			fseek(target, 0, SEEK_SET);
			char* data = malloc(length+1);
			fread(data, length, 1, target);
			
			FILE* backup = fopen(destination, "wb+");
			fwrite(data, length, 1, backup);
			fclose(backup);
			free(data);
		}
	}
	fseek(target, (pointer[0]|pointer[1]<<8)+22, SEEK_SET);
	char byte[2];
	fread(byte, 1, 1, target);
	
	fseek(target, -1, SEEK_CUR);
	byte[0] |= 0x20;
	fwrite(byte, 1, 1, target);
	fclose(target);
}
