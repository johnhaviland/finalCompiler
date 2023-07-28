// Header file to create Abstract Syntax Tree (AST)
#include <string.h>

struct AST{
	char nodeType[50];
	char LHS[50];
	char RHS[50];
	
	struct AST * left;
	struct AST * right;

	int value;
};



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

struct AST * AST_BinaryExpression(char nodeType[50], char LHS[50], char RHS[50]){
	struct AST* ASTBinExp = malloc(sizeof(struct AST));
	strcpy(ASTBinExp->nodeType, nodeType);
	strcpy(ASTBinExp->LHS, LHS);
	strcpy(ASTBinExp->RHS, RHS);
	
	return ASTBinExp;
}

struct AST * AST_Type(char nodeType[50], char LHS[50], char RHS[50]){
	struct AST* ASTtype = malloc(sizeof(struct AST));
	strcpy(ASTtype->nodeType, nodeType);
	strcpy(ASTtype->LHS, LHS);
	strcpy(ASTtype->RHS, RHS);
		
	return ASTtype;
	
}

struct AST * AST_Func(char nodeType[50], char LHS[50], char RHS[50]){
	struct AST* ASTtype = malloc(sizeof(struct AST));
	strcpy(ASTtype->nodeType, nodeType);
	strcpy(ASTtype->LHS, LHS);
	strcpy(ASTtype->RHS, RHS);
	
	return ASTtype;
}

struct AST * AST_Write(char nodeType[50], char LHS[50], char RHS[50]){
	struct AST* ASTtype = malloc(sizeof(struct AST));
	strcpy(ASTtype->nodeType, nodeType);
	strcpy(ASTtype->LHS, LHS);
	strcpy(ASTtype->LHS, RHS);
		
	return ASTtype;
}

struct AST * AST_If(char nodeType[50], char LHS[50], struct AST * thenBranch){
	struct AST * ASTif = malloc(sizeof(struct AST));
	strcpy(ASTif->nodeType, nodeType);
	strcpy(ASTif->LHS, LHS);
	strcpy(ASTif->RHS, "");

	ASTif->left = thenBranch;
	ASTif->right = NULL;

	return ASTif;
}

struct AST * AST_IfElse(char nodeType[50], char LHS[50], struct AST * thenBranch, struct AST * elseBranch){
	struct AST * ASTifelse = malloc(sizeof(struct AST));
	strcpy(ASTifelse->nodeType, nodeType);
	strcpy(ASTifelse->LHS, LHS);
	strcpy(ASTifelse->RHS, "");

	ASTifelse->left = thenBranch;
	ASTifelse->right = elseBranch;

	return ASTifelse;
}

struct AST * AST_IfIfElse(char nodeType[50], char LHS1[50], struct AST * thenBranch1, char LHS2[50], struct AST * thenBranch2, struct * elseBranch){
	struct AST * ASTififelse = malloc(sizeof(struct AST));
	strcpy(ASTififelse->nodeType, nodeType);
	strcpy(ASTififelse->LHS, LHS1);
	strcpy(ASTififelse->RHS, "");

	struct AST * ASTifelseBranch = malloc(sizeof(struct AST));
	strcpy(ASTifelseBranch->nodeType, nodeType);
	strcpy(ASTifelseBranch->LHS, LHS2);
	strcpy(ASTifelseBranch->RHS, "");

	ASTififelse->left = thenBranch1;
	ASTififelse->right = ASTifelseBranch;

	ASTifelseBranch->left = thenBranch2;
	ASTifelseBranch->right = elseBranch;

	return ASTififelse;
}

void printDots(int num){
	for (int i = 0; i < num; i++)
		printf("      ");
}

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
