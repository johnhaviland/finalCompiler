// Header file that creates symbol table
#include <string.h>
#include <stdio.h>

struct Entry{
	int itemID;
	char itemName[50];
	char itemKind[8];
	char itemType[8];
	int arrayLength;
	int itemVal;
	char scope[50];
};

struct Entry symTabItems[100];
int symTabIndex = 0;
int SYMTAB_SIZE = 20;

void symTabAccess(void){
	printf(">>>> SYMBOL TABLE ACCESSED <<<<\n");
}

void addItem(char itemName[50], char itemKind[8], char itemType[8], int arrayLength, char scope[50]){
		symTabItems[symTabIndex].itemID = symTabIndex;
		strcpy(symTabItems[symTabIndex].itemName, itemName);
		strcpy(symTabItems[symTabIndex].itemKind, itemKind);
		strcpy(symTabItems[symTabIndex].itemType, itemType);
		symTabItems[symTabIndex].itemVal = 0;
		symTabItems[symTabIndex].arrayLength = arrayLength;
		strcpy(symTabItems[symTabIndex].scope, scope);
		symTabIndex++;
}

int setValue(char itemName[50], int itemVal, char scope[50]){
	for (int i = 0; i < SYMTAB_SIZE; i++){
		int str1 = strcmp(symTabItems[i].itemName, itemName); 
		int str2 = strcmp(symTabItems[i].scope,scope); 
		
		if (str1 == 0 && str2 == 0){
			symTabItems[i].itemVal = itemVal;
			return 1;
		}
	}
		
	return 0;
}

void showSymTable(){
	printf("itemID    itemName    itemVal    itemKind     itemType     arrayLength       itemScope\n");
	printf("=======================================================================================\n");
	
	for (int i = 0; i < symTabIndex; i++){
		printf("%5d %8s  %10d  %9s %10s %12d %15s %s \n",symTabItems[i].itemID, symTabItems[i].itemName, symTabItems[i].itemVal, symTabItems[i].itemKind, symTabItems[i].itemType, symTabItems[i].arrayLength, symTabItems[i].scope, "G");
	}
	
	printf("=======================================================================================\n");
}

int found(char itemName[50], char scope[50]){
	for(int i = 0; i < SYMTAB_SIZE; i++){
		int str1 = strcmp(symTabItems[i].itemName, itemName); 
		int str2 = strcmp(symTabItems[i].scope,scope); 
		
		if( str1 == 0 && str2 == 0){
			return 1;
		} 
	}
	
	return 0;
}


int getValue(char itemName[50],char scope[50]){
	int returnNum;
	
	for(int i = 0; i < SYMTAB_SIZE; i++){
		int str1 = strcmp(symTabItems[i].itemName, itemName); 
		int str2 = strcmp(symTabItems[i].scope,scope); 

		if(str1 == 0 && str2 == 0){
			returnNum = symTabItems[i].itemVal;
			return symTabItems[i].itemVal;
		}
	}

	return 0;
}

void printVal(){
	for(int i = 0; i < 10; i++) {
		printf("%7d\n", symTabItems[i].itemVal);
	}
}

int getID(char itemName[50],char scope[50]){
	int returnID;

	for(int i = 0; i < SYMTAB_SIZE; i++){
		int str1 = strcmp(symTabItems[i].itemName, itemName); 
		int str2 = strcmp(symTabItems[i].scope,scope); 
		
		if( str1 == 0 && str2 == 0){
			returnID = (int)(symTabItems[i].itemID)+0;
			return returnID;
		}
	}
	
	return 0;
}

const char* getVariableType(char itemName[50], char scope[50]){
	for(int i=0; i<SYMTAB_SIZE; i++){
		int str1 = strcmp(symTabItems[i].itemName, itemName); 
		int str2 = strcmp(symTabItems[i].scope,scope); 

		if( str1 == 0 && str2 == 0){
			return symTabItems[i].itemType;
		}
	}
	
	return NULL;
}

int compareTypes(char itemName1[50], char itemName2[50],char scope[50]){
	const char* idType1 = getVariableType(itemName1, scope);
	const char* idType2 = getVariableType(itemName2, scope);
	
	printf("%s = %s\n", idType1, idType2);
	
	int typeMatch = strcmp(idType1, idType2);
	
	if(typeMatch == 0){
		return 1; 
	}
		
	else return 0;
}

void getArrayValuesFromTable(char itemName[50], char scope[50], int values[]) {
    for (int i = 0; i < SYMTAB_SIZE; i++) {
        int str1 = strcmp(symTabItems[i].itemName, itemName);
        int str2 = strcmp(symTabItems[i].scope, scope);

        if (str1 == 0 && str2 == 0) {
            if (strcmp(symTabItems[i].itemKind, "Array") == 0) {
                for (int j = 0; j < symTabItems[i].arrayLength; j++) {
                    values[j] = symTabItems[i].itemVal + j;
                }
                return;
            } else {
                printf("ERROR: %s is not an array in scope %s\n", itemName, scope);
                return;
            }
        }
    }

    printf("ERROR: Array %s not found in scope %s\n", itemName, scope);
}
