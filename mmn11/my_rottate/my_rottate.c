/* 
Submitted by : Efrat Friedrich 
This program get a number x and performs a rotation of n bits on parameter a.
Rotates to the right When a>o, and to the left if a<0. 
For example:
The representation of input in binary is:1010111011111011
for n=3 the output is: 		         0111010111011111
for n=-3 the output is:                  0111011111011101

It's print the input and output representation in base 16,10,8,2
*/

#include <stdio.h>

unsigned int my_rottate(unsigned int , int );
void printBin(int );             


int main(void) {
	int x, n;
	printf("Enter x - to be rotated (integer):\n");
	scanf("%d", &x);
	printf("Enter n - the number of bits to rotate (integer):\n");
	scanf("%d", &n); 


	printf("\nx before rotate:\n");
	printf(" base 2:");
	printBin(x);
	printf(" base 16 unsigned: %x\n base 10: %u\n base 8 unsigned: %o\n", x,x,x);

	printf("\nNumber of bits to rotate: %d\n",n);


	printf("\nx after rotate:\n");
	printf(" base 2:");
	printBin(my_rottate(x,n));
	printf(" base 16 unsigned: %x\n base 10: %d\n base 8 unsigned: %o\n", my_rottate(x,n),my_rottate(x,n),my_rottate(x,n));
	return 0;
}


unsigned int my_rottate(unsigned int x, int n){
/* This function performs a rotation of n bits on a number.*/
	if(n>0) {
	/*when n>0: Check the x's right bit.
	when right bit=1- set the left bit to 1 by using (x OR 10...0).
	when right bit=0- move bits one step right.*/
		while (n > 0) {
			if ((x & 1) == 1)	
				x = (x >> 1) | ~(~0U >> 1);
			else			
				x = (x >> 1);
			n--;
		}
	}

	else {
        /*when n<0: Check the left bit.
	when left bit=1- set the right bit to 1 by (x OR 00...01).
	when left bit=0, move bits one step left.*/
		while (-n > 0) {
			if ((x & (~(~0U >> 1))) == 1)	
				x = (x << 1) | 1;
			else			
				x = (x << 1);
			n++;
		}
	}
	return x;
}    

void printBin(int a){
/* This function prints binary representation of a number */

/*
   	set initial mask to 10000...0000 in order to 
   	check left bit. Then print 1 or 0 bit accordigly.
   	Update mask by moving one step to right until mask=0 and Check again.
*/

	unsigned int mask= 1<< (8*sizeof(int)-1); 
	
	while(mask){		
		if((a&mask)==0)
			printf("0");
		else 
			printf("1");
		mask>>=1;	
	}
	printf("\n");
}
