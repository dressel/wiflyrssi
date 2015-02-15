
/* Function to start connection */
int startconnection();

/* Ensure that you are in command mode */
int commandmode(int);

/* Scan the channels for a specific SSID */
int scanrssi(int, char *);
int scanrssi_f(int fd, char *ssid, FILE *f, int numtimes);

/* Parses output from scan  */
int getrssi(char *, char *);

/* Higher level scan functions that the user might interact with */
int scan1(int, char *, int, char *);
int scan2(int, char *, int, char *, char *);
