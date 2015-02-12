#include <fcntl.h> /* File control definitions */
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <limits.h>

#define WD 1000



/**
 * Start the connection to /dev/ttyUSB0
 * TODO: Allow user to specify. Maybe it isn't /dev/ttyUSB0
 */
int startconnection()
{
	int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
	return fd;
}


/**
 * Scans the channels and returns the rssi of the specified SSID
 */
int scanrssi(int fd, char *ssid)
{
	char buf[1000];
	write(fd, "scan 10\r", 8);
	usleep(1000000);
	read(fd, buf, sizeof(buf));
	//printf("buf is:\n%s\n", buf);

	return getrssi(buf, ssid);
}

/**
 * Scans numtimes times and prints rssi values to a line in a file
 */
int scanrssi_f(int fd, char *ssid, FILE *f, int numtimes)
{
	int rssi_value;
	int i;
	for (i = 1; i <= (numtimes-1); i++)
	{
		rssi_value = scanrssi(fd, ssid);
		fprintf(f, "%i,", rssi_value);
		printf("rssi_value = %i\n", rssi_value);
	}

	/* Don't include comma for last one */
	/* TODO: I end with a newline. Should I? */
	rssi_value = scanrssi(fd, ssid);
	fprintf(f, "%i\n", rssi_value);
	printf("rssi_value = %i\n", rssi_value);
}

/**
 * This puts you in command mode
 * Must wait 250 
 */
int commandmode(int fd)
{
	// First, we must make sure we are in command mode
	// For now, let's assume we just booted up
	write(fd, "exit\r", 5);
	usleep(WD);
	write(fd, "exit\r", 5);
	usleep(WD);

	// Give it the turn on command
	/* must wait 250 ms before and after giving $$$ command */
	/* to be safe, i wate 300 ms */
	write(fd, "$$$", 3);
	usleep(300000);
}

/**
 * Parses output from scan command.
 * Searches for SSID provided.
 * Returns the RSSI value of that SSID, as an int.
 */
// TODO: Should this be static?
int getrssi(char *buf, char *ssid)
{
	char *delim = "\n";
	char *token = strtok(buf, delim);
	int rssi_value = INT_MAX;

	while (token)
	{
		if (strstr(token, ssid) != NULL)
		{
			char *comma_delim = ",";
			char *jam_token = strtok(token, comma_delim);
			jam_token =	strtok(0, comma_delim);
			jam_token =	strtok(0, comma_delim);
			rssi_value = atoi(jam_token);
			token = NULL;
		}
		else
		{
			token = strtok(0, delim);
		}
	}

	return rssi_value;
}
