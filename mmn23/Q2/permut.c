
/*********************************************************************/
/******      submitted by Efrat Friedrich     ***********/
/*******************************************************************************
This program open a txt file and scans it in order  to find a permutation  (anagram) of a given STRING.

STRING may contains any ASCII characters between 32 (SPACE) and 126 (~).

The user should enter 2 arguments via the command line:
1) file name
2) a STRING to search it's anagram in the file. A STRING containing spaces must be wrapped with "".

The program stops if 
	- the user didn't enter exactly 2 command line argumens as mentioned above. 
	- the file is empty
	- memory allocation failed

The program prints all the anagrams.

exaples for "token":anagram
	- "chai": no ANAGRAM found 
	- "gariches": arich 
	- "CHAIR":no ANAGRAM found
	- "chaiddddrcha1h7":no ANAGRAM found
	- "chairchddrcha1h7raichraich": chair , raich, raich


The algorithm 
	- reads line by line (character by character until "enter" detected.) 
	- splits line into tokens 
	- scans the token to find anagrams and prints it.
	

For explanations of the auxiliary functions, refer to the data.h files 

********************************************************************************/

#include "data.h"

FILE *fd;
char *line; /* contains a line in the file to be scanned - stored in heap*/ 
char *word; /* the STRING to search for anagram- stored in heap*/
  
int main(int argc, char *argv[])
{
	 
 	int n;       		  	   /* length of the input STRING*/ 
   int word_cnt[SIZE_LETTERS]={0}; /*the letter counts arrays of "STRING" */
   int counter=0;          /*number of anagram found*/
   		      
  	    
	/*********** check command line arguments ***********/
	if (!(argc==3))
	{
		fprintf(stderr,"Error: you entered %d arguments \n",argc);
		fprintf(stderr,"you must enter exactly two arguments: a file name and one string.\n");
		fprintf(stderr,"Wrapped in quotes if the string contains more than one word.\n");
		exit(0);
	}

	
   /*********** open file  and validate it ****************************/ 
   fd = fopen(argv[1], "rt");
   validFile(fd);
   

  /*********** get word  *******************************/
    
    n=strlen(argv[2])+1; 
    word=(char *)malloc(n*sizeof(char));
    message_malloc1(word,fd) /*message - memory faild*/
    
    strncpy(word, argv[2], n-1);
    word[n]='\0';
    
	 fprintf(stdout, "The string to search for is:%s\n", word);
	 fprintf(stdout, "The results are:\n");
    
    	
	 countLetters(word , word_cnt); /*create letter counts arrays of word*/

	/*********** search for anagrams and print results *******/   
	
	
   while (!feof(fd)){
		line=NULL;
		getLine();
 	
		counter = counter + FindAnagram(line, word , word_cnt);

 		free(line);
	}	
	
   if (counter==0)
	  	fprintf(stdout,"no ANAGRAM found\n");
	
   free(word);     	
   fclose(fd);
   return 0;
}

