/*
* this is a new world
* Assignment: add a program to the svn
* Name of programer: Alexandra Elson
* WSU ID: W964T632
* hello this is line 3 // today has been a long day
>>>>>>> .r4
* Description: This program implements the Collatz Conjecture for any positive integer under 500,000.
* 		If the integer is even, then it will be divided by 2, and if the integer is odd,
* 		it will be multiplied by 3 and added to 1. Using this method, the sequence should
*		eventually converge to 1.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char *argv[])
{
	int input, counter=0;							//the input converted to an integer, and a counter
	pid_t pid;								//the pid for the fork call

	if(argc != 2)								//There are not enough arguments
	{
		printf("%s <integer value>\n", argv[0]);
		return 1;
	}

	input = atoi(argv[1]);							//converting the input into an integer

	if(input < 0)								//The user tried to input a negative number
	{
		printf("The integer must be positive.\n");
		return 1;
	}
	if(input > 500000)							//The user tried to input a number greater than the max
	{
		printf("The integer must be less than 500,000.\n");
		return 1;
	}

	pid = fork();

	if(pid<0) 								//An error has occurred
	{
		fprintf(stderr, "Fork Failed\n");
		return 1;
	}


	else if(pid == 0)							//The child process
	{
		printf("\n%d, ", input);
		counter++;

		while(input != 1)
		{
			if((input%2) == 0)					//if the input is even
			{
				input = input/2;
				if (counter != 10)				//if there are not ten numbers listed on the row
				{
					if(input ==1)
					{
						printf("%d\n\n", input);
					}
					else
					{
						printf("%d, ", input);
						counter++;
					}
				}
				else if(counter == 10)				//if there are ten numbers listed on the row
				{
					if(input == 1)
					{
						printf("\n%d\n\n", input);
					}
					else
					{
						printf("\n%d, ", input);
						counter = 0;
					}
				}
			}

			else							//if the input is odd
			{
				input = 3*input +1;

				if(counter != 10)				//if there are not ten numbers listed on the row
				{
					printf("%d, ", input);
					counter++;
				}

				else if(counter == 10)				//if there are ten numbers listed on the row
				{
					printf("\n%d, ", input);
					counter = 0;
                               	}

			}
		}
	}

	else									//The parent process
	{
		wait(NULL);
	}

	return 0;
}
