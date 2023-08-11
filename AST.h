// Header file to create Abstract Syntax Tree (AST)
#include <string.h>

// Define struct for AST nodes
struct AST{
	char nodeType[50];
	char LHS[50];
	char RHS[50];
	
	struct AST * left;
	struct AST * right;

	int value;
};

// Function that creates and returns AST node for an assignment operation
struct AST * AST_assignment(char nodeType[50], char LHS[50], char RHS[50]){
	struct AST* ASTassign = malloc(sizeof(struct AST));
	strcpy(ASTassign->nodeType, nodeType);
	strcpy(ASTassign->LHS, LHS);
	strcpy(ASTassign->RHS, RHS);

/*
       	   =
	 /   \
	x     y

*/

	return ASTassign;
}

// Function that creates and returns AST node for a binary expression
struct AST * AST_BinaryExpression(char nodeType[50], char LHS[50], char RHS[50]){
	struct AST* ASTBinExp = malloc(sizeof(struct AST));
	strcpy(ASTBinExp->nodeType, nodeType);
	strcpy(ASTBinExp->LHS, LHS);
	strcpy(ASTBinExp->RHS, RHS);

	return ASTBinExp;
}

// Function that creates and returns AST node for a type declaration
struct AST * AST_Type(char nodeType[50], char LHS[50], char RHS[50]){
	struct AST* ASTtype = malloc(sizeof(struct AST));
	strcpy(ASTtype->nodeType, nodeType);
	strcpy(ASTtype->LHS, LHS);
	strcpy(ASTtype->RHS, RHS);
		
	return ASTtype;
}

// Function that creates and returns AST node for a function call
struct AST * AST_Func(char nodeType[50], char LHS[50], char RHS[50]){
	struct AST* ASTtype = malloc(sizeof(struct AST));
	strcpy(ASTtype->nodeType, nodeType);
	strcpy(ASTtype->LHS, LHS);
	strcpy(ASTtype->RHS, RHS);
	
	return ASTtype;
}

// Function that creates and returns AST node for a 'write' statement
struct AST * AST_Write(char nodeType[50], char LHS[50], char RHS[50]){
	struct AST* ASTtype = malloc(sizeof(struct AST));
	strcpy(ASTtype->nodeType, nodeType);
	strcpy(ASTtype->LHS, LHS);
	strcpy(ASTtype->LHS, RHS);
		
	return ASTtype;
}

// Function that creates and returns AST node for 'if' statement w/o an 'else' statement 
struct AST * AST_If(char nodeType[50], char LHS[50], struct AST * thenBranch){
	printf("AST_If() is called\n");
	struct AST * ASTtype = malloc(sizeof(struct AST));
	strcpy(ASTtype->nodeType, nodeType);
	strcpy(ASTtype->LHS, LHS);
	strcpy(ASTtype->RHS, "");

	ASTtype->left = thenBranch;
	ASTtype->right = NULL;

	return ASTtype;
}

// Function that creates and returns AST node for 'while' statement w/o an 'else' statement 
struct AST * AST_While(char nodeType[50], char LHS[50], struct AST * thenBranch){
	printf("AST_While() is called\n");
	struct AST * ASTtype = malloc(sizeof(struct AST));
	strcpy(ASTtype->nodeType, nodeType);
	strcpy(ASTtype->LHS, LHS);
	strcpy(ASTtype->RHS, "");

	ASTtype->left = thenBranch;
	ASTtype->right = NULL;

	return ASTtype;
}

// Function that creates and returns AST node for 'if-else' statement
struct AST * AST_IfElse(char nodeType[50], char LHS[50], struct AST * thenBranch, struct AST * elseBranch){
	struct AST * ASTtype = malloc(sizeof(struct AST));
	strcpy(ASTtype->nodeType, nodeType);
	strcpy(ASTtype->LHS, LHS);
	strcpy(ASTtype->RHS, "");

	ASTtype->left = thenBranch;
	ASTtype->right = elseBranch;

	return ASTtype;
}

// Create and return AST node for a nested 'if-else' statement
struct AST * AST_IfIfElse(char nodeType[50], char LHS1[50], struct AST * thenBranch1, char LHS2[50], struct AST * thenBranch2, struct AST * elseBranch){
	struct AST * ASTtype1 = malloc(sizeof(struct AST));
	strcpy(ASTtype1->nodeType, nodeType);
	strcpy(ASTtype1->LHS, LHS1);
	strcpy(ASTtype1->RHS, "");

	struct AST * ASTtype2 = malloc(sizeof(struct AST));
	strcpy(ASTtype2->nodeType, nodeType);
	strcpy(ASTtype2->LHS, LHS2);
	strcpy(ASTtype2->RHS, "");

	ASTtype1->left = thenBranch1;
	ASTtype1->right = ASTtype2;

	ASTtype2->left = thenBranch2;
	ASTtype2->right = elseBranch;

	return ASTtype1;
}

// Function that compares two values based on the given operator
int compareValues(int value1, const char* operator, int value2) {
    if (strcmp(operator, "==") == 0) {
        return value1 == value2;
    } else if (strcmp(operator, "!=") == 0) {
        return value1 != value2;
    } else if (strcmp(operator, "<") == 0) {
        return value1 < value2;
    } else if (strcmp(operator, ">") == 0) {
        return value1 > value2;
    } else if (strcmp(operator, "<=") == 0) {
        return value1 <= value2;
    } else if (strcmp(operator, ">=") == 0) {
        return value1 >= value2;
    } else {
        return 0;
    }
}

// Function that prints dots (indentation) for AST node formatting
void printDots(int num){
	for (int i = 0; i < num; i++)
		printf("      ");
}

// Function that prints the AST
void printAST(struct AST* tree, int level) {
    if (tree == NULL) return;
    printDots(level);
    printf("%s", tree->nodeType);
    if (strcmp(tree->nodeType, "NUM") == 0 || strcmp(tree->nodeType, "ID") == 0) {
        printf(" -> %d\n", tree->value);
    } else {
        printf("\n");
    }
    printDots(level);
    printf("%s %s\n", tree->LHS, tree->RHS);
    if (tree->left != NULL) printAST(tree->left, level + 1);
    if (tree->right != NULL) printAST(tree->right, level + 1);
}
