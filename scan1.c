#include <fcntl.h> /* File control definitions */
#include <errno.h>
#include <termios.h>
//#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "serialwifly.h"

/* Main function for scanning with a single antenna */
/* Makes 10 measurements and appends them to a specified file */
int scan1(int degree, char *ssid, int numtimes, char *f1_name)
{
	/* Start the connection to the WiFly */
	/* If the connection does not exist, quit */
	/* This is assuming we want to connect to /dev/ttyUSB0 */
	/* TODO: Don't make that assumption */
	int fd = connect0();
	if (fd < 0)
	{
		printf("Error connecting to wifly. Exiting...\n");
		return 0;
	}

	/* Go into command mode */
	commandmode(fd);

	/* Open a file to write values to */
	/* Appending values */
	FILE *f = fopen(f1_name, "a");
	if (f == NULL)
	{
		printf("Error opening output file\n");
		return 0;
	}

	/* Scan values to this file */
	/* Add degree at which you measure first */
	fprintf(f, "%i,", degree);
	scanrssi_f(fd, ssid, f, numtimes);

	/* Be sure to close the output file and connection */
	fclose(f);
	close(fd);
}
