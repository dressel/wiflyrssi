#include <fcntl.h> /* File control definitions */
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "serialwifly.h"

/**
 * 1 argument:  Degree at which only antenna is measured
 * 2 arguments: 1st is number of antennas (1 or 2), 2nd is degree
 *
 * Examples:
 *  ./a.out => Measures output of a single antenna
 *  ./a.out 20 => Measures output of a single antenna at 20 degrees
 *  ./a.out 2 20 => Measures output of two antennas at 20 degrees
 */
int main(int argc, char *argv[])
{
	/* Specify the degree */
	int degree;
	if (argc == 1)
	{
		degree = 0;
		scan1(degree, "JAMMER01", 10, "wifly.csv");
	}
	else if(argc == 2)
	{
		degree = atoi(argv[1]);
		scan1(degree, "JAMMER01", 10, "wifly.csv");

	}
	else if(argc == 3)
	{
		degree = atoi(argv[2]);
		if (atoi(argv[1]) == 1)
			scan1(degree, "JAMMER01", 10, "wifly.csv");
		else if (atoi(argv[1]) == 2)
			scan2(degree, "JAMMER01", 10, "wifly1.csv", "wifly2.csv");
		else
		{
			printf("Only supports one or two wifly modules at the moment.\n");
			printf("value is : %s\n", argv[1]);
			return 0;
		}
	}
	else
	{
		printf("Invalid number of parameters entered.\n");
		return 0;
	}
}
