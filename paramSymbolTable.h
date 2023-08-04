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

struct Entry paramTabItems[100];
int paramTabIndex = 0;
int PARAMTAB_SIZE = 20;

void paramTabAccess(void){
	printf(">>>> SYMBOL TABLE ACCESSED <<<<\n");
}

void paramAddItem(char itemName[50], char itemKind[8], char itemType[8], int arrayLength, char scope[50]){
		paramTabItems[paramTabIndex].itemID = paramTabIndex;
		strcpy(paramTabItems[paramTabIndex].itemName, itemName);
		strcpy(paramTabItems[paramTabIndex].itemKind, itemKind);
		strcpy(paramTabItems[paramTabIndex].itemType, itemType);
		paramTabItems[paramTabIndex].itemVal = 0;
		paramTabItems[paramTabIndex].arrayLength = arrayLength;
		strcpy(paramTabItems[paramTabIndex].scope, scope);
		paramTabIndex++;
}

int setParamValue(char itemName[50], int itemVal, char scope[50]){
	for (int i = 0; i < PARAMTAB_SIZE; i++){
		int str1 = strcmp(paramTabItems[i].itemName, itemName); 
		int str2 = strcmp(paramTabItems[i].scope,scope); 
		
		if (str1 == 0 && str2 == 0){
			paramTabItems[i].itemVal = itemVal;
			return 1;
		}
	}
		
	return 0;
}

void showParamTable(){
	printf("itemID    itemName    itemKind    itemType     ArrayLength    itemSCope\n");
	printf("=====================================================================\n");
	
	for (int i = 0; i < paramTabIndex; i++){
		printf("%5d %15s  %7d  %7s %7s %6d %15s \n",paramTabItems[i].itemID, paramTabItems[i].itemName, paramTabItems[i].itemVal, paramTabItems[i].itemKind, paramTabItems[i].itemType, paramTabItems[i].arrayLength, paramTabItems[i].scope);
	}
	
	printf("=====================================================================\n");
}

int paramFound(char itemName[50], char scope[50]){
	for(int i = 0; i < PARAMTAB_SIZE; i++){
		int str1 = strcmp(paramTabItems[i].itemName, itemName); 
		int str2 = strcmp(paramTabItems[i].scope,scope); 
		
		if( str1 == 0 && str2 == 0){
			return 1;
		} 
	}
	
	return 0;
}


int getParamValue(char itemName[50],char scope[50]){
	int returnNum;
	
	for(int i = 0; i < PARAMTAB_SIZE; i++){
		int str1 = strcmp(paramTabItems[i].itemName, itemName); 
		int str2 = strcmp(paramTabItems[i].scope,scope); 

		if(str1 == 0 && str2 == 0){
			returnNum = paramTabItems[i].itemVal;
			return paramTabItems[i].itemVal;
		}
	}

	return 0;
}

void printParamVal(){
	for(int i = 0; i < 4; i++) {
		printf("%7d\n", paramTabItems[i].itemVal);
	}
}

int getParamID(char itemName[50],char scope[50]){
	int returnID;

	for(int i = 0; i < PARAMTAB_SIZE; i++){
		int str1 = strcmp(paramTabItems[i].itemName, itemName); 
		int str2 = strcmp(paramTabItems[i].scope,scope); 
		
		if( str1 == 0 && str2 == 0){
			returnID = (int)(paramTabItems[i].itemID)+0;
			return returnID;
		}
	}
	
	return 0;
}

const char* getParameterType(char itemName[50], char scope[50]){
	for(int i=0; i<PARAMTAB_SIZE; i++){
		int str1 = strcmp(paramTabItems[i].itemName, itemName); 
		int str2 = strcmp(paramTabItems[i].scope,scope); 

		if( str1 == 0 && str2 == 0){
			return paramTabItems[i].itemType;
		}
	}
	
	return NULL;
}

int compareParamTypes(char itemName1[50], char itemName2[50],char scope[50]){
	const char* idType1 = getParameterType(itemName1, scope);
	const char* idType2 = getParameterType(itemName2, scope);
	
	printf("%s = %s\n", idType1, idType2);
	
	int typeMatch = strcmp(idType1, idType2);
	
	if(typeMatch == 0){
		return 1; 
	}
		
	else return 0;
}