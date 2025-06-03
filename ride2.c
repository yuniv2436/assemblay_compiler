#include "ride2.h"


word1* codingFirstWord(ptInstruction ptIC,int * ICF){/*make a new struct firstWord*/ 
	word1* fWord=(word1*)malloc(sizeof(word1));  
    	fWord->word=(firstWord*)malloc(sizeof(firstWord)); 
    	fWord->split=(ABCD*)malloc(sizeof(ABCD));  


    	fWord->word->msb=0;/*allways zero*/  
    	fWord->word->ARE=4;/*100 in binary=A from ARE*/ 

	fWord->word->opcode=0;  
    	fWord->word->opcode=setBit(fWord->word->opcode,ptIC->opcode); 

	return fWord;
}  

int getReg(char* op){ /*get the number of the register*/
	int i=0;  
    	int j=0;
    	char regNum[3];  

	while(op[i]!='r'){  
        	i++;
    	}  
    	i++;
    	while(isdigit(op[i])){  
        	regNum[j]=op[i]; 
        	i++; 
        	j++;
    	}   
    	regNum[j]='\0';

	return atoi(regNum);
}

word2* codingSecondWord(int funct,char* op1, char* op2,int * ICF){/*make a new struct secondWord*/ 
	int regSrc; 
    	int regDas; 
    	int adrSrc; 
    	int adrDas; 

    	word2* sWord=(word2*)malloc(sizeof(word2));   
    	sWord->word=(secondWord*)malloc(sizeof(secondWord)); 
    	sWord->split=(ABCD*)malloc(sizeof(ABCD));

     

	if(op2){ /*there is 2 operands*/   
        	if(getMethod(op1)==3 ||getMethod(op1)==2){ /*thre is regSrc*/  
            		regSrc=getReg(op1); 
        	} 
        	else  
			regSrc=0; 
  
        	if(getMethod(op2)==3 ||getMethod(op2)==2){ /*thre is regDas*/  
            		regDas=getReg(op2); 
       		 }	 
        	else  
            		regDas=0; 
        
        	adrSrc=getMethod(op1); 
        	adrDas=getMethod(op2); 
	}
    	else{ /*one operand*/ 
        	regSrc=0;
        	adrSrc=0;  

        	if(getMethod(op1)==3 ||getMethod(op1)==2){ /*thre is regDas*/  
            		regDas=getReg(op1); 
        	}  
        	else  
            		regDas=0;  
        
		adrDas=getMethod(op1);  
	}  

	sWord->word->msb=0;
        sWord->word->ARE=4;
        sWord->word->adrDas=adrDas; 
        sWord->word->adrSrc=adrSrc;
        sWord->word->dasRegister=regDas;  
        sWord->word->srcRegister=regSrc;
        sWord->word->funct=funct;
        
	return sWord;
} 

void addFirstWord(word1* word,FILE* fileObj,int * ICF){      
    	fprintf(fileObj,"%04d\t",*ICF);
    	fprintf(fileObj,"A%03x-",(word->split->data>>16) & 15);  
    	fprintf(fileObj,"B%03x-",(word->split->data>>12) & 15); 
    	fprintf(fileObj,"C%03x-",(word->split->data>>8) & 15); 
    	fprintf(fileObj,"D%03x-",(word->split->data>>4) & 15); 
    	fprintf(fileObj,"E%03x\n",word->split->data & 15);   

    	*ICF=*ICF+1;  
}

void addSecondWord(word2* word,FILE* fileObj,int * ICF){      
   	fprintf(fileObj,"%04d\t",*ICF); 
   	fprintf(fileObj,"A%03x-",(word->split->data>>16) & 15);  
    	fprintf(fileObj,"B%03x-",(word->split->data>>12) & 15); 
    	fprintf(fileObj,"C%03x-",(word->split->data>>8) & 15); 
    	fprintf(fileObj,"D%03x-",(word->split->data>>4) & 15); 
    	fprintf(fileObj,"E%03x\n",word->split->data & 15);   
    
	*ICF=*ICF+1;   
}  

void addAditionWord(additionWord* word,FILE* fileObj,int * ICF){   
    	fprintf(fileObj,"%04d\t",*ICF);  
    	fprintf(fileObj,"A%03x-",(word->split->data>>16) & 15);  
    	fprintf(fileObj,"B%03x-",(word->split->data>>12) & 15); 
    	fprintf(fileObj,"C%03x-",(word->split->data>>8) & 15); 
    	fprintf(fileObj,"D%03x-",(word->split->data>>4) & 15); 
    	fprintf(fileObj,"E%03x\n",word->split->data & 15);   
    
	*ICF=*ICF+1;   
} 

void printbin(int x){ 
	unsigned int mask=1 << (sizeof(int)*8-1); 

	while(mask){ 
		if(x&mask) 
			putchar('1'); 
		else 
			putchar('0'); 
	
		mask=mask >>1;
	}
}  

int getNumber(char* op1){ /*get imidiete opperand with number and return the number*/ 
	char sNumber[SIZELABEL]; 
    	int number;  
    	int i=1;  
    	int j=0;
    	int flagMP=1;
    	op1=skipWhite(op1); 

    
    	if(op1[i]=='+')
        	i++;   
    	else if(op1[i]=='-'){ 
        	i++;  
        	flagMP=-1;
    	}  
    	while(op1[i]){ 
        	sNumber[j]=op1[i];
        	i++; 
        	j++;
   	 }   
    	sNumber[j]='\0';  
    	number=atoi(sNumber); 
    	number=number*flagMP; 

    	return number;
}    


char* checkErrorLabel(char* op,ptNodeSymbol head){/*check error at the opearnd label*/    
	int method; 
    	char labelName[SIZELABEL]; 
    	int i=0;
    	if(op==NULL) 
        	return NULL; 

    	method=getMethod(op);

	if(method==1){  
        	if(!checkExist(head,op)){   
            		return("the operand(label) not exist"); 
		}
    	} 
	else if(method==2){  
        	while(op[i]!='['){  
            		labelName[i]=op[i]; 
            		i++;
        	} 
		labelName[i]='\0';  
        	if(!checkExist(head,labelName)) 
            		return("the operand(label) not exist");
    	} 
	return NULL;
}  

int getBasic(int adress){ /*return the BASE number*/
	if(adress<16) 
        	return 0; 
    	while(adress>=16){   
        	if(adress%16==0) 
            		return adress; 
        	adress=adress-1;  
    	} 
	return 0;
} 

int getHist(int adress){ /*return the HIST number*/ 
	int basic=getBasic(adress); 
    	return adress-basic;
} 

	int addExternal(ptExternal* head,char* name,int BASE){ 
    	ptExternal pt;	
	if(*head)
	{		
		pt = *head;		
		while(pt->next)
		{			
			pt = pt->next;
		}		
		pt->next = (ptExternal)malloc(sizeof(external));		
		pt = pt->next;
	}
	else
	{		
		*head = (ptExternal)malloc(sizeof(external));
		pt = *head;
	}	
	if(pt && (pt->name = (char *)malloc(31*sizeof(char))))
	{			
		pt->next = NULL;
		pt->name = strcpy(pt->name,name);
		pt->adressBase=BASE;
	}
	else
	{		
		return -2;
	}
	return 1;

}


void codingAditionWord(char* op,FILE* fileobj,ptNodeSymbol head,int * ICF,ptExternal* headExternal){ /*adding lined to the ovject file with the adittion word*/
       
	additionWord* w1=(additionWord*)malloc(sizeof(additionWord));  
        additionWord* w2=(additionWord*)malloc(sizeof(additionWord));  
        ptNodeSymbol ptSymbol=(ptNodeSymbol)malloc(sizeof(nodeSymbol));
        int method;    
        char labelName[SIZELABEL]; 
        int i=0;

        w1->word=(addition*)malloc(sizeof(addition)); 
        w1->split=(ABCD*)malloc(sizeof(ABCD));    
        w2->word=(addition*)malloc(sizeof(addition)); 
        w2->split=(ABCD*)malloc(sizeof(ABCD));  
        
	if(op!=NULL){ 
		method=getMethod(op);
        	if(method==0){    
            	w1->word->ARE=4; 
            	w1->word->msb=0; 
            	w1->word->data=getNumber(op);
        	} 
        	else if(method==1){     
            		ptSymbol=GetIfExist(head,op); 
            		if(ptSymbol->type1==External){ 
                		w1->word->ARE=1; 
                		addExternal(headExternal,ptSymbol->name,*ICF); 
            		} 
            		else{ 
                		w1->word->ARE=2;
            		}
            		w1->word->msb=0; 
			w1->word->data=getBasic(ptSymbol->adress);  

            		if(ptSymbol->type1==External){ 
                		w2->word->ARE=1; 

            		}   
            		else{ 
                		w2->word->ARE=2;
            		} 
            		w2->word->msb=0; 
            		w2->word->data=getHist(ptSymbol->adress); 
		} 
        	else if(method==2){  
            		while(op[i]!='['){  
            			labelName[i]=op[i]; 
            			i++;
            		} 
			labelName[i]='\0';  
            		ptSymbol=GetIfExist(head,labelName);  
            		if(ptSymbol->type1==External) 
                	w1->word->ARE=1; 
            		else{ 
                		w1->word->ARE=2;
            		}  

            		w1->word->msb=0; 
            		w1->word->data=getBasic(ptSymbol->adress);  

			if(ptSymbol->type1==External){ 
			w2->word->ARE=1;  
                	addExternal(headExternal,ptSymbol->name,*ICF); 
            		}
            		else{ 
                		w2->word->ARE=2;
            		} 
            		w2->word->msb=0; 
            		w2->word->data=getHist(ptSymbol->adress);
		} 
        	if(method!=3){
            		addAditionWord(w1,fileobj,ICF);  
            		if(method!=0)
                	addAditionWord(w2,fileobj,ICF); 
        	}
	}
}  

void addDataToFile(char* ptCommand,FILE* fileOBJ,int* ICF){   
	const char s[2] = ",";
	char* token = strtok(ptCommand, s);  
    	char number[SIZELABEL];   
    	int num;
    	int j;
	int i;  
    	int flagMP=1; 
    	additionWord* w1=(additionWord*)malloc(sizeof(additionWord));  

    	w1->word=(addition*)malloc(sizeof(addition)); 
    	w1->split=(ABCD*)malloc(sizeof(ABCD));    

    	while( token != NULL ){  
        	i=0; 
        	j=0;  
        	number[j]='\0';
        	token=skipWhite(token); 
        	if(token[i]=='+') 
            		i++; 
        	if(token[i]=='-'){ 
            		i++; 
            		flagMP=-1;
        	}  
		while(token[i]!=' ' && token[i]!='\0' && token[i]!='\n' && token[i]!=EOF && token[i]!='\t'){ 
            		number[j]=token[i]; 
            		number[j+1]='\0'; 
            		i++; 
            		j++;
        	}  
		num=atoi(number); 
        	num=num*flagMP;
        	w1->word->ARE=4; 
        	w1->word->msb=0; 
        	w1->word->data=0; 
        	w1->word->data=num;    
        	addAditionWord(w1,fileOBJ,ICF);  
        	token = strtok(NULL, s);
	}
}

void addStringToFile(char* ptCommand,FILE* fileOBJ,int* ICF){
	int j=0;
	int i=1;  
	additionWord* w1=(additionWord*)malloc(sizeof(additionWord));  

	w1->word=(addition*)malloc(sizeof(addition)); 
	w1->split=(ABCD*)malloc(sizeof(ABCD));      

	while(ptCommand[i]!='\n' && ptCommand[i]!=EOF){ 
        	if(ptCommand[i]=='\"') 
            		j=i;
        	i++;
    	}   
	i=1;
	while(i!=j){  
        	w1->word->ARE=4; 
        	w1->word->msb=0; 
        	w1->word->data=(ptCommand[i]);   
        	addAditionWord(w1,fileOBJ,ICF); 
        	i++; 
    	}  
    	w1->word->data=0;  
    	addAditionWord(w1,fileOBJ,ICF);  
}

void createFiles(ptNodeSymbol head,const char* fileName,ptExternal headExternal){ /*create the files - ext ent */

	char FileNameEXT[SIZELABEL]; 
	char FileNameENT[SIZELABEL];  
    	FILE* fileEXT; 
    	FILE* fileENT; 

    	strcpy(FileNameEXT,fileName);  
    	strcat(FileNameEXT,".ext\0");  
    	strcpy(FileNameENT,fileName); 
    	strcat(FileNameENT,".ent\0");   

    	fileEXT=fopen(FileNameEXT,"w");/*open the asembler file the user enter for reading*/ 
    	fileENT=fopen(FileNameENT,"w");/*open the asembler file the user enter for reading*/

    	while(head)
	{	  
        	if(head->type2==Entry){ 
            		fprintf(fileENT,"%s,%04d,%04d\n",head->name,getBasic(head->adress),getHist(head->adress)); 
        	} 
        	head=head->next;
	} 


	while(headExternal)
	{ 
        	fprintf(fileEXT,"%s BASE %04d\n",headExternal->name,headExternal->adressBase);  
        	fprintf(fileEXT,"%s OFFSET %04d\n",headExternal->name,headExternal->adressBase+1);  
        	fprintf(fileEXT,"\n"); 

		headExternal=headExternal->next;		
	}
}
