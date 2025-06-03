#ifndef RIDE_2 
#define RIDE_2   
#include "ride1.h"
#include "global.h"

word1* codingFirstWord(ptInstruction ptIC,int * ICF); 
int getReg(char* op); 
word2* codingSecondWord(int funct,char* op1, char* op2,int * ICF); 
void addFirstWord(word1* word,FILE* fileObj,int * ICF); 
void addSecondWord(word2* word,FILE* fileObj,int * ICF); 
void addAditionWord(additionWord* word,FILE* fileObj,int * ICF); 
void printbin(int x); 
int getNumber(char* op1); 
char* checkErrorLabel(char* op,ptNodeSymbol head); 
int getBasic(int adress); 
int getHist(int adress); 
int addExternal(ptExternal* head,char* name,int BASE); 
void codingAditionWord(char* op,FILE* fileobj,ptNodeSymbol head,int * ICF,ptExternal* headExternal); 
void addDataToFile(char* ptCommand,FILE* fileOBJ,int* ICF); 
void addStringToFile(char* ptCommand,FILE* fileOBJ,int* ICF); 
void createFiles(ptNodeSymbol head,const char* fileName,ptExternal headExternal); 

#endif