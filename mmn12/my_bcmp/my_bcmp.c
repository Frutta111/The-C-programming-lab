/* Submitted by : Efrat Friedrich  */

/*
The program compares two segments in memory that are equal in size and returns a message whether they contain identical content.
The program receives as input 4 arguments: three positive integers and a string of a maximum size of 512 characters. 
The order of input must be:
 1) Number of bytes to compare (block size)
 2) First index that will point to a location in memory
 3) Second index that will point to a location in memory 
 4) String that will be the segment of the memory on which the program will work with.

Main function of my_bcmp:
A) Gets and validate type of user-input
	method: get input using getchar() as a string and validate type 		     		simultaneously. Allows multiple white characters between arguments.
	Validates value of inputs after argumets are received.
	If the input is incorrect - the program stops and issue an error message.
C) Prints user-input 
D) Calls my_bcmp to perform the comparison and return value. Returns 0 if the memory segments contain identical content. Otherwise, returns the difference between the first non-identical characters. 
E) Prints results
*/

#include <stdio.h>
#include <stdlib.h> /*for atoi()*/
#include <ctype.h>
#include <string.h>

#define MAXNUM 100    /* max size of a number from input */
#define MAXSTR 513    /* max size of string to work on */

int getnumber(char []);   /* gets a number form user using getchar */
void getstring(char []);  /* gets a string form user using getchar */
void fatal_error(int  , int  , int , char []); /*checks if input value*/
void print_substr(char [], int , int ); /*prints substring */
int my_bcmp(const void *, const void *, int ); /*compares two segments in memory*/

int main()
{
	/* variables for getting user-input */
	char sn[MAXNUM]; /*string for function getnumber*/
 	char sw[MAXSTR]; /*string for function getstring*/
	int  len, ind1, ind2;
	char *p1 , *p2;

	printf("Enter as follows: number of bytes to compare, index to pointer 1, index to pointer 2, a string to work with a maximum size of 512 characters. Use white characters to separate the variables.\n\n"); 
	
 	/*read input*/
	len=getnumber(sn);	/*user input: number of bytes to be compared*/	
	ind1=getnumber(sn);  /*user input: first index pointer to a memory block */
	ind2=getnumber(sn);  /*user input: secound index pointer to a memory block*/
		
	getstring(sw); /*memory area to work with*/
	
	/*Validation check of the input values*/
	fatal_error(ind1,ind2,len,sw);

	
	/*print input on screen*/
	printf("-------The inputs are:--------------------------------------------\n"); 
	printf("  Index1 points to: %d and index2 points to: %d\n" ,ind1, ind2);
   printf("  Number of bytes to be compared is: %d\n" , len);
   printf("  Memory segments contains the string: \n%s" , sw);
   
   printf("\n-------The segments to be compared are:----------------------------\n"); 
   print_substr(sw, ind1, len);  
   print_substr(sw, ind2, len);
   
   /*print the results of my_bcmp*/
   printf("\n-------The result is:-------------------------------------------\n"); 
	p1=sw+ind1;
	p2=sw+ind2;
	
	printf("my_bcmp return value = %d \n",my_bcmp(p1, p2, len));
	printf("memcmp return value = %d \n",my_bcmp(p1, p2, len));
		
	if(my_bcmp(p1, p2, len)==0)
		printf("segments are equal \n");
	else 
		printf("segments are unequal \n");

	return(0);
}


/* getnumber: gets a number form user using getchar */
int getnumber(char s[])
{
 	int i=0, c, number;
 	
 	while ((c = getchar()) == ' ' || c == '\t' || c=='\n')
 	;
 	
 	if (!isdigit(c)) /* not a number */
 		{
 			printf("error: input must contains three integers and one string\n");
 			exit(0); 
 		}
 		
 	s[i++] = c;
 	
 	if (isdigit(c)) /* collect integer part */
 		while (isdigit(s[i++] = c = getchar()))
 		;
 
	s[--i] = '\0';
	
	if (c != ' ' && c != '\t' && c !='\n') /* not a number */
 		{
 			printf("error: user-input must contains three integers and one string\n");
 			exit(0); 
 		}	 
	 
	number=atoi(s);
	return number;
}

/* getstring: gets a string form user using getchar */
void getstring(char s[])
{
	int i=0, c;
	while ((c = getchar()) == ' ' || c == '\t' || c=='\n')
 	;

	while((c=getchar()) !=EOF)
	{
		s[i] = c;
		i++;
	}
	s[i] = '\0';
}

/* fatal_error: checks input value.If out-of-range then print a message and exit  */
void fatal_error(int index1 , int index2 , int bytenum, char s[])
{
	int l ;
	l=strlen(s);
	
	if (index1 > l) {
			printf("invalid input: index1 is grater than string size\n");
			exit(0);
		} 
		
	if (index2 > l) {
			printf("invalid input: index2 is grater than string size\n");
			exit(0);
		} 	
		
	if ((index1+bytenum) > l) {	
			printf("invalid input: size to be compared is greater than string size\n");
			exit(0);
		} 	

	if ((index2+bytenum) > l) {	
			printf("invalid input: size to be compared is greater than string size");
			exit(0);
		} 		
}

/*print_substr: prints a substring of s[] starting at index p of length l bytes */   
void print_substr(char s[], int p, int l)
{
   int i = 0;
   char c;
   
   while (i < l) 
   {
   	c=s[p+i];
      putchar(c);
      i++;
   }
   puts("\n");
}

/*my_bcmp: compares two segments in memory 
  len <- segmetns size.  *b1 and *b2 <- pointers to segments
  if equal - returns 0. 
  if unequal - returns the difference of the first unequal character */
int my_bcmp(const void *b1, const void *b2, int len)
{
	int i =0 , cmp=0;
	char *q1=(char *)b1;
	char *q2=(char *)b2;
	
	while (cmp==0 && i < len)
	{
		cmp=q1[i]-q2[i];
		/*printf("q1=%c , q2=%c ,cmp=%d\n",q1[i],q2[i],cmp);*/
		i++;
	}
	return(cmp);
}


