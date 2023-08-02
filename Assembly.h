// Header file to create Assembly code
#include <stdio.h>

void initAssemblyFile(){
    FILE * MIPScode;
    MIPScode = fopen("MIPScode.asm", "w");
    printf("opened MIPScode.asm\n");
    fprintf(MIPScode, ".text\n");
    fprintf(MIPScode, "main:\n");
    fprintf(MIPScode, "# ==================================\n\n");
    printf("header printed\n");
}

void emitMIPSAssignment(char * id1, char * id2){
    FILE * MIPScode;
    MIPScode = fopen("MIPScode.asm", "a");

    fprintf(MIPScode, "li $t1,%s\n", id1);
    fprintf(MIPScode, "li $t2,%s\n", id2);
    fprintf(MIPScode, "li $t2,$t1\n\n");
}

void emitMIPSConstantIntAssignment (char * id1, char * id2, int currentScope){
    FILE * MIPScode;
    MIPScode = fopen("MIPScode.asm", "a");
    fprintf(MIPScode, "li $t%d,%s\n\n", currentScope, id2);
}

void emitMIPSFunctionDeclaration(char *funcName, char *returnType) {
    FILE *MIPScode;
    MIPScode = fopen("MIPScode.asm", "a");

    fprintf(MIPScode, "%s:\n", funcName);
    fprintf(MIPScode, "sw $ra, 0($sp)\n");
    fprintf(MIPScode, "addi $sp, $sp, -4\n");
    fprintf(MIPScode, "lw $ra, 4($sp)\n");
    fprintf(MIPScode, "addi $sp, $sp, 4\n");
    fprintf(MIPScode, "jr $ra\n");

    fclose(MIPScode);
}

void emitMIPSWriteId(char * id, int count){
    FILE * MIPScode;
    MIPScode = fopen("MIPScode.asm", "a");
    fprintf(MIPScode, "move $a0,$t%d\n", count);
    fprintf(MIPScode, "li $v0,1\n");
    fprintf(MIPScode, "syscall\n");

    fprintf(MIPScode, "li $a0, 10\nli $v0, 11\nsyscall\n\n");
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

    printf("end of assembly printed to file\n");

    fclose(MIPScode);
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
    
