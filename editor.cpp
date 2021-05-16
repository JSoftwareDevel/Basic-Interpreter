#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "editor.h"

#define TEXT_BUFFER 1000

void savefile(char text[TEXT_BUFFER][TEXT_BUFFER])
{
	FILE *file = NULL;
	file = fopen("program.bas","w");
	if (file == NULL) {
		printf("Error open file\n");
		return;
	}

	for(int i=0;i<TEXT_BUFFER;i++){
			fprintf(file,"%s",text[i]);
	}

	fclose(file);
}

void readfile(char text[TEXT_BUFFER][TEXT_BUFFER])
{
	FILE *file = NULL;
	file = fopen("program.bas","r");
	if(file == NULL){
		printf("Error can't open file");
		return;
	}

	fseek(file,0,SEEK_SET);

	{
		int fileend = 0;
		int j=0,i=0;
		while(fileend == 0){		
			char c = fgetc(file);
			if (c == EOF){
				fileend = 1;
			}else{
				if (c == '\n'){
					text[i][j] = (unsigned char)c;
					i++;
					j=0;
				}else{
					text[i][j] = (unsigned char)c;
					j++;
				}
			}
		}
	}

	fclose(file);
}

int editorstart(char text[TEXT_BUFFER][TEXT_BUFFER])
{
	char buffer[TEXT_BUFFER];
	char run = 1;
	char debug = 0;

	//memset(text,0,sizeof(char)*TEXT_BUFFER*TEXT_BUFFER);
	memset(buffer,0,sizeof(char)*TEXT_BUFFER);
	printf("Init basic editor\n");
	int x = 0;
	while(run){
		char character = getchar();

		if (character == '\n'){
			buffer[x] = '\n';
			if (strcmp("LIST\n",buffer) == 0){
				printf("---List---\n");
				if (debug) printf("debug list detected");
				for(int i = 0; i <= TEXT_BUFFER; i++){
					printf("%s",text[i]);
				}
			}else if (strcmp("SAVE\n",buffer) == 0){
				savefile(text);
				printf("File save...\n");
			}else if (strcmp("QUIT\n",buffer) == 0){
				printf("Exit text editor...\n");
				run = 0;
				break;
			}else if (strcmp("LOAD\n",buffer) == 0 ){
				printf("Loading file...\n");
				memset(text,0,sizeof(char)*TEXT_BUFFER*TEXT_BUFFER);
				readfile(text);
			}else if ( strcmp("CLEAR\n",buffer) == 0) {
				system("clear");
			}else if ( strcmp("RUN\n",buffer) == 0) {
				return 0; //Exit to interpreter
			}else{
				if( buffer[0] >= '0' && buffer[0] <='9'){
					int counter = 0;
					while( buffer[counter] != '\n' && buffer[counter]>='0' && buffer[counter]<='9' ){
						counter++;
					}
					if (buffer[counter] != ' '){
						printf("Inmediate value for basic interpreter\n");
					}else{
						int lineNumber = atoi(buffer);
						if (lineNumber >= TEXT_BUFFER){
							printf("Error buffer overflow\n");
							exit(-1);
						}
						memcpy(text[lineNumber],buffer,sizeof(char)*TEXT_BUFFER);
					}
				}else{
					printf("syntax error\n");
				}
			}
			memset(buffer,0,sizeof(char)*TEXT_BUFFER);
			x=0;
			continue;
		}

		buffer[x] = character;
		x++;
	}
	return 0;
}
