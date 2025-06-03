#include "global.h"
#include "ride1.h" 
#include "ride2.h" 
#include "macro.h"   
#include "symbols.h"  
#include "utils.h" 

#define EXTRANEOUS_TEXT(ch,lineL)\
    if (ch!='\n' && ch!=EOF && ch!='\0'){\
            printf("line %d -ERROR: %s\n",lineL,"extrenhouse text ");\
            *success=0;\
            continue;\
    }

#define JUMP_ERROR(lineL,err){\
    printf("line %d-ERROR: %s\n",lineL,err);\
    *success=0;\
    continue;\
}

void preProccesor(FILE*,char*); 
void ride1(char*,int*); 
void ride2(const char*,int*,ptNodeSymbol); 
void ride3(const char*,FILE*,int*);

ptNodeSymbol headSymbol=NULL; /*head of the symbol table*/ 
int DC=0,IC=100; /*image */

int main(int argc, char const *argv[]){   
	int success; 
	int i;  
	char fullFileName[SIZELABEL]; 
	char fullFileNameAM[SIZELABEL];
	FILE* preFile=NULL; 

	if(argc<=1){
		printf("No File where typed.\n"); 
		exit(0);
	}
	for(i=1;i<argc;i++){  
		success=1;
		strcpy(fullFileName,argv[i]);  
		strcat(fullFileName,".as\0");  
		strcpy(fullFileNameAM,argv[i]); 
		strcat(fullFileNameAM,".am\0"); 
    
	printf("\n -- File: %s -- \n",fullFileName); 
	preFile=fopen(fullFileName,"r");/*open the asembler file the user enter for reading*/ 

	if(preFile){   
		preProccesor(preFile,fullFileNameAM);  
		ride1(fullFileNameAM,&success);  
		if(!success){
                	printf(" -- File: %s couldn't be created becuse there are error to fix in it. --\n",fullFileName);  
                	DeleteSymbols(&headSymbol);
                	continue;
            	}   
		ride2(argv[i],&success,headSymbol); 
		DeleteSymbols(&headSymbol);  
		if(success){
			printf("the progrem running ok ;)");
            	}
	} 
        else{ 
		printf("Error: The file %s.as dose not exists.\n", argv[i]);
        }  
	}
	return 1;
}   

void preProccesor(FILE* preFile,char* fullFileNameAM){  
	FILE* file=fopen(fullFileNameAM,"w");/*create new file to write into*/  
	ptMacro headMacro=NULL; 
	int indexL=0;/*line number*/
	char line[SIZELINE+2];  
	char* firstWord=NULL; 
	int macroFlag=0;   
	char macroName[SIZELABEL]; 
	char* tempNameM=NULL;
	char copyLine[SIZELINE]; 
	macro* newMacro=NULL;
	char temp[255]; 
	temp[0]='\0';    

	while(fgets(line,SIZELINE+2,preFile)){    
		indexL++;  
		strcpy(copyLine,line);  
		if (strchr(line, '\n') == NULL && !feof(preFile))
			printf("\nline %d (preProccesor) - WARNNING:Line too long to process. Maximum line length should be %d",indexL,SIZELINE);
		firstWord=strtok(copyLine," ");   
		if(!strncmp(firstWord,"endm\n",4)){  
			addMacro(&headMacro,newMacro);  
		macroFlag=0; 
		temp[0]='\0';   
		}
		else{ 
			if(macroFlag){  
				strcat(temp,line); 
				strcpy(newMacro->lines,temp);
			}  
			else if(!strcmp( firstWord,"macro")){  
				tempNameM=strtok(NULL," ");  
				strcpy(macroName,tempNameM); 
				newMacro=(macro*)malloc(8*sizeof(macro)); 
				strcpy(newMacro->name,macroName);  
				newMacro->next=NULL;    
				macroFlag=1;  
			} 
			else if(searchMacro(headMacro,firstWord)){   
				addLinesToFile(headMacro,firstWord,file);  
				}
				else{   
                			fprintf(file,"%s",line);  
				} 
        	}  
	}   
	DeleteMacros(&headMacro); 
	fclose(preFile);  
	fclose(file); 
} 

void ride1(char* fileName,int* success){   
	int lineL=0; /*line number*/
	FILE* file=fopen(fileName,"r"); 
	char command[SIZELINE+2];   
	char* ptCommand=NULL; 
	char copyPtCmd[82];
	char* cuWord=NULL;/*the current word with \0 at the end*/ 
	int labelFlag=0; /*there is a label at this line*/
	char* err;/*err string*/ 
	char labelName[31]; 
	ptNodeSymbol new;
	ptInstruction ptIC;    
    
	while(fgets(command,SIZELINE+2,file)){  
		lineL++; 
		labelFlag=0; 

		if (strchr(command, '\n') == NULL && !feof(file)){
			JUMP_ERROR(lineL,"the line is to longer");
		}       
		ptCommand=skipWhite(command);  
		  
		if(ptCommand[0]=='\n' || ptCommand[0]==EOF){/*check for empty line*/  
			continue; 
        	} 
        	if(ptCommand[0]==';'){ 
            		continue; 
        	}   
        	cuWord=getWord(ptCommand);   
        	if(checkIfLabel(cuWord)){/** if its label **/   
            		cuWord[strlen(cuWord)-1]='\0'; /*cut the : from the label*/
            		err=parseLabel(cuWord);
            	if(!err){ /*if there isn't any error in the label*/ 
                	if(!checkExist(headSymbol,cuWord)){/*check is the label already exisy in the table*/
                    		labelFlag=1; 
                    		strcpy(labelName,cuWord);  
                    		ptCommand=getNextWord(ptCommand);
                    		cuWord=getWord(ptCommand);  
                	} 
                	else/*if the label already exist*/
                    		JUMP_ERROR(lineL,"name of the label already exist");
            	} 
            	else  /*if was an error in the label*/
                	JUMP_ERROR(lineL,err);
        	} 
        	if(!strcmp(cuWord,".string") || !strcmp(cuWord,".data")){/*type=0 , type=1*/  
            		if(labelFlag){  
                	addNext(&headSymbol,labelName,DC,Data);    
                	labelFlag=0;
            		}   
            		ptCommand=getNextWord(ptCommand); 
            		if(!strcmp(cuWord,".string"))
                		err=parseString(&DC,ptCommand);/*check if there is erro in the string*/ 
            		else 
                		err=parseNumbers(&DC,&ptCommand);
            		if(!err){ /*if there is only valid string*/   
                		continue;
            		} 
            		else
                		JUMP_ERROR(lineL,err);
		}    
        	else if(!strcmp(cuWord,".entry")){ /*ride2 will hendle it*/  
			if(labelFlag) 
				printf("line %d - WARNNING:there is label before entry\n",lineL); 
				continue;
		} 
        	else if(!strcmp(cuWord,".extern")){      
            		ptCommand=getNextWord(ptCommand); 
            		cuWord=getWord(ptCommand);  
            		new=GetIfExist(headSymbol,cuWord); 
            		if(new && new->type1!=4){/*if the label already exist and type extern*/  
               			JUMP_ERROR(lineL,err);
            		}  
		else if(!new){ /*if label not exist*/  
                	err=parseLabel(cuWord); 
                	if(!err){ 
				ptCommand=getNextWord(ptCommand);/*get to the begin of the label */ 
            			EXTRANEOUS_TEXT(*ptCommand,lineL); /*if get to not \n or EOF will send error externouse text*/
                		addNext(&headSymbol,cuWord,0,External);  
                	} 
                	else{  
                    		JUMP_ERROR(lineL,err);
                	}  
		} /*if exist with type extern - dont do nothing its already define*/  

			ptCommand=getNextWord(ptCommand);/*get to the begin of the label */ 
            		ptCommand=getNextWord(ptCommand);/*get to \n or to some externhouse*/ 
            		EXTRANEOUS_TEXT(*ptCommand,lineL); /*if get to not \n or EOF will send error externouse text*/
            		continue; 
		}  
		else{ /**its instruction line**/ 
			if(labelFlag){  
                		addNext(&headSymbol,labelName,IC,Code);   
            	}  
            		ptIC=getIc(cuWord);  
            		if(ptIC){/*if the instruction word exist*/  
                		ptCommand=getNextWord(ptCommand); 
                		strcpy(copyPtCmd,ptCommand);/*use the copy because the duncion change the string with strtoken*/
                		err=parseOperands(ptIC,copyPtCmd);  
                		if(!err){  
                    			if(ptIC->das!=0 || ptIC->src!=0){/*if thre is more then 0 operand*/ 
                        		err=parseIntegrity(&IC,ptCommand,ptIC);/*check the integrity of them compare to the instruction word rules */  
                        		if(!err){   
                            			continue; 
                        		} 
                        		else 
                            			JUMP_ERROR(lineL,err); 
                    			}   
					IC++; 
                		} 
			else 
				JUMP_ERROR(lineL,err);
			}  
			else{  
				JUMP_ERROR(lineL,"the instruction word not exist");  
			}
		}
	}    
	updateTable(IC,headSymbol); 

	if(IC+DC>8192){ 
		printf("line %d - the progrem is biger then ram memory you have",lineL);  
		*success=0;
	}
		
}   

void ride2(const char* fileName,int* success,ptNodeSymbol headSymbol){   
	char fileNameO[SIZELABEL]; 
    	char fileNameA[SIZELABEL];  
    	char command[SIZELINE+2];  
    	char* ptCommand=NULL; 
    	char* cuWord=NULL;/*curent word*/  
    	ptNodeSymbol ptSy;  
    	int lineL=0;   
    	int ICF=100;
    	int flagLabel=0; 
    	ptInstruction ptIC; 
   	word1* fWord=NULL; /*first machine word*/
    	word2* sWord=NULL; /*second machine word*/ 
    	char* op1=NULL; /*first Operand*/ 
    	char* op2=NULL; /*second operand - only if exist*/ 
    	char* err=NULL;
    	FILE* fileAM; 
    	FILE* fileOBJ;  
    	ptExternal headExternal=NULL; /*linked list of external struct for the file ex*/
    
	strcpy(fileNameO,fileName); 
    	strcat(fileNameO,".object\0");   
     
    	strcpy(fileNameA,fileName); 
    	strcat(fileNameA,".am\0"); 

    	fileAM=fopen(fileNameA,"r");/*open the file -> .am*/ 
    	fileOBJ=fopen(fileNameO,"w");/*create new file -> .object*/   

    	fprintf(fileOBJ,"     %d    %d\n",IC-100,DC); 
	while(fgets(command,SIZELINE+2,fileAM)){   
        	ptCommand=skipWhite(command);   
        	lineL++;  
        	flagLabel=0;

        	if(ptCommand[0]=='\n' || ptCommand[0]==EOF){/*check for empty line*/  
            		continue; 
        	} 
        	if(ptCommand[0]==';'){  
            		continue; 
        	}   
		cuWord=getWord(ptCommand); 

		if(checkIfLabel(cuWord)){ 
            		ptCommand=getNextWord(ptCommand); 
            		cuWord=getWord(ptCommand); 
            		flagLabel=1;
        	}     
        	if(!strcmp(cuWord,".data") || !strcmp(cuWord,".string") || !strcmp(cuWord,".extern")){   
            		continue;          
        	}   
        	if(!strcmp(cuWord,".entry")){  
            		ptCommand =getNextWord(ptCommand); 
			if(ptCommand[0]=='\n' || ptCommand[0]=='\n'){  
				printf("line %d - WANNING - set entry with no label\n",lineL);   
				continue;
			}
            		cuWord=getWord(ptCommand);  
            		ptSy=GetIfExist(headSymbol,cuWord); 
            		if(flagLabel) 
                		printf("line %d - WANNING - set label for entry\n",lineL); 
            		if(!ptSy){/*if the symbol not exist*/  
                		JUMP_ERROR(lineL,"set entry to label that not exist\n");    
            		}
            		else if(ptSy->type1==External){    
                		JUMP_ERROR(lineL,"set entry to label the set also external\n");  
            		}
            		else{ 
                		ptSy->type2=Entry;  
                		continue;
            		}  
		}   
		/**its  instruction word**/
		ptIC=getIc(cuWord);   
		fWord=codingFirstWord(ptIC,&ICF);    
        	addFirstWord(fWord,fileOBJ,&ICF);
        	if(getNumOp(ptIC)>0){ /*there is more then one operand--add second word*/  
            		ptCommand=getNextWord(ptCommand);
            		op1=strtok(ptCommand,",");  
            		op2=strtok(NULL,",");   
            		if(op2){ 
                		op2=skipWhite(op2);  
				op2=ignoreSpace(op2);    
            		}  
			if(op1){
				op1=ignoreSpace(op1);/*delete space from the end of the string and set \0*/  
			} 
            		sWord=codingSecondWord(ptIC->funct,op1,op2,&ICF);  
            		addSecondWord(sWord,fileOBJ,&ICF);  
            		err=checkErrorLabel(op1, headSymbol);  
            		if(err) 
                		JUMP_ERROR(lineL,err); 
			err=checkErrorLabel(op2,headSymbol);  
            		if(err) 
                		JUMP_ERROR(lineL,err);  
            		codingAditionWord(op1,fileOBJ,headSymbol,&ICF,&headExternal); 
            		codingAditionWord(op2,fileOBJ,headSymbol,&ICF,&headExternal);  
		}  
	}   
    	if(*success){/*if wasnt any error*/
    	ride3(fileName,fileOBJ,&ICF);  
    	createFiles(headSymbol,fileName,headExternal); 
    	} 
    	else{  
        	fclose(fileOBJ);
        	remove(fileNameO);
    	}
} 
 
/*this ride3 only add data to the file */
void ride3(const char* fileName,FILE* fileOBJ,int* ICF){   
	char command[SIZELINE+2];  
    	char* ptCommand=NULL; 
    	char* cuWord=NULL;    
    	char fileNameA[SIZELABEL];  
    	FILE* fileAM;  
   
    	strcpy(fileNameA,fileName); 
    	strcat(fileNameA,".am\0"); 
    	fileAM=fopen(fileNameA,"r");/*open the file -> .am*/ 

    	while(fgets(command,SIZELINE+2,fileAM)){   
        	ptCommand=skipWhite(command);  

        	if(ptCommand[0]=='\n' || ptCommand[0]==EOF){/*check for empty line*/  
            		continue; 
        	}   
        	cuWord=getWord(ptCommand);

        	if(checkIfLabel(cuWord)){ 
            		ptCommand=getNextWord(ptCommand); 
            		cuWord=getWord(ptCommand); 
        	}     
        	if(!strcmp(cuWord,".data")){  
            	ptCommand=getNextWord(ptCommand);
            	addDataToFile(ptCommand,fileOBJ,ICF);            
        	}   
        	if(!strcmp(cuWord,".string")){  
            		ptCommand=getNextWord(ptCommand); 
            		addStringToFile(ptCommand,fileOBJ,ICF);
        	}
	}  
}




