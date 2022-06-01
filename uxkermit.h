/*
 *  K e r m i t	 File Transfer Utility
 *
 *  UNIX Kermit, Columbia University, 1981, 1982, 1983, 1984
 *	Bill Catchings, Bob Cattani, Chris Maio, Frank da Cruz,
 *	Alan Crosswell, Jeff Damens
 *
 * file uxkermit.h
 */

#include "sgtty.h"

/* Conditional compilation for different machines/operating systems */
/* One and only one of the following lines should be 1 */

#define UZI180	    1	    /* UZI180 UNIX */
#define UCB4X	    0	    /* Berkeley 4.x UNIX */
#define TOPS_20	    0	    /* TOPS-20 */
#define IBM_UTS	    0	    /* Amdahl UTS on IBM systems */
#define VAX_VMS	    0	    /* VAX/VMS */

/* Conditional compilation for the different Unix variants */
/* 0 means don't compile it, nonzero means do */

#if UZI180
#define V6_LIBS	    0	    /* Don't use retrofit libraries */
#define NO_FIONREAD 0	    /* No ioctl(FIONREAD,...) for flushinput() */
#define NO_TANDEM   0	    /* No TANDEM line discipline (xon/xoff) */
#endif

#if UCB4X
#define V6_LIBS	    0	    /* Dont't use retrofit libraries */
#define NO_FIONREAD 0	    /* We have ioctl(FIONREAD,...) for flushinput() */
#define NO_TANDEM   0	    /* We have TANDEM line discipline (xon/xoff) */
#endif

#if IBM_UTS
#define V6_LIBS	    0	    /* Don't use retrofit libraries */
#define NO_FIONREAD 1	    /* No ioctl(FIONREAD,...) for flushinput() */
#define NO_TANDEM   1	    /* No TANDEM line discipline (xon/xoff) */
#endif

#if TOPS_20
#define V6_LIBS	    0	    /* Don't use retrofit libraries */
#define NO_FIONREAD 1	    /* No ioctl(FIONREAD,...) for flushinput() */
#define NO_TANDEM   1	    /* No TANDEM line discipline (xon/xoff) */
#endif

#if VAX_VMS
#define V6_LIBS	    0	    /* Don't use retrofit libraries */
#define NO_FIONREAD 1	    /* No ioctl(FIONREAD,...) for flushinput() */
#define NO_TANDEM   1	    /* No TANDEM line discipline (xon/xoff) */
#endif

// File uxkermit.c
extern int  main(int, char **);
extern char sendsw();				// Sendsw is the state table switcher for sending files
extern char sinit();				// Send Initiate
extern char sfile();				// Send File Header
extern char sdata();				// Send File Data
extern char seof();				// Send End-Of-File
extern char sbreak();				// Send Break (EOT)
extern int  recsw();				// State table switcher for receiving files
extern char rinit();				// Receive Initialization
extern char rfile();				// Receive File Header
extern char rdata();				// Receive Data
extern char dopar(char);			// Send the character
extern int  clkint();				// Timer interrupt handler
extern void spack(char, int, int, char *);	// Send a Packet
extern char rpack(int *, int *, char *);	// Read a Packet
extern char cinchr();				// Get a parity adjusted character from the line
extern char inchr();				// Get a character from the line
extern int  bufill(char buffer[]);		// Get a bufferful of data from the file that's being sent
extern void bufemp(char  buffer[], int);	// Put data from an incoming packet into a file
extern char gnxtfl();				// Get next file in a file group
extern void spar(char data[]);			// Fill the data array with my send-init parameters
extern void rpar(char data[]);			// Get the other host's send-init parameters
extern void flushinput();			// Dump all pending input to clear stacked up NACK's
extern void usage();				// Print summary of usage info and quit
extern void printmsg();				// Print message on standard output if not remote.
extern void error();				// Print error message
extern void prerrpkt(char *);			// Print contents of error packet received from remote host

// File uxkonu.c				// for "standard" unix
extern void connect();				// Establish a virtual terminal connection with the remote host

// File unxkerunx.c
extern int  ttopen(char *);			// Open tty
extern void ttbin(int, struct sgttyb *);	// Set tty
extern void ttres(int, struct sgttyb *);	// Restore controlling tty's modes
extern void setspd(struct sgttyb *);		// Set speed

// End file uxkermit.h

