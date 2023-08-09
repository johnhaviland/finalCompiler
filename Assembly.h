// Header file to create Assembly code
#include <stdio.h>

void initAssemblyFile(){
    FILE * MIPScode;
    MIPScode = fopen("MIPScode.asm", "w");

    printf("opened MIPScode.asm\n");
    fprintf(MIPScode, ".text\n");
    fprintf(MIPScode, ".globl main\n");
    fprintf(MIPScode, "main: \n");
    fprintf(MIPScode, "# ==================================\n\n");

    fclose(MIPScode);

    printf("header printed\n");
}

void emitMIPSAssignment(char * id1, char * id2){
    FILE * MIPScode;
    MIPScode = fopen("MIPScode.asm", "a");

    fprintf(MIPScode, "li $t1,%s\n", id1);
    fprintf(MIPScode, "li $t2,%s\n", id2);
    fprintf(MIPScode, "li $t2,$t1\n\n");

    fclose(MIPScode);

    printf("emitMIPSAssignment() used\n");
}

void emitMIPSConstantIntAssignment (char * id1, char * id2, int currentScope){
    FILE * MIPScode;
    MIPScode = fopen("MIPScode.asm", "a");

    fprintf(MIPScode, "li $t%d,%s\n\n", currentScope, id2);

    fclose(MIPScode);

    printf("emitMIPSConstantIntAssignment() used\n");
}

void emitMIPSFunctionBody(char* funcName, struct AST * funcBody, struct AST * funcParams) {
    FILE* MIPScode;
    MIPScode = fopen("MIPScode.asm", "a");

    fprintf(MIPScode, "jal %s\n\n", funcName);
    fprintf(MIPScode, "%s:\n\t", funcName);
    emitMIPSFunctionBodyAST(MIPScode, funcBody);
    fprintf(MIPScode, "jr $ra\n");

    fclose(MIPScode);

    printf("emitMIPSFunctionBody() used\n");
}

void emitMIPSFunctionBodyAST(FILE * MIPScode, struct AST * ast) {
    if (ast == NULL) {
        return;
    }

    if (strcmp(ast->nodeType, "=") == 0){
        char* lhs = ast->LHS;
        char* rhs = ast->RHS;
        fprintf(MIPScode, "lw $t0, %s\n\t", rhs);
        fprintf(MIPScode, "sw $t0, %s\n\t", lhs);
    } 
    else if (strcmp(ast->nodeType, "write") == 0){
        char* id = ast->LHS;
        fprintf(MIPScode, "lw $a0, %s\n\t", id);
        fprintf(MIPScode, "li $v0, 1\n\t");
        fprintf(MIPScode, "syscall\n\t");
    }

    if (strcmp(ast->nodeType, "Param") == 0) {
        char* paramName = ast->LHS;
        fprintf(MIPScode, "lw $t0, %d($fp)\n\t", -4);
        fprintf(MIPScode, "sw $t0, %s\n\t", paramName);
    }

    emitMIPSFunctionBodyAST(MIPScode, ast->left);
    emitMIPSFunctionBodyAST(MIPScode, ast->right);

    fclose(MIPScode);

    printf("emitMIPSFunctionBodyAST() used\n");
}


void emitMIPSWriteId(char * id, int count){
    FILE * MIPScode;
    MIPScode = fopen("MIPScode.asm", "a");
    fprintf(MIPScode, "move $a0,$t%d\n", count);
    fprintf(MIPScode, "li $v0,1\n");
    fprintf(MIPScode, "syscall\n");

    fprintf(MIPScode, "li $a0, 10\nli $v0, 11\nsyscall\n\n");

    fclose(MIPScode);

    printf("emitMIPSWriteId() used\n");
}

void emitMIPSConstantIntArrayAssignment(char * id, int size, int values[]) {
    FILE * MIPScode;
    MIPScode = fopen("MIPScode.asm", "a");

    for (int i = 0; i < size; i++) {
        fprintf(MIPScode, "li $t0, %d\n", values[i]);
        fprintf(MIPScode, "sw $t0, %s(%d)\n", id, i * 4);
    }

    fclose(MIPScode);

    printf("emitMIPSConstantIntArrayAssignment() used\n");
}

void emitMIPSArrayDeclaration(char * id, int size, int values[]) {
    FILE * MIPScode;
    MIPScode = fopen("MIPScode.asm", "a");

    fprintf(MIPScode, ".data\n");
    fprintf(MIPScode, "%s: .space %d\n", id, size * 4);

    emitMIPSConstantIntArrayAssignment(id, size, values);

    fprintf(MIPScode, ".text\n");

    fclose(MIPScode);

    printf("emitMIPSArrayDeclaration() used\n");
}

void emitEndOfAssemblyCode(){
    FILE * MIPScode;
    MIPScode = fopen("MIPScode.asm", "a");
    printf("end of assembly started\n");
    fprintf(MIPScode, "\n");
    fprintf(MIPScode, "li $v0,10\n\n\n");
    fprintf(MIPScode, "\n# ==================================\n\n");
    fprintf(MIPScode, "li $v0,10\n\n\n");
    fprintf(MIPScode, "syscall\n");
    fprintf(MIPScode, ".end main\n");

    fclose(MIPScode);

    printf("emitEndOfAssemblyCode() used\n");
}

void emitEndOfAssemblyCodeNEW(){
    FILE * MIPScode;
    MIPScode = fopen("MIPScode.asm", "a");
    printf("end of assembly started\n");
    printf("\n");
    printf("li $v0,10\n\n\n");
    printf("\n# ==================================\n\n");
    printf("li $v0,10\n\n\n");
    printf("syscall\n");
    printf(".end main\n");

    printf("end of assembly printed to file\n");

    fclose(MIPScode);
}
    
