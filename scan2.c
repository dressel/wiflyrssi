#include <fcntl.h> /* File control definitions */
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "serialwifly.h"

/* Main function for scanning with two antennas */
/* Makes 10 measurements and appends them to a specified file */
int scan2(int degree, char *ssid, int numtimes, char *f1_name, char *f2_name)
{
	/* Start the connection to the WiFly */
	/* If the connection does not exist, quit */
	int fd1 = connect0();
	if (fd1 < 0)
	{
		printf("Error connecting to first wifly. Exiting...\n");
		return 0;
	}

	/* Start the connection to the WiFly */
	/* If the connection does not exist, quit */
	int fd2 = connect1();
	if (fd2 < 0)
	{
		printf("Error connecting to second wifly. Exiting...\n");
		close(fd1);
		return 0;
	}

	/* Go into command mode */
	commandmode(fd1);
	commandmode(fd2);

	/* Open the first output file*/
	/* Appending values */
	FILE *f1 = fopen(f1_name, "a");
	if (f1 == NULL)
	{
		printf("Error opening first output file\n");
		return 0;
	}

	/* Open the second output file */
	/* Appending values */
	FILE *f2 = fopen(f2_name, "a");
	if (f2 == NULL)
	{
		printf("Error opening second output file\n");
		close(fd1);
		close(fd2);
		fclose(f1);
		return 0;
	}

	/* Scan values to this file */
	/* Add degree at which you measure first */
	fprintf(f1, "%i,", degree);
	fprintf(f2, "%i,", degree);
	scanrssi_2(fd1, fd2, ssid, f1, f2, numtimes);

	/* Be sure to close the output files and connections */
	fclose(f1);
	fclose(f2);
	close(fd1);
	close(fd2);
}
