
#include "data.h"

extern FILE *fd;
extern char *line; /* contains a line in the file to be scanned - stored in heap*/ 
extern char *word; /* the STRING to search for anagram- stored in heap*/

/******************************************************************************/
 void  validFile(FILE *fd) {
 	  long size;
 	
     if (fd == NULL) {
        fprintf(stderr,"Error: can not open file!\n");
        exit(0);
    }
    
    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    if (size == 0) {
        fprintf(stderr,"Error: The file is empty\n");
        exit(0);
    }
    rewind(fd); /*Return pointer to the beginning of the file*/
}

/********************************************************************************/

void countLetters(char token[] , int letteCount[]) 
{
    int i;
    
    for (i = 0; i< SIZE_LETTERS; i++) 
  	 	letteCount[i]=0;
    
    for (i = 0; word[i] != '\0'; i++) 
  	 	letteCount[token[i] - FIRST_LETTER]++;
}



/*****************************************************************************/

void getLine() {

    char *q= NULL;
    int len = 0;
    int ch;
    
   line=(char *)malloc(0);
				
    /*Get line*/
    while (((ch=fgetc(fd))!='\n') && !feof(fd)) { 
       	q = (char *)realloc(line, len + 1);
			message_realloc(q,line,word,fd) /*message - memory faild*/
         line=q;
         line[len++] = ch;         
    }
      
    /*add '/0' to end the string*/ 	
    if (!feof(fd)) {		
       	if (ch == '\n') {
        		q = (char *)realloc(line, len + 1);
         	message_realloc(q,line,word,fd) /*message - memory faild*/		
         	line=q;
       		line[len++] = '\0';
	       	
    		}
    }
 }


/*****************************************************************************************************/ 


 int FindAnagram (char *token, char *word , int letteCount_w[] ) {
	
	int n;
	char *window; /*the segment that scaned*/
	int letteCount_t[SIZE_LETTERS]; /*count letter array of window*/
	int len=0, i=0, j=0, k=0, l=0, counter=0, comper=0;
			
	len=strlen(token);
	n=strlen(word);
	
	window=(char *)malloc(n*sizeof(char));
	message_malloc(window,line,word,fd) /*message - memory faild*/
	
		if (len < n){ 
			free(window);
			window=NULL;
			return(0);
		}
		
		else {
      	while (i <= len - n) {
      		k=0;
      		for (j = i; j < i + n; j++) {
            	window[k]=token[j];
        /*    	printf("%c", token[j]);*/
            	k++;
            }
            
            countLetters(window , letteCount_t); /*create letter counts arrays of window*/
				
				/*check if the "window" is anagram of "word"*/
				comper=0;
				for (l=0; l < SIZE_LETTERS; l++)
					comper+=(!(letteCount_t[l]==letteCount_w[l]));
									
				if (comper==0){	
					for (k=0; k < n ; k++)
						fprintf(stdout,"%c", window[k]);
						
					fprintf(stdout,"\n");	
					counter++; 
					i=i+n-1;	/* Do not allow overlapping anagrams*/
				}  
				 		
        		i++;
        	}
        	      	
        	free(window);
        	window=NULL;
       	return counter;
    }
 }		
		
 

