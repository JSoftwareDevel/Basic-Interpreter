#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "interpreter.h"
#include "editor.h"

int main()
{
	char codetext[TEXT_BUFFER][TEXT_BUFFER];
	memset(codetext,0,sizeof(char)*TEXT_BUFFER*TEXT_BUFFER);

	editorstart(codetext);
	runinterpreter(codetext);

	return 0;
}


