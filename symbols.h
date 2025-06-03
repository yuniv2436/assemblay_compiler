#ifndef SYMBOLS_H 
#define SYMBOLS_H   

#include "global.h"

void printSymbolList(ptNodeSymbol head); 
int addNext(ptNodeSymbol* head,char* labelName, int adress, short type); 
int checkExist(ptNodeSymbol head, char *name); 
ptNodeSymbol GetIfExist(ptNodeSymbol head, char *name); 
int isSYEmpty(ptNodeSymbol head); 
ptNodeSymbol getNextSY(ptNodeSymbol* head); 
void DeleteSymbols(ptNodeSymbol* head); 

#endif