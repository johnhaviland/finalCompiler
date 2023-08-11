%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "symbolTable.h"
#include "AST.h"
#include "IRcode.h"
#include "Assembly.h"
#include "registerManager.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);
char currentScope[50]; 
int result = 0;
int semanticCheckPassed = 1; 
%}

%union {
	int number;
	char character;
	char* string;
	struct AST* ast;
}

%token <string> TYPE
%token <string> ID
%token <character> SEMICOLON
%token <string> EQ 
%token <string> MATHOP
%token <string> COMPOP
%token <string> LOGOP
%token <number> NUMBER
%token <string> WRITE
%token <character> LPAREN
%token <character> RPAREN
%token <character> LBRACK
%token <character> RBRACK
%token <character> LBRACE
%token <character> RBRACE
%token <character> COMMA
%token <string> IF
%token <string> ELSE
%token <string> WHILE
%token <character> NOT


%left '+' '-'
%left '*' '/'

%left AND
%left OR
%left '!'

%printer { fprintf(yyoutput, "%s", $$); } ID;
%printer { fprintf(yyoutput, "%d", $$); } NUMBER;

%type <ast> Program DeclList Decl VarDecl Stmt StmtList Expr Rec Array FuncDecl IfStmt WhileStmt ElseStmt WriteStmt FuncStmt FuncBody

%start Program

%%

Program:	DeclList { 
			$$ = $1;
			printf("\n--- Abstract Syntax Tree ---\n\n");
			printAST($$, 0);
		}
;


DeclList:	Decl DeclList {
    			$1->left = $2;
			$$ = $1;
		}
		
		| Decl	{
    			$$ = $1; 
		}
;


Decl:	VarDecl
	| FuncDecl
	| StmtList
;


VarDecl:	{}

		| TYPE ID SEMICOLON { 
    			char id1[50];
    			printf("\n RECOGNIZED RULE: Variable declaration %s\n", $2);
			symTabAccess();
			int inSymTab = found($2, currentScope);

			if(inSymTab == 0){
				addItem($2, "Var", $1, 0, currentScope);
			}
			else{
				printf("SEMANTIC ERROR: Var %s is already in the symbol table", $2);
			}
	
			showSymTable();
    			sprintf(id1, "%s", $2);
    			int numid = getID(id1, currentScope);
    			emitConstantIntAssignment ($2, numid);							
			$$ = AST_Type("Type", $1, $2);
			//printf("-----------> %s", $$->LHS);
		}
        
		| TYPE ID LBRACK NUMBER RBRACK SEMICOLON {
            		char id1[50];
            		printf("\n RECOGNIZED RULE: Array declaration %s\n", $2);
            		symTabAccess();
            		int inSymTab = found($2, currentScope);
    
            		if(inSymTab == 0){
                		addItem($2, "Array", $1, $4, currentScope);
            		} 
            		else{
                		printf("SEMANTIC ERROR: Array %s is already in the symbol table", $2);
            		}
            
            		showSymTable();
            		sprintf(id1, "%s", $2);
            		int numid = getID(id1, currentScope);
            		emitConstantIntAssignment($2, numid);
            		$$ = AST_Type("Type", $1, $2);
        	}

        	| TYPE ID LBRACK ID RBRACK SEMICOLON {
            		char id1[50];
            		printf("\n RECOGNIZED RULE: Array declaration %s\n", $2);
            		symTabAccess();
            		int inSymTab = found($2, currentScope);
    
            		if(inSymTab == 0){
                		addItem($2, "Array", $1, $4, currentScope);
            		} 
            		else{
                		printf("SEMANTIC ERROR: Array %s is already in the symbol table", $2);
            		}
            
            		showSymTable();
            		sprintf(id1, "%s", $2);
            		int numid = getID(id1, currentScope);
            		emitConstantIntAssignment($2, numid);
            		$$ = AST_Type("Type", $1, $2);
        	}

        	| TYPE ID LBRACK RBRACK SEMICOLON {
            		char id1[50];
            		printf("\n RECOGNIZED RULE: Array declaration %s\n", $2);
            		symTabAccess();
            		int inSymTab = found($2, currentScope);
    
            		if(inSymTab == 0){
                		addItem($2, "Array", $1, 0, currentScope);
            		} 
            		else{
                		printf("SEMANTIC ERROR: Array %s is already in the symbol table", $2);
            		}
            
            		showSymTable();
            		sprintf(id1, "%s", $2);
            		int numid = getID(id1, currentScope);
            		emitConstantIntAssignment($2, numid);
            		$$ = AST_Type("Type", $1, $2);
        	}

    		| TYPE ID COMMA VarDecl { 
    			char id1[50];
    			printf("\n RECOGNIZED RULE: Variable declaration %s\n", $2);
			symTabAccess();
			int inSymTab = found($2, currentScope);
			
			if(inSymTab == 0){
				addItem($2, "Var", $1, 0, currentScope);
			}
			else{
				printf("SEMANTIC ERROR: Var %s is already in the symbol table", $2);
			}
			
			showSymTable();
    			sprintf(id1, "%s", $2);
    			int numid = getID(id1, currentScope);
    			emitConstantIntAssignment ($2, numid);							
			$$ = AST_Type("Type",$1,$2);
			//printf("-----------> %s", $$->LHS);
		}
;


FuncDecl:	TYPE ID LPAREN VarDecl RPAREN LBRACE DeclList RBRACE {
			char id1[50];
                	printf("\n RECOGNIZED RULE: Function declaration %s\n", $2);
                	symTabAccess();
                	int inSymTab = found($2, currentScope);

                	if(inSymTab == 0){
                    		addItem($2, "Func", $1, 0, currentScope);
                	} 
                	else{
                    		printf("SEMANTIC ERROR: Func %s is already in the symbol table", $2);
                	}

                	showSymTable();
                	sprintf(id1, "%s", $2);
                	int numid = getID(id1, currentScope);
                	emitConstantIntAssignment($2, numid);
                	$$ = AST_Type("Type", $1, $2);
                	//printf("-----------> %s", $$->LHS);
                	emitFunctionIR($2, $4);
                	emitMIPSFunctionBody($2, $7, $4); 
            	}
;


StmtList:	{}
		| Stmt StmtList
;


Stmt:	SEMICOLON {}
	
	| Expr SEMICOLON {
        	$$ = $1;
    	}

	| WriteStmt SEMICOLON {
		$$ = $1;
	}

        | WhileStmt {
        	$$ = $1;
        }

	| IfStmt {
		$$ = $1;
	}

        | FuncStmt {
		$$ = $1;
        }
;


IfStmt: IF LPAREN Expr RPAREN LBRACE StmtList RBRACE {
            $$ = AST_If("IF", "", $3);
            $$->left = $6;
            $$->right = NULL;
        }
        
        | IF LPAREN Expr RPAREN LBRACE StmtList ElseStmt RBRACE {
            $$ = AST_IfElse("IF_ELSE", $3, $6, $7);
        }


WhileStmt:	WHILE LPAREN Expr RPAREN LBRACE StmtList RBRACE {
                	$$ = AST_While("WHILE", NULL, $3);
                	$$->left = $6;
                	$$->right = NULL;
            	}
            
            	| WHILE LPAREN Expr RPAREN LBRACE StmtList IfStmt RBRACE {
                	$$ = AST_WhileElse("WHILE_IF", $3, $6, $7);
            	}

            	| WHILE LPAREN Expr RPAREN LBRACE StmtList ElseStmt RBRACE {
                	$$ = AST_WhileElse("WHILE_ELSE", $3, $6, $7);
            	}


ElseStmt:	ELSE LBRACE StmtList RBRACE {
                	$$ = $3;
            	}


FuncStmt:	ID LPAREN RPAREN {
                	printf("\n RECOGNIZED RULE: Function call %s\n", $1);
            	}

		| ID LPAREN ID RPAREN {
                	printf("\n RECOGNIZED RULE: Function call %s with parameter %s\n", $1, $2);
            	}

            	| ID LPAREN NUMBER RPAREN {
                	printf("\n RECOGNIZED RULE: Function call %s with parameter %s\n", $1, $2);
            	}


Expr:	Expr LOGOP Expr {}

	| LPAREN Expr RPAREN {}

	| NOT Expr {}

	| ID EQ Rec { 
		printf("\n RECOGNIZED RULE: Simplest expression\n"); 
           	char id1[50], id2[50];
            	sprintf(id1, "%s", $1);
            	sprintf(id2, "%d", result);
            	int numid = getID(id1, currentScope);
            	emitIR(id1, id2, numid);
            	emitMIPSConstantIntAssignment(id1, id2, numid);		
            	result = 0;		
        }

        | ID EQ ID { 
            	printf("\n RECOGNIZED RULE: Assignment statement\n"); 
            	$$ = AST_assignment("=", $1, $3);
            	
		if(found($1, currentScope) != 1){
                	printf("SEMANTIC ERROR: Variable %s has NOT been declared in scope %s \n", $1, currentScope);
                	semanticCheckPassed = 0;
            	}

            	if(found($3, currentScope) != 1){
                	printf("SEMANTIC ERROR: Variable %s has NOT been declared in scope %s \n", $1, currentScope);
                	semanticCheckPassed = 0;
            	}

            	printf("\nChecking types: \n");
            	int typeMatch = compareTypes ($1, $3, currentScope);
            	
		if(typeMatch == 0){
                	printf("SEMANTIC ERROR: Type mismatch for variables %s and %s \n", $1, $3);
                	semanticCheckPassed = 0;
            	}

            	if(semanticCheckPassed == 1){
                	printf("\n\n>>> AssignStmt Rule is SEMANTICALLY correct and IR code is emitted! <<<\n\n");
                	emitAssignment($1, $3);
                	emitMIPSAssignment($1, $3);
            	}
	}

        | ID EQ ID Array { 
        	printf("\n RECOGNIZED RULE: Array Assignment statement\n"); 
        	$$ = AST_assignment("=", $1, $3);
            
		if(found($1, currentScope) != 1){
                	printf("SEMANTIC ERROR: Variable %s has NOT been declared in scope %s \n", $1, currentScope);
        		semanticCheckPassed = 0;
            	}
            
		if(found($3, currentScope) != 1){
                	printf("SEMANTIC ERROR: Array %s has NOT been declared in scope %s \n", $1, currentScope);
                	semanticCheckPassed = 0;
            	}
            
		printf("\nChecking types: \n");
            	int typeMatch = compareTypes ($1, $3, currentScope);
            	
		if(typeMatch == 0){
                	printf("SEMANTIC ERROR: Type mismatch for variables %s and %s \n", $1, $3);
                	semanticCheckPassed = 0;
            	}
            
		if(semanticCheckPassed == 1) {
                	printf("\n\n>>> AssignStmt Rule is SEMANTICALLY correct and IR code is emitted! <<<\n\n");
                	emitAssignment($1, $3);
                	emitMIPSAssignment($1, $3);
            	}

        }

        | ID EQ NUMBER { 
        	printf("\n RECOGNIZED RULE: ID EQ NUMBER\n"); 
            	char str[50];
            	char id1[50];
            
		if(found($1, currentScope) != 1) {
                	printf("SEMANTIC ERROR: Variable %s has NOT been declared in scope %s \n", $1, currentScope);
                	semanticCheckPassed = 0;
            	}

            	printf("\nChecking types: \n");
            	printf("%s = %s\n", "int", "number");  
            
		if(semanticCheckPassed == 1){
                	printf("\n\nRule is semantically correct!\n\n");
                	sprintf(str, "%d", $3); 
                	sprintf(id1, "%s", $1);	
                	symTabAccess();
                	setValue(id1, $3, currentScope);
                	showSymTable();
                	$$ = AST_assignment("=",$1, str);
                	char id1[50], id2[50];
                	sprintf(id1, "%s", $1);
                	sprintf(id2, "%d", $3);
                	int numid = getID(id1, currentScope);
                	emitIR(id1, id2, numid);
                	emitMIPSConstantIntAssignment(id1, id2, numid);
            	}
        }

        | NUMBER COMPOP Rec {
        	$$ = AST_BinaryExpression($2, "", "");
        	$$->left = AST_Type("NUM", "", "");
        	$$->left->value = $1;
        	$$->right = $3;
        	$$->value = compareValues($1, $2, $3->value);

        	if($$->value){
                	printf("The comparison statement is TRUE!\n");
        	} 
            	else{
                	printf("The comparison statement is FALSE.\n");
            	}
        }

        | ID COMPOP Rec {
        	//symTabAccess();
            	int id_value = getValue($1, currentScope);

            	$$ = AST_BinaryExpression($2, "", "");
            	$$->left = AST_Type("ID", "", "");
            	$$->left->value = id_value;
            	$$->right = $3;
            	$$->value = compareValues(id_value, $2, $3->value);

            	if($$->value){
                	printf("The comparison statement is TRUE!\n");
            	} 
            	else{
                	printf("The comparison statement is FALSE.\n");
            	}
	}
;


WriteStmt:	WRITE ID { 
        		printf("\n RECOGNIZED RULE: WRITE statement\n");
        		$$ = AST_Write("write",$2,"");
        		char id1[50];
        		sprintf(id1, "%s", $2);
        		int numid = getID(id1, currentScope);

        		if(found($2, currentScope) != 1){
                		printf("SEMANTIC ERROR: Variable %s has NOT been declared in scope %s \n", $2, currentScope);
                		semanticCheckPassed = 0;
        		}
            
			if(semanticCheckPassed == 1) {
                		printf("\n\nRule is semantically correct!\n\n");
                		emitWriteId($2);
                		emitMIPSWriteId($2,numid);
            		}
		}
;


Rec:	NUMBER { 
    		//printf("\n RECOGNIZED RULE: ADD STATEMENT NUM END\n");
    		$$ = AST_Type("NUM", "", "");
    		$$->value = $1;
	}

	| ID {
    		printf("\n RECOGNIZED RULE: ADD STATEMENT ID END \n");
    		symTabAccess();
    		int id_value = getValue($1, currentScope);
    		$$ = AST_Type("ID", "", "");
    		$$->value = id_value;
	}

	| NUMBER MATHOP Rec {
		$$ = AST_BinaryExpression($2, "", "");
    
		if(strcmp($2, "+") == 0){
        		$$->value = $1 + $3->value;
    		} 
		else if(strcmp($2, "-") == 0){
        		$$->value = $1 - $3->value;
		} 
		else if(strcmp($2, "*") == 0){
        		$$->value = $1 * $3->value;
    		} 
		else if(strcmp($2, "/") == 0){
        		$$->value = $1 / $3->value;
    		}
	}

	| ID MATHOP Rec {
    		symTabAccess();
    		int id_value = getValue($1, currentScope);
    		$$ = AST_BinaryExpression($2, "", "");
    
		if(strcmp($2, "+") == 0){
        		$$->value = id_value + $3->value;
    		} 
		else if(strcmp($2, "-") == 0){
        		$$->value = id_value - $3->value;
    		} 
		else if(strcmp($2, "*") == 0){
        		$$->value = id_value * $3->value;
    		} 
		else if(strcmp($2, "/") == 0){
        		$$->value = id_value / $3->value;
    		}
	}

	| LOGOP {}
;


FuncBody:   Decl {}


Array:	LBRACK RBRACK {
        	int size = 0;
        	emitMIPSArrayDeclaration($$, size, NULL);
        	$$ = $1; 
	}

        | LBRACK NUMBER RBRACK {
        	int arraySizeAttr = $2;
        	int size = 0; 
        	emitMIPSArrayDeclaration($$, size, NULL);
        	$$ = $1;
        }

        | LBRACK ID RBRACK {
        	int arraySizeAttr = getValue($2, currentScope);
        	int size = 0; 
        	emitMIPSArrayDeclaration($$, size, NULL);
        	$$ = $1; 
        }
;

%%


int main(int argc, char**argv){

	clock_t start, end;
	double cpu_time_used;

	start = clock();

	initIRcodeFile();
	initAssemblyFile();

	printf("\n\n##### COMPILER STARTED #####\n\n");
	
	if(argc > 1){
		if(!(yyin = fopen(argv[1], "r"))){
			perror(argv[1]);
		    	return(1);
	    	} 
	}

	yyparse();

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Program took %f seconds to execute\n", cpu_time_used);

	emitEndOfAssemblyCode();
	emitEndOfAssemblyCodeNEW();

	return 0;
}

void yyerror(const char* s){
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
