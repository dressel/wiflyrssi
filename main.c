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
 * 3 arguments: 1st is num antennas, 2nd is number of samples, 3rd is degree
 *
 * Examples:
 *  ./a.out => Measures gain of a single antenna
 *  ./a.out 20 => Measures gain of a single antenna at 20 degrees
 *  ./a.out 2 20 => Measures gain of two antennas at 20 degrees
 *  ./a.out 2 10 20 => Measure gain of two antennas at 20 deg, 10 times each
 */
int main(int argc, char *argv[])
{

	/* Set default values for degree, number of samples, and ssid to search */
	int degree = 0;
	int num_samples = 10;
	char *ssid = "JAMMER01";

	/* Check the argument combinations */
	if (argc == 1)
	{
		scan1(degree, ssid, num_samples, "wifly.csv");
	}
	else if (argc == 2)
	{
		degree = atoi(argv[1]);
		scan1(degree, ssid, num_samples, "wifly.csv");

	}
	else if (argc == 3)
	{
		degree = atoi(argv[2]);
		if (atoi(argv[1]) == 1)
			scan1(degree, ssid, num_samples, "wifly.csv");
		else if (atoi(argv[1]) == 2)
			scan2(degree, ssid, num_samples, "wifly1.csv", "wifly2.csv");
		else
		{
			printf("Only supports one or two wifly modules at the moment.\n");
			printf("value is : %s\n", argv[1]);
			return 0;
		}
	}
	else if (argc == 4)
	{
		num_samples = atoi(argv[2]);
		degree = atoi(argv[3]);
		if (atoi(argv[1]) == 1)
			scan1(degree, ssid, num_samples, "wifly.csv");
		else if (atoi(argv[1]) == 2)
			scan2(degree, ssid, num_samples, "wifly1.csv", "wifly2.csv");
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
