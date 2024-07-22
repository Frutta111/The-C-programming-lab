#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FIRST_LETTER 32 /*FIRST ASCII CODE*/
#define SIZE_LETTERS 95 /*NUMBER OF ASCII LETTERS TO BE CHECKED IN RANGE*/

#define message_realloc(a,b,c,d) \
			if (!a) { \
    			fprintf(stderr, "Error: memory allocation faild"); \
    			free(b); \
    			free(c); \
    			fclose(d);\
    			exit (0); \
    		} 

#define message_malloc(a,b,c,d) \
			if (!a) { \
    			fprintf(stderr, "Error: memory allocation faild"); \
   			free(b); \
    			free(c); \
    			fclose(d);\
    			exit (0); \
    		} 
    		
#define message_malloc1(a,d) \
			if (!a) { \
    			fprintf(stderr, "Error: memory allocation faild"); \
    			fclose(d);\
    			exit (0); \
    		} 

void validFile(FILE *fd);     
void countLetters(char token[] , int letteCount[]) ;
void getLine() ;
int FindAnagram (char *token, char *word , int letteCount_w[] );



 /*****************************************************************************
 The function **validFile** receives a pointer to the file, informs and stops the program if
  the file is empty or does not exist.
 ******************************************************************************/  
 
/*****************************************************************************
This function **countLetters** accepts  a string and emprty ineger array.
it returns the letter counts array of size MAX_LETTERS that representing the letters in the string.
******************************************************************************/

/*********************************************************************************
The function **getLine** gets global variables: a pointer to a txt file and an empty string (line).
 
It scan the file and insert to the string character by character until the character 
"enter" is detected.

The function uses dynamic memory allocation to store the line.
if used MUST free memory allocation line!
**********************************************************************************/

/*******************************************************************************
This function **FindAnagram** receives a string (token), a word (word), a letter count array of the word representing all ASCII codes between 32 (SPACE) and 126 (~).
The function prints on the screen the anagrams (permutations) of a given word that appear in the string. The function does not print overlapping anagrams.
For example,
Possible outputs for the anagram for the word chair:

"token":anagram
"chai": no ANAGRAM found 
"gariches": arich 
"CHAIR":no ANAGRAM found
"chaiddddrcha1h7":no ANAGRAM found
"chairchddrcha1h7raichraich": chair , raich, raich

The function returns the number of anagram found in a token.
********************************************************************************/



