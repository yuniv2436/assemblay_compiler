
#include "global.h"  
#include "macro.h"

void printMacroList(ptMacro head)
{ 
	ptMacro temp=head;
    	while (temp != NULL){
        	printf(" %s ", temp->name);
        	temp = temp->next;
    	}
}

void addMacro(ptMacro* head,ptMacro newMacro){  
	if(*head==NULL){ 
        	*head=newMacro; 
   	 } 
    	else{ 
        	ptMacro lastNode=*head;  
        	while(lastNode->next != NULL){ 
            	lastNode=lastNode->next;
        } 
	lastNode->next=newMacro;
    }
} 

int searchMacro(ptMacro head,char* macroName){  
	ptMacro temp=head; 

	while(temp != NULL){ 
        	if(!strcmp(temp->name,macroName)) 
            		return 1;
        	temp=temp->next;
    	} 
	return 0;
} 
 
void addLinesToFile(ptMacro head,char* macroName,FILE* file){ 

	ptMacro lastNode=head;  
    	while(lastNode != NULL){ 
        	if(!strcmp(lastNode->name,macroName)) 
            		break;

        	lastNode=lastNode->next;
    	}  
    	if(lastNode==NULL) 
        	return; 
    	fprintf(file,"%s",lastNode->lines);
} 

int isMAEmpty(ptMacro head){

	return (head)? 0 : 1;
} 

void DeleteMacros(ptMacro* head){

	ptMacro pt; 
    	ptMacro next;
	if(!isMAEmpty(*head)){
	
		pt = *head;
		while(pt)
		{
			next = pt->next;
			free(pt);
			pt = next;
		}
		*head = NULL;
	}
}

