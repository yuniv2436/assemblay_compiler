#ifndef MACRO_H 
#define MACRO_H  

#include "global.h"

void printMacroList(ptMacro head); 
void addMacro(ptMacro* head,ptMacro newMacro); 
int searchMacro(ptMacro head,char* macroName); 
void addLinesToFile(ptMacro head,char* macroName,FILE* file); 
int isMAEmpty(ptMacro head); 
void DeleteMacros(ptMacro* head); 

#endif