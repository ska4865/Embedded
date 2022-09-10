// in-class exercise 1
// Version 1 - Larry Kiser RIT June 2021
// Version 2 - Mitesh Parikh RIT Aug 2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Objective -- explore data types & bitwise operation.
//Submit to in-class 1 activity folder by due date in myCourses.

int main( int arg_count, char *arg_list[] )
{
	int result = 0 ;		// default to success

	return result ;
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