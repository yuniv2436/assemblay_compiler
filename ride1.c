 
#include "ride1.h"
 
int checkIfLabel(char* word){/*check if the word is  a label*/  
	int length=strlen(word); 
	if(word[length-1]==':') 
        	return 1; 
    	else 
        	return 0;
}

char* parseLabel(char* word){  /*check errors in the label and send string of the error*/
	int i=0;
    	int length=strlen(word); 

    	while(strcmp(registers[i],"undefind")){ 
        	if(i<=14 && !strcmp(word,registers[i]))
            		return("name of label cant be register name"); 
        	if(!strcmp(word,operations[i])) 
            		return("name of label cant be operations name");  
        	if(i<=3 && !strcmp(word,directions[i])) 
            		return("name of label cant be derection name"); 
        	i++;
	} 
	if(length>31) 
        	return("length of label cant be more then 31 letters"); 

    	i=0; 

	while(i!=strlen(word)-1){   
        	if(i==0 && !isalpha(word[i])){  
            		return("first char in label must be alpha");  
		} 
        	if(!isalnum(word[i]))
            		return("the chars in label must be alphanumeric");  
        	i++; 
    	}   
	return NULL;
}

char * getNextWord(char* ptWord){/*return pointer to the begin of the next word*/  
	int i=0;
    	while((ptWord[i] != ' ') && (ptWord[i] != '\t') && (ptWord[i] != '\n')){ 
        	i++;
    	} 
    	ptWord+=i; 
    	ptWord=skipWhite(ptWord); 
    	return ptWord;
}

char* parseString(int * DC,char* string){  /*get pointer to the begining of the string and return if was any error else return null*/ 
	int j=0;
	int i=0; 
	int flag=0;   

	if((string)[i]!='\"')
		return ("string shuld start with quotation marks");  

	while((string)[i]!='\n' && (string)[i]!=EOF && (string)[i]!=13){ 
		if((string)[i]=='\"'){ 
			j=i;/*save the last index that was quotation mark*/
            		flag=1;
        	} 
        	else if((string)[i]!=' ' && (string)[i]!='\t'){  
            		flag=0; 
        	} 
        	i++;
    	}  
	if(!flag)  
		return("string shuld close with quotation marks"); 

	*DC=*DC+j;  
	return NULL;
}   
   

int checkComma(char* ptCommand){ /*check if exist ",," in the string*/  
	int i=0; 
	while(ptCommand[i] != '\n' && ptCommand[i] !=EOF){
		if(ptCommand[i]==',' && ptCommand[i+1]==',') 
			return 1; /*there is double comma*/
		else 
		i++; 
	} 
	return 0;
} 

char* parseNumbers(int* DC,char** ptCommand){ /*parse errors in the number data*/
	const char s[2] = ",";
	char *token; 
	int i=0;
	int empty=0; 
	int comma=0; 
	int invalidChar=1;

	if(checkComma(*ptCommand)) 
		return("there is double comma->,,");
	token = strtok(*ptCommand, s);

	while( token != NULL ){ 
		comma=0;
		i=0;
		empty=0;  

		while(token[i] && token[i]!='\n' && token[i]!=13){  
			if(comma && token[i]!=' ' && token[i]!='\t') 
				return("missing comma bitwin two numbers");
			if(token[i]!=' ' && token[i]!='\t')
				empty=1; 
			else
				invalidChar=0;
			if((token[i]=='+' || token[i]=='-')){ 
				invalidChar=0; /* == + || -*/
				if(!isdigit(token[i+1])) 
					return ("there is not correct mark plus");  
			}
			if(isdigit(token[i]) && (token[i+1]==' ' || token[i]=='\t'))  
				comma=1;  
			if(invalidChar && !isdigit(token[i])){/*the char not ' ' || '+' || '-' || '\t' || digit */  
				return("there is not number");   
			}  
				
			invalidChar=1;
			i++; 
	 	}  
		if(!empty) 
			return("there is extra comma"); 
		token = strtok(NULL, s);   
		*DC=*DC+1;  
	}  
	*ptCommand=(*ptCommand)+i+1;
	return NULL;
}   
 
char* checkExistIc(char* cuWord){/*check if the instruction word exist, return null if exist*/  
	int i=0; 
    	while(!strcmp("undefind",operations[i])){  
        	if(!strcmp(cuWord,operations[i])) 
            		return ("the instruction word not exist");
    	} 
    	return NULL;
}  

ptInstruction getIc(char* IC){ /*get pointer to instruction struct if exist*/
	int i=0;
    	while(strcmp(ptArrIC[i]->name,"undefind")){  
        	if(!strcmp(ptArrIC[i]->name,IC)) 
            		return ptArrIC[i];
        	i++;
    	}   		
    	return NULL;/*if the IC command not exist the funcion return NULL else return pointer to the IC data*/
}  

int getNumOp(ptInstruction ptIC){ /*return number of operand shuld be in the struction word*/
	int count=0; 
    	if(ptIC->das>0) 
        	count++; 
    	if(ptIC->src>0) 
        	count++;  
    	return count; 
}

char* parseOperands(ptInstruction ptIC,char* ptCommand){ /*loking for error in the instruction command*/ 
	int numOP=getNumOp(ptIC); /*number operand shuld be*/ 
    	int countOP=0;/*count operand at the string*/
    	const char s[2] = ",";
	char *token=strtok(ptCommand, s); 
	int i=0; /*index of token*/ 
    	int empty=0; 
	int comma=0; 
 

	while( token != NULL ){   
        	comma=0;
		i=0;
		empty=0;   

        while(token[i] && token[i]!='\n' ){/*until the end of the token*/  
		if(token[i]!=' ' && token[i]!='\t' )
			empty=1;/*not empty*/  
            	if(comma && (token[i]!=' ' && token[i]!='\t')){/**/ 
                	if(numOP==countOP+2) 
                    		return("missing comma bitwin two operands");  
                	else if(numOP==countOP+1)
				return("externous text after last operand");   
		}  
            	if((isdigit(token[i]) || isalpha(token[i])) && (token[i+1]==' ' || token[i+1]=='\t'))  
			comma=1;  
		i++; 
	}  
	if(!empty){   
		if(numOP==0 && countOP==0) 
		return NULL;
		if(strtok(NULL, s)==NULL && countOP<numOP)
                	return("missing opperand");  

		return("there is extra comma"); 
        } 
        countOP++; 
        if(countOP>numOP)  
            return("extra operand"); 

        token = strtok(NULL, s); 
	}  
    	if(numOP>countOP) 
        	return("missing operand");  

	return NULL;
}   

int checkImidiete(char* op){ /*check if the operand is imidiete method*/  
	int i=0;  
    	int flagDigit=0;   

    	if(op[i]=='#'){ 
		i++; 
        if(op[i]=='+' || op[i]=='-') 
		i++;  
        while(op[i]){ 
		if(!isdigit(op[i]) && op[i]!='\n' && op[i]!=' ' && op[i]!='\t')  
                	flagDigit=1; 
		i++;
        }   
        if(!flagDigit)
		return 0;/*imidiete method->#25*/
	}    
	return -1;
} 

int checkDirectR(char* op){ /*check if the operand is direct register method*/   
	int i=0;   
    	int rNUM;

    	if(op[i]=='r'){  
        	i=1;    
        	rNUM=atoi(op+i);
        	if(rNUM>=1  && rNUM<=15){  
            		return 3;/*direct register->*/ 
        	}
    	}  
	return -1;
}

int checkIndexR(char* op){ /*check if the operand is index method*/
	int i=0;  
	char r[SIZELABEL]; 
    	int j=0; 

    	while(op[i]!='['){  
        	i++; 
        	if(!op[i]) 
            		return -1;
    	}  
    	i++;  
    	while(op[i] && op[i]!=']'){ 
        	r[j]=op[i];  
        	j++; 
        	i++;
    	}    
    	r[j]='\0';
    	if(op[i]==']'){ 
        	i=0;
        	while(strcmp(registers[i],"undefind")){ 
            	if(!strcmp(r,registers[i])) 
                	return 2; 
            	i++;
        	} 
    	} 

	return -1;
}

int getMethod(char* op){/*return 0,1,2,3 if the method exist else return -1*/   

	if(checkImidiete(op)>=0) 
        	return checkImidiete(op); /*0*/
    	else if(checkDirectR(op)>0) /*3*/
            	return  checkDirectR(op); 
    	else if(checkIndexR(op)>0) /*2*/
            	return checkIndexR(op);
    	else 

        	return 1;
}

char* parseIntegrity(int* IC,char* ptCommand,ptInstruction ptIC){ /*parse the operand and the instruction word match*/
	char* op1; 
    	char* op2;  
    	int methodOP1; 
    	int methodOP2; 
    	const char s[2] = ",";

    	if(ptIC->src==0){/*of there is only one operand-src*/  
        	op1=getWord(ptCommand);   
        	methodOP1=getMethod(op1);  
	   
        if(ptIC->das & (1<<methodOP1)){    
		if(methodOP1==1 || methodOP1==2) 
                	*IC=*IC+2; 
            	else if(methodOP1==0) 
                	*IC=*IC+1; 

		*IC=*IC+2; 
            	return NULL;
        }
        else  
		return("operand method not fit to instruction word");
	} 
    	else{/*there is 2 operand src and das*/  
        	op1=strtok(ptCommand,s);  
        	op2=strtok(NULL,s);   
        	op2=skipWhite(op2);  
        	methodOP1=getMethod(op1); 
		methodOP2=getMethod(op2);    
    	 
		if((ptIC->src & (1<<methodOP1)) && (ptIC->das & (1<<methodOP2))){     
            		if(methodOP1==1 || methodOP1==2) 
                		*IC=*IC+2; 
            		else if(methodOP1==0) 
                		*IC=*IC+1;   
            		if(methodOP2==1 || methodOP2==2) 
                		*IC=*IC+2; 
           		 else if(methodOP2==0) 
                		*IC=*IC+1; 
			*IC=*IC+2;  

		return NULL;
	}    
        else 
		return ("operand method not fit to instruction word"); 
	}
}  

void printTable(ptNodeSymbol headSymbol){ /*print the all table-->only for the developer*/
	ptNodeSymbol temp=headSymbol; 
    	printf("name\t"); 
    	printf("address\t"); 
    	printf("type1\t"); 
   	printf("type2\t");   
    	printf("\n");

	while (temp != NULL) {
        	printf(" %s\t", temp->name); 
        	printf(" %d\t", temp->adress); 
        	printf(" %d\t", temp->type1);
        	printf(" %d\t", temp->type2);        
        	printf("\n");
        	temp = temp->next;
    	} 
} 

void updateTable(int IC,ptNodeSymbol headSymbol){ /*update the dc to be DC+IC*/  
	ptNodeSymbol temp=headSymbol;
    	while (temp != NULL) { 
        	if(temp->type1==0){ 
			temp->adress=temp->adress+IC;
        	} 
		temp = temp->next;
    	} 
}

int setBit(int n, int k)/*turn on the bit k at the int n */
{
	return (n | (1 << (k)));
}
 
  













 





