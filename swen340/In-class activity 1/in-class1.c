// in-class exercise 1
// Version 1 - Larry Kiser RIT June 2021
// Version 2 - Mitesh Parikh RIT Aug 2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bin_prnt_byte(int x_byte);
void bin_prnt_int(int x_word);

	//Objective -- explore data types & bitwise operation.
	//Submit to in-class 1 activity folder by due date in myCourses.

int main(int arg_count, char *arg_list[])
{
	int result = 0 ;		// default to success
	unsigned char q1 = 73;
	signed char q2 = -5;
	unsigned char q3 = 0b11010110;
	unsigned char a = 26; // 0x011010
	unsigned char b = 55; // 0x110111
	char c = 0;

	//Activity #1 - print q1 in binary and hexadecimal
	printf("Binary - >");
	bin_prnt_byte(q1);
	printf("\nHexadecimal - > 0x%x\n", q1);

	//Activity #2 - print q2 in binary and hexadecimal
	printf("Binary - > ");
	bin_prnt_byte(q2);
	printf("\nHexadecimal - > 0x%x\n", q2);

	//Activity #3 - print q3 in decimal and hexadecimal
	printf("Decimal - > %d", q3);
	printf("\nHexadecimal - > 0x%x\n", q3);

	//Activity #4 - c = a & b;
	c = a & b; // 0x010010
	printf("a & b = 0x%x dec - %d\n", c, c);
	//c = a | b;
	c = a | b; // 0x111111
	printf("a | b = 0x%x dec - %d\n", c, c);
	//c = a ^ b;
	c = a ^ b; // 0x101101
	printf("a ^ b = 0x%x dec - %d\n", c, c);
	//c = ~a 
	printf("~a = 0x%x dec - %d\n", ~a, ~a);
	//c = a << 2
	c = a << 2;
	printf("a << 2 = 0x%x dec - %d\n", c, c);
	//c = a >> 2
	c = a >> 2;
	printf("a >> 2 = 0x%x dec - %d\n", c, c);

	//Activty #5
	//solution is q3 & 0x80
	//or q3 & (1 << 7)
	if(q3 >> 7){
		printf("Top bit is set\n");
	}
	else {
		printf("Top bit is not set\n");
	}

	return result;
}


// Functions to print Binary
void bin_prnt_int(int x_word)
{
	int hi_byte;
	int lo_byte;

	// for top Byte.. shift right and logical AND 
	hi_byte = (x_word >> 8) & 0x00FF;
	// for low Byte .. just AND with 0x00FF
	lo_byte = x_word & 0x00FF;

	// Print hi-byte
	bin_prnt_byte(hi_byte);
	printf(" ");
	
	// Print lo-byte
	bin_prnt_byte(lo_byte);
}

void bin_prnt_byte(int x_byte)
{
	int n;
	// Print Byte (8 bits)
	for(n=0; n<8; n++)
	{
		if((x_byte & 0x80) !=0)
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
		if (n==3)
		{
			//insert a space between nibbles
			printf(" "); 
		}
		x_byte = x_byte << 1;
	}
}
