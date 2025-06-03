#ifndef RIDE1_H 
#define RIDE1_H 

#include "symbols.h"
#include "global.h"
#include <utils.h>

int checkIfLabel(char* word); 
char* parseLabel(char* word); 
char * getNextWord(char* ptWord); 
char* parseString(int * DC,char* string);  
int checkComma(char* ptCommand); 
char* parseNumbers(int* DC,char** ptCommand); 
char* checkExistIc(char* cuWord); 
ptInstruction getIc(char* IC); 
int getNumOp(ptInstruction ptIC); 
char* parseOperands(ptInstruction ptIC,char* ptCommand); 
int checkImidiete(char* op); 
int checkDirectR(char* op); 
int checkIndexR(char* op); 
int getMethod(char* op); 
char* parseIntegrity(int* IC,char* ptCommand,ptInstruction ptIC); 
void printTable(ptNodeSymbol headSymbol); 
void updateTable(int IC,ptNodeSymbol headSymbol);  
int setBit(int n, int k);


#endif

