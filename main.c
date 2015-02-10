#include <fcntl.h> /* File control definitions */
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <limits.h>

#include "serialwifly.h"

#define WD 1000

/* Main function */
int main(int argc, char *argv[])
{
	/* Specify the degree */
	int degree = 0;
	if (argc == 2)
	{
		//printf("arg is: %s\n", argv[1]);
		degree = atoi(argv[1]);
	}

	/* Start the connection to the WiFly */
	/* If the connection does not exist, quit */
	int fd = startconnection();
	if (fd < 0)
	{
		printf("Error connecting to wifly. Exiting...\n");
		return 0;
	}

	/* Go into command mode */
	commandmode(fd);

	/* Open a file to write values to */
	/* Appending values */
	FILE *f = fopen("wiflytest.csv", "a");
	if (f == NULL)
	{
		printf("Error opening file\n");
		return 0;
	}

	/* Scan values to this file */
	/* Add degree at which you measure first */
	fprintf(f, "%i,", degree);
	scanrssi_f(fd, "JAMMER01", f, 10);

	/* Be sure to close the output file and connection */
	fclose(f);
	close(fd);
}
