#include "string.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, const char *argv[])
{
	int i;
	char serial[7] = { '8', '6', '7', '5', '3', '0', '9' };
	if (argc == 1 || strlen(argv[1]) < 7)
	{
		printf("You have to input as a command line argument a serial number with 7 char.\n\n");
		exit(1);
	}
	
	for (i = 0; i < 7; ++i)
	{
		int p = 0;
		int t = sizeof(argv) * 100000; // prevents compile time loop optimization. 
		for (int i = 0; i<t; i++)
		{ // waste some time
			p = t + i*strlen(argv[0]) - strlen(argv[1]); // prevents more optimization... Which wastes a bit of time.  
		}

		if (argv[1][i] != serial[i])
		{
			printf("\nSerial number is incorrect!\n\n");
			exit(1);
		}
	}
	if (i == 7)
	{
		printf("\nSerial number is correct!\n\n");
		exit(0);
	}
}