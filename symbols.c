
#include "global.h"  
#include "symbols.h" 
 
void printSymbolList(ptNodeSymbol head)
{ 
	ptNodeSymbol temp=head;
    	while (temp != NULL) {
        	printf(" %s ", temp->name); 
		printf("->");
        	temp = temp->next;
   	 }
}

int addNext(ptNodeSymbol* head,char* labelName, int adress, short type)
{
	ptNodeSymbol pt;	
	if(*head)
	{		
		pt = *head;		
		while(pt->next)
		{			
			pt = pt->next;
		}		
		pt->next = (ptNodeSymbol)malloc(sizeof(nodeSymbol));		
		pt = pt->next;
	}
	else
	{		
		*head = (ptNodeSymbol)malloc(sizeof(nodeSymbol));
		pt = *head;
	}	
	if(pt && (pt->name = (char *)malloc(31*sizeof(char))))
	{			
		pt->next = NULL;
		pt->name = strcpy(pt->name, labelName);
		pt->adress = adress;
		pt->type1 = type;
	}
	else
	{		
		return -2;
	}
	return 1;
}

int checkExist(ptNodeSymbol head, char *name)
{	
	while(head)
	{ 
		if(strcmp(head->name,name) == 0)
			return 1;
		head = head->next;		
	}
	return 0;
} 

ptNodeSymbol GetIfExist(ptNodeSymbol head, char *name)
{
	while(head)
	{	 
		if(!strcmp(head->name,name))
			return head;
		head = head->next;		
	}
	return NULL;
} 

int isSYEmpty(ptNodeSymbol head)
{
	return (head)? 0 : 1;
} 

ptNodeSymbol getNextSY(ptNodeSymbol* head)
{
	ptNodeSymbol p;
	if(!isSYEmpty(*head))
	{
		p = *head;
		*head = (*head)->next;
		return p;
	}
	return NULL;
} 

void DeleteSymbols(ptNodeSymbol* head)
{
	ptNodeSymbol pt; 
	ptNodeSymbol next;
	if(!isSYEmpty(*head))
	{
		pt = *head;
		while(pt)
		{
			next = pt->next; 
			free(pt->name);
			free(pt); 
			pt = next;
		}
		*head = NULL;
	}
} 

