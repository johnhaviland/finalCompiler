// Header file to create IR code
#include <stdio.h>

FILE * IRcode;        // File pointer for IRcode.ir
int numbers[10];      // global array variable for addNumbers() & sumOfNumbers() functions 

// Function that emits IR code header to IRcode.ir
void initIRcodeFile(){
    IRcode = fopen("IRcode.ir", "w");
    
    fprintf(IRcode, "\n\n#### IR Code ####\n\n");
    
    fclose(IRcode);
}

// Function that emits IR code for a binary operation to IRcode.ir
void emitBinaryOperation(char * op[1], const char * id1, const char * id2){
    IRcode = fopen("IRcode.ir", "a");
    
    fprintf(IRcode, "T1 = %s %s %s", id1, op, id2);
    
    fclose(IRcode);
}

// Function that emits IR code for variable assignment to IRcode.ir
void emitAssignment(char * id1, char * id2){
    IRcode = fopen("IRcode.ir", "a");

    fprintf(IRcode, "T0 = %s\n", id1);
    fprintf(IRcode, "T1 = %s\n", id2);
    fprintf(IRcode, "T1 = T0\n");
    
    fclose(IRcode);
}

// Function that emits IR code for constant int assignment to IRcode.ir
void emitConstantIntAssignment(char * id1[50], char * id2[50]){
    IRcode = fopen("IRcode.ir", "a");
    
    fprintf(IRcode, "T%d = %s\n", id2, id1);
    
    fclose(IRcode);
}

// Function that emits generic IR code statement to IRcode.ir
void emitIR(char * id1[50], char * id2[50], char * currentScope[50]){
    IRcode = fopen("IRcode.ir", "a");
    
    fprintf(IRcode, "T%d = %s\n", currentScope, id2);
    
    fclose(IRcode);
}

// Function that emits IR code for 'write' statements to IRcode.ir
void emitWriteId(char * id){
    IRcode = fopen("IRcode.ir", "a");

    fprintf (IRcode, "output %s\n", "T2");
    
    fclose(IRcode);
}

// Function that emits IR code for function calls to IRcode.ir
void emitFunctionIR(char * functionName, char * parameters){
    IRcode = fopen("IRcode.ir", "a");
    
    fprintf(IRcode, "\n\n#### Function: %s ####\n\n", functionName);
    fprintf(IRcode, "param %s\n", parameters);
    fprintf(IRcode, "call %s\n", functionName);
    fprintf(IRcode, "T0 = returnVal\n");
    
    fclose(IRcode);
}

// Function that adds numbers to numbers[] array
void addNumbers(int num){
    int index = 0;
    numbers[index] = num;
    index++;
}

// Function that finds the sum of the numbers in the numbers[] array
int sumOfNumbers(){
    int sum = 0;
    for (int i = 0; i < 50; i++){
        sum += numbers[i];
        numbers[i] = 0;
    }
    
    return sum;
}
