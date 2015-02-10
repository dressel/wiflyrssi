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
int main()
{
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

	/* Tell it to scan */
	/*
	int i;
	int rssi_value;
	for (i = 1; i <= 10; i++)
	{
		rssi_value = scanrssi(fd, "JAMMER01");
		printf("rssi value = %i\n", rssi_value);
	}
	*/

	//scanrssi10(fd, "JAMMER01");

	/* Some file I/O */
	FILE *f = fopen("rar.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file\n");
		return 0;
	}
	//fprintf(f, "ha!\n");
	scanrssi_f(fd, "JAMMER01", f, 10);
	fclose(f);

	/* Be sure to close the output */
	close(fd);
}

/* Writes a new line */
int scanrssi_f(int fd, char *ssid, FILE *f, int numtimes)
{
	int rssi_value;
	int i;
	for (i = 1; i <= numtimes; i++)
	{
		rssi_value = scanrssi(fd, ssid);
		fprintf(f, "%i,", rssi_value);
	}
	fprintf(f, "\n");
}
