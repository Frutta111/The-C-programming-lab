#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "set.c"

int main ()
{
    char *nameOfSets2[numOfSets]={"SETA", "SETB", "SETC", "SETD", "SETE", "SETF"};
    char *nameOfCommands2[numOfCommands]={"read_set", "print_set", "union_set", "intersect_set", "sub_set", "symdiff_set", "stop"};
    char newLine [maxInputSize];
    char * ptr;
    int commandNumber;
    int j;
	int i; 
    int numbers [maxNumbers];
    char * set1Name;
    set * sets [numOfSets]; /* 6 different sets in array of sets */ 
    set * set1 = creatSet(); /* pointer */ 
    set * set2 = creatSet(); /* pointer */ 
    set * set3 = creatSet();	/*pointer */ 
    memset(set1, 0, numOfBytes);
    memset(set2, 0, numOfBytes);
    memset(set3, 0, numOfBytes);
    for (j = 0; j < numOfSets; j++)
    {

        if((sets[j] = creatSet()) == NULL)
        {
            int k;
            for (k = 0; k < j; k++)
            {
                free (sets[k]);
            }
            exit (0);
        }
    }
	printf ("Hi! I'm going to introduce to you our new interactice caculator. \n");
	printf ("This caculator will do some operations on set numbers. \n");
	printf ("We are going to learn step by step how to use it well.\n");	
	printf ("The command line use to include the relevant name of sets, potentially command in the right struct of line.\n");
	printf ("The potentially commands on the numbers are : read_set, print_set, union_set, intersect_set, sub_set and symdiff_set \n");
	printf ("The potentially names of sets are : SETA, SETB, SETC, SETD, SETE and SETF (with capital letters). \n");
	printf ("The numbers we will enter to each set sould be between 0 - 127. \n");
	printf ("The struct of the line is different if we use different commands : \n");
	printf ("if we use read_set, the line should be : |read_set| |name of set|, |number|, |number|,... to end it enter -1 and then |enter| \n");
    printf ("For example : read_set SETB, 5,67,89,-1 and |enter| \n");
	printf ("Note: there is no output aftar read_set operation. \n");
	printf ("if we use print_set, the line should be : |print_set| |name of set| and then |enter| , for example: \n");
	printf ("print_set SETC and |enter| \n");
	printf ("if we use union_set, intersect_set, sub_set and symdiff_set, the line should be : |command| |name of first set|, |name of second set|, |name of thirs set| and then |enter| .\n");
	printf("The result of the operetion on the two first sets, enters to the third set. \n"); 
	printf ("For example: sub_set SETC, SETD, SETB and |enter| \n");
	printf ("If there is a problem, it will print you message \n");
	printf ("To end the program write : |stop| and then |enter| and |enter| \n");
	printf ("For example : stop \n"); 
	printf ("Enjoy! \n");
	printf ("--> ");
	while (fgets (newLine ,maxInputSize, stdin) != NULL) {
        ptr = newLine;
        while (isspace(*ptr)) {
            ptr++; /* the pointer is on the command */
        }
        if (allLineIsValid(ptr))  /*the all line is valid*/
        {
            commandNumber = commandIsValid(ptr);
            ptr = ptr + strlen(nameOfCommands2[commandNumber]);
            while (isspace(*ptr)) {
                ptr++; /* the pointer is on the command */
            }
            set1Name = nameOfSets2[nameIsValid(ptr)];
            set1 = sets[nameIsValid(ptr)];
            ptr = ptr + strlen(nameOfSets2[nameIsValid(ptr)]);
            i = 0;
            switch (commandNumber)
            {
                case 0:
                    while ((*ptr) != '\0' && (ptr) != NULL) /* the line is good, and we are not in the end of line/input */
                    {
                        while ((isspace((*ptr))) || ((*ptr) == ',')) {
                            ptr++;
                        }
                        numbers[i] = strtol(ptr, &ptr, 10);
                        i++;
                    }
                    memset(set1, 0, numOfBytes); /* initialization of set1 */
                    read_set(set1, numbers, i-1);
                    break;
                case 1:
                    printf("%s is : ", set1Name);
                    print_set(set1);
                    printf("\n");
                    break;
                case 2: case 3: case 4: case 5:
                    while ((isspace((*ptr))) || ((*ptr) == ',')) {
                        ptr++;
                    }
                    set2 = sets[nameIsValid(ptr)];
                    ptr = ptr + strlen(nameOfSets2[nameIsValid(ptr)]);
                    while ((isspace((*ptr))) || ((*ptr) == ',')) {
                        ptr++;
                    }
                    set3 = sets[nameIsValid(ptr)];
                    if (commandNumber == 2)
                        union_set(set1, set2, set3);
                    if (commandNumber == 3)
                        intersect_set(set1, set2, set3);
                    if (commandNumber == 4)
                        sub_set(set1, set2, set3);
                    if (commandNumber == 5)
                        symdiff_set(set1, set2, set3);
                    break;
                case 6:
                    for (i = 0; i < numOfSets; i++) {
                        free(sets[i]);
                    }
					while ((isspace(*ptr)) || ((*ptr) == '\0' || (*ptr) == EOF)) 					{
						stop();
                    	break;
					}
					                    
            }
        }
		printf ("--> ");
    }
	if ((*ptr) != EOF)
	{
    	printf ("The calculator stops, without 'stop' command \n");
		return 0; 
	}
return 0; 
}

