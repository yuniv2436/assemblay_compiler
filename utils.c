#include "utils.h"

int getLength(char* ptWord){  /*return the length of the first word in the line, *not include '\0'*/ 
	int i=0;
    	while((ptWord[i] != ' ') && (ptWord[i] != '\t') && (ptWord[i] != '\n') && (ptWord[i] != EOF)){  
        	i++;
    	}
	return i; 
} 

char* getWord(char* ptWord){   
	int length=0; 
    	int i;  
    	char* word;
    	length=getLength(ptWord);
    	word=(char*)malloc((length+1)*sizeof(char)); 
    	for(i=0;i<length;i++){  
        	word[i]=ptWord[i];
    	}  
    	word[i]='\0';
	return word; 
}

char *skipWhite(char *s){ 
	int i;
	for (i = 0; s[i] != 0 && (s[i] == ' ' || s[i] == '\t'); i++) {
	} /* Count how many spaces there are at the beginning */ 

	return s + i;
}    

char * ignoreSpace(char* word){  
	int i=0 ; 
	while(word[i]!=' '&& word[i]!='\t' && word[i]!='\n' && word[i]!=EOF){   
		i++;
	}
	word[i]='\0';  

	return word;
} 





























