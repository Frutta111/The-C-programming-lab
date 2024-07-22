/*
Submitted by : Efrat Friedrich

This program gets a string (maximum size 80) and returns it short. 
It repalces ascending sequence of 3 or more letters of A-Z and a-z  
and shortens the string.

for example:
input:  dabcefLMNOpQrstuv567zyx
output: da-cefL-OpQr-v567zyx
*/ 

#include <stdio.h>
#include <string.h>

#define SIZE 80 
#define asciiRng(FROM,TO)((str1[i]>FROM && str1[i]<=TO)) 

void shrink(char str1[]);

int main() {
     	     char str1[SIZE];
	     printf("\nEnter a string to be shortened (up to %d chars):\n", SIZE);
	     fgets(str1, SIZE+1, stdin);
	     printf("\nThe original string is:\n%s\n", str1);
	     shrink(str1);
	     printf("\nThe shortend string is:\n%s\n", str1);
return 0;
}


void shrink(char str1[]) {
	int i=1;          
	int j;
	int k;
	int counter;

	while (str1[i] != '\0') {

		j=i;
		counter=0;
	
		/* check if current char is a letter in ascending sequence and counts sequance size -1*/
		while((asciiRng(65,90) || asciiRng(97,122)) && str1[i]-str1[i-1]==1) {
			counter++;
			i++;
		}
		/* shorts the sequance and copy the rest of the string */
		if(counter>=2) {
     			str1[j]='-';
			k=i-1;   /*points to the last char that has been checked in the LONG (old) string*/
			i=j+1;   /*points to the last char that has been checked in the SHORT (new) string*/
 
	       		/* copy the rest of the string to its new place */
			while (str1[k] != '\0') {
				str1[j+1] = str1[k];
				++j;
				++k;
			}
			str1[j+1] = '\0';	
		}	
		i++;
	}

}

