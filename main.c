#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

	for(int i = 0; i < TEXT_BUFFER; i++){
		fscanf(file,"%s",text[i]);
	}

	fclose(file);
}


int main()
{
	char text[TEXT_BUFFER][TEXT_BUFFER];
	char buffer[TEXT_BUFFER];
	char run = 1;
	char debug = 0;

	memset(text,0,sizeof(char)*TEXT_BUFFER*TEXT_BUFFER);
	memset(buffer,0,sizeof(char)*TEXT_BUFFER);
	printf("Init basic editor\n");
	int x = 0;
	while(run){
		char character = getchar();

		if (character == '\n'){
			buffer[x] = '\n';
			if (strcmp("list\n",buffer) == 0){
				printf("---List---\n");
				if (debug) printf("debug list detected");
				for(int i = 0; i <= TEXT_BUFFER; i++){
					printf("%s",text[i]);
				}
			}else if (strcmp("save\n",buffer) == 0){
				savefile(text);
				printf("File save...\n");
			}else if (strcmp("quit\n",buffer) == 0){
				printf("Exit text editor...\n");
				run = 0;
				break;
			}else if (strcmp("load\n",buffer) == 0 ){
				printf("Loading file...\n");
				readfile(text);
			}else if ( strcmp("clear\n",buffer) == 0) {
				system("clear");
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

