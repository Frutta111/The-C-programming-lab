#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "set.h"


/* the function get pointer to the input line pointer to the new num, and number of numbers,
  the function enters the numbers in to the set , the end of input supposed to be -1 */

void read_set(set *s, int *num, int n)
{
    int i;
    for (i = 0; i < n && *num != -1; i++)
    {
        updateBits(s, *num);
        num++;
    }
}

/* the function get pointer to set and print it  */

void print_set(set *s)
{
    int count = 0;
    int i;
    for (i = 0; i < numOfBits; i++)
    {
        if (checkBit(s, i) != 0)
        {
            count++; /* number of numbers in the set */
            if (count % (numsInLine) == 0)
            {
				printf(" %d ", i);
                          	
				printf("\n"); /* 16 numbers in one line */
                
            }
            else
            {
                printf(" %d ", i);
            }
        }
    }
    if(count == 0)
    {
        printf("The set is empty\n");
    }
    else
    {
        printf("\n");
    }

}

/* the function gets pointer to 3 sets and put at the third set the union of the two first sets */

void union_set(set *set1, set *set2, set *unionSet)
{
	int i;    
	set *temp;
    temp = creatSet(); /* we should create new set as we asked */
    for (i = 0; i < numOfBits; i++)
        if (checkBit(set1, i) || checkBit(set2, i)) /* if the number is in one of the first sets */
            updateBits(temp, i);

    memcpy(unionSet, temp, numOfBits); /* after creat new set we point with the third set to this set */
    free(temp); /* free space */
}

/* the function gets pointer to 3 sets and put at the third set the intersection of the two first sets */

void intersect_set(set *set1, set *set2, set *intersectionSet)
{
	int i;    
	set *temp;
    temp = creatSet(); /* we should create new set as we asked */
    for (i = 0; i < numOfBits; i++)
        if (checkBit(set1, i) && checkBit(set2, i)) /* if the number is in both of the first sets */
            updateBits(temp, i);
    memcpy(intersectionSet,  temp, numOfBits); /* after creat new set we point with the third set to this set */
    free(temp); /* free space */
}

/* the function gets pointer to 3 sets and put at the third set the subtraction of set2 from set1 */
void sub_set(set *set1, set *set2, set *subSet)
{
	int i;    
	set *temp;
    temp = creatSet();
    for (i = 0; i < numOfBits; i++)
        if (checkBit(set1, i) && !(checkBit(set2, i)))
            updateBits(temp, i);
    memcpy(subSet, temp, numOfBits);
    free(temp);
}

/*  the function gets pointer to 3 sets and put at the third set the symmetrical difference of set2 and set1 */
void symdiff_set(set *set1, set *set2, set *symdiffSet)
{
	int i;    
	set *temp;
    temp = creatSet();
    for (i = 0; i < numOfBits; i++)
        if ((checkBit(set1, i) && !(checkBit(set2, i))) || (checkBit(set2, i) && !(checkBit(set1, i))))
            updateBits(temp, i);
    memcpy(symdiffSet, temp, numOfBits);
    free(temp);
}

/* the function stops the input from the user */
int stop(void)
{    
	exit(0);
}

/* the function get number pointer to  set (128 bytes), and "turn on" the appropriate bit */

void updateBits (set *s, int num)
{
    s->bitsArray[num/sizeOfByte] |= 128 >> num % sizeOfByte; /* 128 in binary = 10000000 */
}

/* the function get number and pointer to set (128 bytes), and return if in this set the bit that represent the number is on */
int checkBit(set *s, int num)
{
    return (s->bitsArray[num/sizeOfByte] & (128 >> num%sizeOfByte));
}

/* the function create new "zero" sets - that's why we have to use calloc, and not malloc */
set * creatSet ()
{
    set *s = (set *) calloc ( numOfBytes , sizeOfByte);
    if (s == NULL)
    {
        return (NULL);
    }
    return (s);
}




enum possibleMode {command, set1, comma1, set2, comma2, set3, commaRead, newNum, minus1, stopProg}; /* the possible potentially modes to check in the line */
char *nameOfSets[numOfSets]={"SETA", "SETB", "SETC", "SETD", "SETE", "SETF"}; /* names of the potentially sets */
char *nameOfCommands[numOfCommands]={"read_set", "print_set", "union_set", "intersect_set", "sub_set", "symdiff_set", "stop"}; /* names of the potentially commands */

/* the function get number that represent the kind of the problem, and print suitable message */

void problem (int x)
{
    switch (x)
    {
        case 1:
            printf("Undefined set name\n");
            break;
        case 2:
            printf("Undefined command name\n");
            break;
        case 3:
            printf("Invalid set member – value out of range\n");
            break;
        case 4:
            printf("List of set members is not terminated correctly\n");
            break;
        case 5:
            printf("Invalid set member – not an integer\n");
            break;
        case 6:
            printf("Missing parameter\n");
            break;
        case 7:
            printf("Extraneous text after end of command\n");
            break;
        case 8:
            printf("Multiple consecutive commas\n");
            break;
        case 9:
            printf("Missing comma\n");
            break;
        case 10:
            printf("Illegal comma\n");
            break;
    }
}

/* the function get number and return the number of its digits */

int numOfDigits (int num)
{
	int count;    
	if (num == 0) /* the original number is 0 */
        return 1;
	count = 0;    
	while (num > 0)
    {
        count++;
        num = num/10;
    }
    return count;
}

/* the function ger pointer to potentially new number, and return 0 - if the number is invalid,
1/2/3 - valid (num of digit to jump) , or -1 (end of input numbers) and in purpose to move to "mode" minus1 */

int numIsValid (char * ptr)
{
    char * ptr2;
    long int num;
    num = strtol (ptr, &ptr2, 10); /* 10 = base 10 */
    if (num == -1)
    {
        return -1;
    }
    else if (num > 127 || num < 0)
    {
        problem(3);
        return 0; /* the number is invalid - out of range */
    }
    else if (num == 0)
    {
        if ((*ptr) == '0')
        {
            return 1;
        }
        else
        {
            problem (4);    /* we end with no -1 , as we should */
            return 0;
        }
    }
    else /* num is valid */
    {
        return numOfDigits (num);
    }
}

/* the function get pointer to potentially command, and returns 7 if isn't legal, if it's legal it returns the appropriate number of the command. */

int commandIsValid (char * ptr)
{
    int i;
    for (i = 0; i < numOfCommands; i++)
    {
        if (memcmp(ptr, nameOfCommands[i], strlen(nameOfCommands[i])) == 0) /* compare the string that should be a command */
        {
            return i;
        }
    }
    return i; /* the command isn't legal (7)*/
}

/* the function get pointer to potentially name of set , and returns 6 if isn't legal,  if it's legal it returns a number that represent the appropriate set. */

int nameIsValid (char * ptr)
{
    int i;
    for (i = 0; i < numOfSets; i++)
    {
        if (memcmp (ptr, nameOfSets[i], strlen(nameOfSets[i])) == 0) /* compare the string that should be a name of set */
        {
            return i;
        }
    }
    return i; /* the name is not legal (6) */
}

/*  the function get pointer to the start of the new line , and return 1 if the all line is valid, and 0 if not */

int allLineIsValid (char * ptr)
{
    int commandNumber = 0; /* should represent the number of the command if it's valid */
	int setNumber; /* should represent the number of the set if it's valid */
    int number; /* new number , in read_set */
    enum possibleMode mode;
    mode = command;
    while (ptr != NULL)
    {
		while (isspace(*ptr))
        {
            ptr++;
        }
        switch (mode)
        {
            case command:
                commandNumber = commandIsValid(ptr);
				if (commandNumber == 7) /* the command isn't legal */
                {
                    problem(2);
                    return 0; /* the line isn't valid because command */
                }
                else if (commandNumber == 6) /* stop, and pause the all checks */
                {
					ptr = ptr + strlen(nameOfCommands[commandNumber]);                    
					mode = stopProg;
					
                }
                else /* command is valid */
                {
                    ptr = ptr + strlen(nameOfCommands[commandNumber]); /* ptr is moving to the next 'mode' - supposed to be the first set */
                    mode = set1;
                }
				
				continue;
            case set1:
                while(isspace(*ptr))
                {
                    ptr++;
                }
                setNumber = nameIsValid(ptr);
                if ((*ptr) == ',')
                {
                    problem(10);
                    return 0; /* the line isn't valid - illegal comma */
                }
                else if ((*ptr) == '\0')
                {
                    problem(6);
                    return 0; /* the line isn't valid - no more parameter */
                } else
                {
                    if (nameIsValid(ptr) != 6) /* name of the set is valid */
                    {
                        ptr = ptr + strlen(nameOfSets[setNumber]);
                        if (commandNumber == 0 || commandNumber == 1) {
                            if (commandNumber == 0) {
                                mode = commaRead; /* mode that looking dor comma, in case that the command is read_set , and no need for more sets */
                            }
                            else if (commandNumber == 1) /* the command is print, and name of set is valid - we shouldn't need any other input except ' ' */
                            {
                                while ((*ptr) != '\0')
                                {
                                    if (isspace((*ptr)))
                                    {
                                        ptr++;
                                    }
                                    else
                                    {
                                        problem(7);
                                        return 0;
                                    }
                                    return 1;
                                }
                            }
                        }
                        else /* the command is not print or read, and the name of the set is valid */
                        {
                            mode = comma1; /* mode that looking dor comma, when we need to looking dor more to commas and sets. */
                        }
                    } /* name is not valid */
                    else
                    {
                        problem(1);
                        return 0; /* the line isn't valid because name of set */
                    }
                }
                continue;

            case commaRead:
                if ((*ptr) == '\0')
                {
                    problem(4); /* we didn't finish with -1, as we need */
                    return 0;
                }
                if ((*ptr) == ',')
                {
                    ptr++;
                    mode = newNum; /* mode - looking for new num */
                    continue;
                }
                else
                {
                    if ((*ptr) == '.')
                    {
                        ptr++;
                        if (isdigit(*ptr)) /* the number is double xx.xx */
                        {
                            problem(5);
                            return 0;
                        }
                    }
                    else
                    {
                        problem(9); /* should be a comma */
                        return 0;
                    }
                }
			break;
            case newNum:
                if ((*ptr) == ',') /* double commas */
                {
                    problem(8);
                    return 0;
                }
                else if ((*ptr) == '\0')
                {
                    problem(4);
                    return 0;
                }
				else if (((*ptr) < '0' || (*ptr) > '9') && (*ptr) != '-')
                {
                    problem(5);
                    return 0;
                }
                number = numIsValid(ptr);
                if (number == 0)  /* num is not valid */
                {
                    return 0;
                }

                if (number == -1)
                {
                    ptr = ptr + 2; /* 2= two chars , '-' and '1' */
                    mode = minus1;
                }
                else
                {
                    ptr = ptr + number;
                    mode = commaRead;
                }
                continue;

            case minus1:
                if ((*ptr) == '\0')
                {
                    return 1; /* it's the end of line */
                }
                else
                {
                    problem(7); /* there is something after -1 */
                    return 0;
                }

            case comma1:
                if ((*ptr) != ',')  /* missing comma */
                {
                    problem(9);
                    return 0;
                }
                else
                {
                    ptr++;
                    mode = set2; /* mode - looking for the second set */
                }
                continue;

            case set2:
                if ((*ptr) == '\0')
                {
                    problem(6);
                    return 0;
                }
                else if ((*ptr) == ',') /* double comma */
                {
                    problem(8);
                    return 0;
                }
                if (nameIsValid(ptr) == 6) /* name of set is not valid */
                {
                    problem(1);
                    return 0;
                }
                else /* valid */
                {
                    ptr = ptr + strlen(nameOfSets[setNumber]);
                    mode = comma2; /* mode - looking for the second comma */
                    continue;
                }
			break;
            case comma2:
                if ((*ptr) != ',' && (*ptr) == '\0')  /* we end the line without more parameters, like example 10 */
                {
                    problem(6);
                    return 0;
                }
                else if ((*ptr) != ',') /* we are at the end, and we just with no comma */
                {
                    problem(9);
                    return 0;
                }
                else /* valid */
                {
                    ptr++;
                    mode = set3;
                    continue;
                }
            case set3:
                if ((*ptr) == '\0')
                {
                    problem(6);
                    return 0;
                }
                else if ((*ptr) == ',')
                {
                    problem(8);
                    return 0;
                }
                if (nameIsValid(ptr) == 6)
                {
                    problem(1);
                    return 0;
                }
                else
                {
                    ptr = ptr + strlen(nameOfSets[setNumber]);
                    while (((*ptr)) != '\0')
                    {
                        if (isspace(*ptr)) /* run until the end of line */
                        {
                            ptr++;
                            continue;
                        }
                        else
                        {
                            problem(7);
                            return (0);
                        }
                    }
                    return 1; /* valid */
                }
				break;
            case stopProg:                 
				if ((*ptr) != '\0' && (*ptr) != EOF)
                {
					problem(7);
					return (0);
                }
				
                return 1;
				break;
        }
		return 1; 
    }
	return 1;
}

