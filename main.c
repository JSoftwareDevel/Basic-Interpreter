#include <stdio.h>
#include <malloc.h>


typedef enum  
{ SUM, REST, DIV, NUMBER,NONE,EXP }Opcode;

typedef struct toke_struct
{
	Opcode op;
	int num;
}Token_t;


typedef struct node_struct
{
	struct node_struct *left;
	Token_t token;
	struct node_struct *right;
}Node_t;


Token_t GetToken(char in)
{
	Token_t token;
	token.op = NONE;

	if (in >= '0' && in <= '9') 
	{
		token.num = in - '0';
		token.op = NUMBER;
		return token;
	}

	switch (in)
	{
	case '+':
		token.op = SUM;
		return token;
		break;
	case '-':
		token.op = REST;
		return token;
		break;
	}
	printf("Error\n");
	exit(-1);
	return token;
}


Node_t* ParseTree(char *input,int count)
{
	Node_t *node;
	node = malloc(sizeof(Node_t));

	node->left = NULL;
	node->token.op = NONE;
	node->token.num = 0;
	node->right = NULL;

	Token_t token = GetToken(input[count]);

	return node;
}


int main(void)
{
	char input[] = "5+2\n";
	Node_t *tree;
	tree  = ParseTree(input,0);



	return 0;
}