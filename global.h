#ifndef GLOBAL_H 
#define GLOBAL_H  
#include <stdio.h>  
#include <stdlib.h>  
#include <ctype.h>
#include <string.h> 
#include <math.h>  


#define SIZELINE 81 
#define SIZELABEL 31   

typedef struct ABCD{  
   unsigned int data:20;
} ABCD;

typedef struct firstWord{   
   unsigned int opcode:16;
   unsigned int ARE:3;
   unsigned int msb:1;

} firstWord;

typedef union word1 {
	firstWord *word;
	ABCD *split;
}word1;
  
typedef struct secondWord{  
    unsigned int adrDas:2; 
    unsigned int dasRegister:4; 
    unsigned int adrSrc:2; 
    unsigned int srcRegister:4; 
    unsigned int funct:4; 
    unsigned int ARE:3; 
    unsigned int msb:1;
} secondWord; 

typedef union word2{
	secondWord *word;
	ABCD *split;
}word2;

typedef struct addition{   
    unsigned int data:16; 
    unsigned int ARE:3;
    unsigned int msb:1;
}addition;  

typedef union additionWord{
	addition *word;
	ABCD *split;
}additionWord;

typedef enum symbolAtribute { 
    Data,Empty,Entry,External,Code
} symbolAtribute;

typedef struct nodeSymbol{  
    char *name; 
    int adress;/*in decimal*/ 
    symbolAtribute type1;/*0,1,2 or 3*/ 
    symbolAtribute type2;/*0,1,2 or 3*/
    struct nodeSymbol* next;} nodeSymbol;  

typedef nodeSymbol* ptNodeSymbol; 

typedef struct macro{ 
    char name[SIZELABEL];
    char lines[SIZELINE*6];
    struct macro* next;
} macro;  

typedef macro* ptMacro;

typedef enum methodOp { 
    Immediate=0,Direct=1,Index=2,Register=3
} methodOp;
 
typedef struct instruction{  
    char name[10];
    int opcode; 
    int funct; /*if the func=0 ->there isnt funct*/   
    /*every bit represent the mwthos the operand can use*/
    unsigned int src:4;  /*if the all bit are off so there isnt src oprand*/   
    unsigned int das:4; /*if the all bit are off so there isnt das oprand*/ 

} instruction;  

typedef instruction* ptInstruction; 

typedef struct external{  
    char* name; 
    int adressBase;  
    struct external* next;
}external; 

typedef struct external* ptExternal;


extern char *registers[];
extern char * operations[];
extern char * directions[];
extern instruction arrIC[17];  /*0-immediate,1-direct,2-index,3-register direct*/
extern ptInstruction ptArrIC[17];


#endif
