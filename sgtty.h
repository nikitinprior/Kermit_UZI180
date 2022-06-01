/*
 *	UZI280   sgtty.h
 */

#define TIOCGETP  0	/* Get a terminal's parameters */
#define TIOCSETP  1
#define TIOCSETN  2	/* get number of available chars */
#define FIONREAD  2	/*  "  " */
/**
#define TIOCEXCL  3	// currently not implemented  SN
**/
/*
 *	UZI280 specific
 */
#define UARTSLOW  4	/* normal UART interrupt routine with ctrl char check */
#define UARTFAST  5	/* fast routine for modem/kermit usage */

#define TIOCFLUSH 6 	/* flush the input stream */
#define TIOCGETC  7	/* get control chars */
#define TIOCSETC  8	/* set   " */
/*
 *	UZI280 extensions used by UZI180 in the CP/M 2.2 Emulator
 */
#define TIOCTLSET 9	/* only used for CPM- */
#define TIOCTLRES 10    /* emulator */

#define XTABS	0006000	/* do tab expansion */
#define RAW	0000040	/* enable raw mode */
#define CRMOD   0000020	/* map lf to cr + lf */
#define CRLF	0000020
#define ECHO	0000010	/* echo input */
#define LCASE	0000004
#define CBREAK	0000002	/* enable cbreak mode */
#define COOKED  0000000	/* neither CBREAK nor RAW */

#define TANDEM  COOKED  /* make kermit happy */

/*
 *	In the UZI-180 operating system, members of the tchars structure 
 *	are members of the sgttyb structure.
 */

struct sgttyb {
    char sg_ispeed,	/* input speed */
	 sg_ospeed;	/* output speed */
    char sg_erase,	/* erase character */
	 sg_kill;	/* kill character */
    int  sg_flags;	/* mode flags */

    char t_intr;	/* SIGINT char */
    char t_quit;	/* SIGQUIT char */
    char t_start;	/* start output (initially CTRL-Q) */
    char t_stop;	/* stop output	(initially CTRL-S) */
    char t_eof;		/* EOF (initially CTRL-D) */

    char ctl_char;
};

struct tchars {
    char t_intrc,	/* SIGINT char */
	 t_quit,	/* SIGQUIT char */
	 t_start,	/* start output (initially CTRL-Q) */
	 t_stop,	/* stop output	(initially CTRL-S) */
	 t_eof;		/* EOF (initially CTRL-D) */
};

#define t_quitc	t_quit
#define t_startc t_start
#define t_stopc	t_stop
#define t_eofc	t_eof

#ifdef _ANSI
_PROTOTYPE(int ioctl, (int fd, int mode, int *));
#endif

#define stty( fd, s)	(ioctl(fd, TIOCSETP, s))
#define gtty( fd, s)	(ioctl(fd, TIOCGETP, s))

/*  serial line setting is not yet implemented in UZI280
    only to make programs happy */

#define BITS8        0001400	/* 8 bits/char */
#define BITS7        0001000	/* 7 bits/char */
#define BITS6        0000400	/* 6 bits/char */
#define BITS5        0000000	/* 5 bits/char */
#define EVENP        0000200	/* even parity */
#define ODDP         0000100	/* odd parity */

#define DCD          0100000	/* Data Carrier Detect */

/* Line speeds */
#define B0		   0	/* code for line-hangup */
#define B110		   1
#define B134		   2
#define B300		   3
#define B1200		  12
#define B2400		  24
#define B4800		  48
#define B9600 		  96
#define B19200		 127

/* Things Minix supports but not properly */
/* the divide-by-100 encoding ain't too hot */
#define ANYP         0000300
#define B150               0
#define B200               2
#define B600               6
#define B1800             18
#define B3600             36
#define B7200             72
#define EXTA             192
#define EXTB               0

/* Things Minix doesn't support but are fairly harmless if used */
#define NLDELAY      0001400
#define TBDELAY      0006000
#define CRDELAY      0030000
#define VTDELAY      0040000
#define BSDELAY      0100000
#define ALLDELAY     0177400

