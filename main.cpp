#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>

#define TOKEN_MAX 100
#define VAR_MAX 10
#define TRUE 1
#define FALSE 0

typedef enum
{
	SUM, REST, DIV, NUMBER, NONE, EXP, IF_STATEMENT, ASIGNATION, GOTO_STATEMENT, THEN_STATEMENT, COMPARE_LESS, LINE_NUMBER, PRINT_STATEMENT, INTEGER_VAR, END
}Opcode;

typedef struct toke_struct
{
	Opcode op;
	int num;
	char name[50];
}Token_t;

typedef struct node_struct
{
	struct node_struct* left;
	Token_t token;
	struct node_struct* right;
}Node_t;

typedef struct {
	Opcode op;
	int val;
	char name[50];
}Var_t;

static int ExecuteLine = 0;
static char BranchActivate = FALSE;
static char running = TRUE;
static Var_t VarTable[10];
static int VarNumber = 0;

void Error(const char mesg[])
{
	printf(mesg);
	printf("-----------Fatal Error-----------\n");
	_getch();
}

int SearchNonFinal(Token_t tokenList[], int start, int finish)
{
	for (int i = start; i < finish; i++) {
		if (tokenList[i].op != NUMBER &&
			tokenList[i].op != INTEGER_VAR &&
			tokenList[i].op != END) {
			return i;
		}
	}
	return -1;
}

int SearchThenStart(Token_t tokenList[], int start, int finish)
{
	for (int i = start; i < finish; i++) {
		if (tokenList[i].op == THEN_STATEMENT) return i;
	}
	return -1;
}

void Parse(Node_t*& node, Token_t tokenList[], int start, int finish)
{
	int nonFinal = SearchNonFinal(tokenList, start, finish);
	node = (Node_t*)malloc(sizeof(Node_t));
	if (node != NULL) {

		if (nonFinal == -1) {
			node->left = NULL;
			node->token = tokenList[start];
			node->right = NULL;
		}
		else {

			switch (tokenList[start].op) {
			case IF_STATEMENT:
			{
				int thenPosition = SearchThenStart(tokenList, start, finish);
				if (thenPosition == -1) Error("IF THEN STATEMENT FAILURE\n");
				Parse(node->left, tokenList, start + 1, thenPosition - 1); // TODO HASTA THEN
				node->token = tokenList[nonFinal];
				Parse(node->right, tokenList, thenPosition + 1, finish);  //TODO DESPUES DE THEN
			}
			break;


				//case ASIGNATION:
				//	node->left = NULL;
				//	node->token = tokenList[start];
				//	node->right = Parse(node->right, tokenList, nonFinal + 1, finish);
				//	break;
	/*		case SUM:
			{
				int a = 2342;
			}*/

			case SUM:
				Parse(node->left, tokenList, nonFinal - 1, nonFinal - 1);
				node->token = tokenList[nonFinal];
				Parse(node->right, tokenList, nonFinal + 1, finish);
				break;

			//case INTEGER_VAR:
			//	node->left = NULL;
			//	node->token = tokenList[start];
			//	node->right = NULL;
			//	break;

			case GOTO_STATEMENT:
			case PRINT_STATEMENT:
			{
				Parse(node->left, tokenList, start + 1, finish);
				node->token = tokenList[nonFinal];
				node->right = NULL;
			}
			break;

			default:
				Parse(node->left, tokenList, nonFinal - 1, nonFinal - 1);
				node->token = tokenList[nonFinal];
				Parse(node->right, tokenList, nonFinal + 1, finish);
				break;
			}
		}
	}
	else {
		Error("No Memory\n");
	}
}

void FreeTree(Node_t* node)
{

}

Token_t* GenLexer(Token_t* tokenArray, char* input, int lenght)
{
	for (int i = 0; i < TOKEN_MAX; i++) {
		tokenArray[i].op = END;
		tokenArray[i].num = 0;
	}

	char firstNumber = TRUE;

	for (int i = 0, inputIndex = 0; inputIndex < lenght; i++, inputIndex++) {
		tokenArray[i].op = END;
		tokenArray[i].num = 0;

		if (input[inputIndex] >= '0' && input[inputIndex] <= '9') //Safe code
		{
			char stringNumber[10] = { '\0' };
			const int maxString = 9;
			for (int j = 0; input[inputIndex] >= '0' && input[inputIndex] <= '9' && inputIndex < lenght && j < maxString; inputIndex++, j++) {
				if (j + 1 >= maxString)Error("Max Lenght Error\n");
				stringNumber[j] = input[inputIndex];
			}

			tokenArray[i].num = atoi(stringNumber);
			if (firstNumber == TRUE)
				tokenArray[i].op = LINE_NUMBER;
			else
				tokenArray[i].op = NUMBER;
			firstNumber = FALSE;
			inputIndex--;
			continue;
		}

		if (input[inputIndex] == 'I' && input[inputIndex + 1] == 'F') //Unsafe code
		{
			tokenArray[i].op = IF_STATEMENT;

			inputIndex += 1;
			continue;
		}

		if (input[inputIndex] == 'G' && input[inputIndex + 1] == 'O' && input[inputIndex + 2] == 'T' && input[inputIndex + 3] == 'O') //Unsafe code
		{
			tokenArray[i].op = GOTO_STATEMENT;
			inputIndex += 3;
			continue;
		}

		if (input[inputIndex] == 'P' && input[inputIndex + 1] == 'R' && input[inputIndex + 2] == 'I' && input[inputIndex + 3] == 'N' && input[inputIndex + 4] == 'T') //Unsafe code
		{
			tokenArray[i].op = PRINT_STATEMENT;
			inputIndex += 4;
			continue;
		}

		if (input[inputIndex] == 'T' && input[inputIndex + 1] == 'H' && input[inputIndex + 2] == 'E' && input[inputIndex + 3] == 'N') //Unsafe code
		{
			tokenArray[i].op = THEN_STATEMENT;
			inputIndex += 3;
			continue;
		}

		switch (input[inputIndex])
		{
		case '+':
			tokenArray[i].op = SUM;
			continue;
			break;
		case '-':
			tokenArray[i].op = REST;
			continue;
			break;
		case '<':
			tokenArray[i].op = COMPARE_LESS;
			continue;
			break;
		case '=':
			tokenArray[i].op = ASIGNATION;
			continue;
			break;
		}

		//Siempre ultima
		if (input[inputIndex] >= 'A' && input[inputIndex] <= 'Z') //Bad Code
		{
			char stringNumber[VAR_MAX + 10] = { '\0' }; // por las dudas
			const int maxString = 10;
			for (int j = 0; input[inputIndex] >= 'A' && input[inputIndex] <= 'Z' && inputIndex < lenght && j < maxString; inputIndex++, j++) {
				if (j + 1 >= maxString)Error("Max Lenght Error\n");
				stringNumber[j] = input[inputIndex];
			}
			memcpy(tokenArray[i].name, stringNumber, sizeof(char) * VAR_MAX);
			tokenArray[i].op = INTEGER_VAR;
			inputIndex--;
			continue;
		}

		if (input[inputIndex] != ' ' && input[inputIndex] != '\n') {
			Error("Invalid Format Statement\n");
		}

		i--;//No Token this is an error
	}
	return tokenArray;
}

int GetVar(char name[])
{
	for (int i = 0; i < VarNumber; i++) {
		if (strcmp(name, VarTable[i].name) == 0) {
			return VarTable[i].val;
		}
	}
	Error("Var not found\n");
	return -1;
}

void AssignOrCreate(char name[], int num)
{
	for (int i = 0; i < VarNumber; i++) {
		if (strcmp(name, VarTable[i].name) == 0) {
			VarTable[i].val = num;
			return;
		}
	}
	strcpy(VarTable[VarNumber].name, name);
	VarTable[VarNumber].val = num;
	VarNumber++;
}

int ResolveTree(Node_t* tree)
{
	int value = 0;
	switch (tree->token.op) {
	case IF_STATEMENT:
		ResolveTree(tree->left) == TRUE ? value = ResolveTree(tree->right) : value = FALSE;
		break;
	case SUM:
		value = ResolveTree(tree->left) + ResolveTree(tree->right);
		break;
	case REST:
		value = ResolveTree(tree->left) - ResolveTree(tree->right);
		break;
	case NUMBER:
		value = tree->token.num;
		break;
	case COMPARE_LESS:
		ResolveTree(tree->left) < ResolveTree(tree->right) ? value = TRUE : value = FALSE;
		break;
	case PRINT_STATEMENT:
		printf("%d\n", ResolveTree(tree->left));
		break;
	case INTEGER_VAR:
		value = GetVar(tree->token.name);
		break;
	case ASIGNATION:
		AssignOrCreate(tree->left->token.name, ResolveTree(tree->right));
		break;
	case GOTO_STATEMENT:
		BranchActivate = TRUE;
		ExecuteLine = ResolveTree(tree->left);
		break;
	}
	return value;
}

int main(void)
{
	constexpr int codeSize = 4;
	char input[codeSize][50] = {  "0 COUNT = 1                \n",
								  "1 COUNT = COUNT + 1        \n",
								  "2 IF COUNT<99 THEN GOTO 1  \n",
								  "3 PRINT COUNT              \n",
	};

	for (int i = 0; i < codeSize; i++) printf(input[i]);
	for (int i = 0; i < 3; i++) printf("\n");
	printf("OUT PROGRAM: \n");

	Token_t tokens[codeSize][TOKEN_MAX];
	for (int i = 0; i < codeSize; i++) GenLexer(&tokens[i][0], input[i], strlen(input[i]));

	Node_t* parsertree[codeSize] = { NULL };
	for (int i = 0; i < codeSize; i++) Parse(parsertree[i], &tokens[i][0], 1, TOKEN_MAX);

	while (running == TRUE) {
		ResolveTree(parsertree[ExecuteLine]);
		BranchActivate == TRUE ? BranchActivate = FALSE : ExecuteLine++;
		if (ExecuteLine > codeSize - 1) running = FALSE;
	}

	printf("--------End-------\n");

	_getch();
	return 0;
}