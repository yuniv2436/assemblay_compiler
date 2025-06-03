#include "global.h"


char *registers[]={
    "r0", 
    "r1", 
    "r3", 
    "r4", 
    "r5",
    "r6", 
    "r7", 
    "r8", 
    "r9", 
    "r10", 
    "r11",
    "r12", 
    "r13", 
    "r14", 
    "r15",  
    "undefind"
}; 

char * operations[]={
    "mov", 
    "cmp", 
    "add", 
    "sub", 
    "lea",
    "clr", 
    "not", 
    "inc", 
    "dec", 
    "jmp", 
    "bne",
    "jsr", 
    "red", 
    "prn", 
    "rts", 
    "stop", 
    "undefind" 
};

char * directions[]={
    ".entry", 
    ".string", 
    ".extern", 
    ".data"
};  

instruction arrIC[17]={  /*0-immediate,1-direct,2-index,3-register direct*/
    {"mov",0,0,15/*1111*/,14/*1110*/},
    {"cmp",1,0,15/*1111*/,15/*1111*/}, 
    {"add",2,10,15/*1111*/,14/*0111*/},  
    {"sub",2,11,15/*1111*/,14/*0111*/},  
    {"lea",4,0,6/*1111*/,14/*1110*/}, 
    {"clr",5,10,0/*1111*/,14/*0111*/}, 
    {"not",5,11,0/*1111*/,14/*0111*/},
    {"inc",5,12,0/*1111*/,14/*0111*/},   
    {"dec",5,13,0/*1111*/,14/*0111*/}, 
    {"jmp",9,10,0/*1111*/,6/*0011*/}, 
    {"bne",9,11,0/*1111*/,6/*0111*/}, 
    {"jsr",9,12,0/*1111*/,6/*0111*/}, 
    {"red",12,0,0/*1111*/,14/*0111*/}, 
    {"prn",13,0,0/*1111*/,15/*0111*/}, 
    {"rts",14,0,0/*1111*/,0/*0111*/}, 
    {"stop",15,11,0/*1111*/,0/*0111*/},
    {"undefind",0,0,0/*0000*/,0/*0000*/}
};   

ptInstruction ptArrIC[17]={ 
    &arrIC[0],
    &arrIC[1],
    &arrIC[2], 
    &arrIC[3],
    &arrIC[4],
    &arrIC[5],
    &arrIC[6],
    &arrIC[7],
    &arrIC[8],
    &arrIC[9],
    &arrIC[10],
    &arrIC[11],
    &arrIC[12],
    &arrIC[13],
    &arrIC[14],
    &arrIC[15], 
    &arrIC[16], 
}; 
