#include <stdio.h>
#include "sgtty.h"

#if CPM
#include <unixio.h>
#endif

extern int  ttopen(char *);			// Open tty
extern void ttbin(int, struct sgttyb *);	// Set tty
extern void ttres(int, struct sgttyb *);	// Restore controlling tty's modes
extern void setspd(struct sgttyb *);		// Set speed

extern int turn, speed;

/*
 * Open tty
 */
int ttopen(char *tn) {
    int fd;

    if (tn == 0) return(0);
    if ((fd = open(tn, 2)) < 0) {
	printmsg("Cannot open %s",tn);
	exit(1);
    }
    return(fd);
}

/*
 * Set tty
 */
void ttbin(int fd, struct sgttyb *old) {
    struct sgttyb new;

    gtty(fd, old);			/* Save current mode so we can */
    gtty(fd, &new);			/* restore it later */
    new.sg_flags |= (RAW);
    if (!turn) new.sg_flags |= TANDEM;	/* use xon/xoff if no handshaking */
    new.sg_flags &= ~(ECHO|CRMOD);
    if (fd != 0) setspd(&new);		/* Speed if requested and supported */
    stty(fd, &new);			/* Put tty in raw mode */
}

/*
 * Restore controlling tty's modes
 */
void ttres(int fd, struct sgttyb *old) {

    sleep(1);				/* wait before releasing the line */
    stty(fd, old);
}

/*
 * Set speed
 */
void setspd(struct sgttyb *tty) {
    int spbits;

    if (speed) {			/* User specified a speed? */
	switch(speed) {			/* Get internal system code */
	    case 110:  spbits = B110; break;
	    case 150:  spbits = B150; break;
	    case 300:  spbits = B300; break;
	    case 1200: spbits = B1200; break;
	    case 1800: spbits = B1800; break;
	    case 2400: spbits = B2400; break;
	    case 4800: spbits = B4800; break;
	    case 9600: spbits = B9600; break; 

	    default:   printmsg("Bad line spbits.");
		       exit(1);
	}
	tty->sg_ispeed = spbits;
	tty->sg_ospeed = spbits;
    }
}
