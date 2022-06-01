# Kermit_UZI180

kermit program in UZI180
------------------------

Sharing files between MacBook and P112 computers running the UZI180 operating system is complicated and very inconvenient. The traditional method requires placing the file for the UZI180 from the MacBook onto the CP/M floppy disk. Boot into CP/M on the P112 microcomputer and use the ucp utility to transfer this file to a UZI180 floppy on the second drive. This procedure requires many steps.

It is more convenient to exchange files using the Kermit protocol.

For my MacBook's RS-232 interface, I use TRENDnet TU-59 Serial-to-USB adapters, which OS X defines as:

	Product ID: 0x2303
	Manufacturer ID: 0x067b (Prolific Technology, Inc.)
	Version: 4.00

The latest versions of Mac OS have drivers that support these devices. When adapters are connected, tty devices appear with the names /dev/cu.usbserial-120 and /dev/cu.usbserial-130 respectively.


Adaptation of the kermit v3 program
-----------------------------------

The source code for the kermit program was adapted for UZI180 from the original UNIX Kermit version 3.0(1) code on 11/5/84.

Machine definitions and function prototypes are moved to a separate uxkermit.h file.
The definition of the new operating system has been added to the text of the program

	#define UZI180	1

The definitions of other machines (or operating systems) are set to 0. Depending on the machine type definition, the rest of the conditional compilation options are set.
An include file statement has been added to the program text

	#include "sgtty.h"

and ANSI-style function prototypes. The format of function definitions in the uxkermit.c, uxconu.c, and uxkerunx.c files has been changed accordingly. 
 
The rest of the source code of the program remained virtually unchanged. The list of files required for compilation is as follows:
	unix.h		include files from UZI180;
	sgtty.h
	uxkermit.h	new include file;
	uxkermit.c	kermit program functions;
	uxconu.c	connect command function for "standard" unix;
	uxkerunx.c	functions for interacting with tty lines for "standard" unix;
	sleep.c		function code missing from the library;
	crtuzI.obj	program initialization code for UZI180;
	libcuzI.lib	library of standard functions for UZI180;
	makefile	file to simplify program compilation.

You can compile the program for the UZI180 operating system using makefile by running the command

	gmake

After that, the kermit executable file will appear, and the auxiliary memory allocation files kermit.map and symbols kermit.sym. Compilation proceeds without diagnostic messages.


Installing the kermit program on a floppy disk with UZI180
----------------------------------------------------------

The compiled kermit program must be written using the cpmtools-2.21 utilities to a floppy disk image with the CP / M v2.2 operating system

	cpmcp -f p112-old cpm2-070805.img kermit 0:KERMIT

in addition, write the ucp.com utility to it

	cpmcp -f p112-old cpm2-070805.img ucp.com 0:UCP.COM

Write the generated image to a floppy disk

	sudo dd if=cpm2-070805.img of=/dev/disk5

Then boot CP/M from this floppy disk and run the command

	ucp 2

and run the following commands:

	ucp: cd /bin
	ucp: bget kermit
	ucp: chmod 775 kermit
	ucp: quit
	A>

Next, you can boot from a floppy disk with UZI180 and run the kermit program.

Note: The UZI180 operating system must use only one screen as the prompt.


Sharing files between MacBook and P112 using Kermit protocol
------------------------------------------------------------

To share files on a MacBook computer, you need:

1.	Install the Kermit server

2.	Launch a terminal program such as iTerm.
 
3.	Go to the working directory in which the files for UZI180 will be located

	cd /Users/macbook/Desktop/data

4.	Run the kermit program from this directory

	kermit

5.	Make some settings for her

	set port /dev/cu.usbserial-120 9600
	set speed 9600
	set flow-control none
	set carrier-watch off

and then switch to server mode:

	server

The Kermit server on the MacBook is now ready to receive files from the UZI180 and save them to the current directory on the MacBook.

6.	On another iTerm terminal, you need to run the program

	screen /dev/cu.usbserial3 9600

After loading the operating system, to send the file to the MacBook server, you need to run the kermit program on the P112:

	kermit sdrl /dev/tty2 file_name

where the letters after the word kermit mean the following:

	s		sent mode;
	d		debug, if you specify the letter d twice in the command, extended debugging information will be displayed;
	r		writing exchange information to the PACKET.LOG file. If the letter r is not present in the command, then PACKET.LOG is not created;
	l		tty name (/dev/tty2);
	file_name	is the name of the file being transferred.

Other letters are described in the kermit User manual.

7.	To get the file from the Kermit server, enter the command

	kermit rdrl /dev/tty2

where

	r	receive mode

The rest of the letters have the same meaning.

8.	On the MacBook side, you need to send the required file using the command

	C-Kermit>send file_name

The kermit program on the P112 microcomputer in the UZI180 operating system runs as on a local computer, using a free RS-232 line for file transfer.
Unfortunately, the UZI180 operating system cannot change the baud rate on tty lines. The kermit program knows about this and when trying to determine the baud rate, it will display a message

	Speed setting implemented for Unix only

The kermit program can connect to a remote computer, and after authorization on the remote side, you can run, for example, the gkermit program for exchange. Then return to the local computer and run the kermit program to send or receive a file. To do this, in the kermit command, the first letter must be c. But this is a more complicated way of exchanging files between computers.


Beautifully conceived, but poorly implemented
---------------------------------------------

The source code of the program is quite simple. The sgttyb structure is implemented slightly differently but changing its description should not affect the program's operation.

In the UZI180 operating system, members of the tchars structure are members of the sgttyb structure.

Perhaps the terminal driver is not implemented correctly in the UZI180.

The program tries to send or receive a file from the server but fails to do so. The server sees These attempts. Two d's in the command result in diagnostic output to the console. The letter z results in the creation of a PACKET.LOG debug file on P112. However, the information contained in this file is uninformative and incomprehensible for understanding.

Perhaps among the lovers of the P112 microcomputer and the UZI180 operating system there are knowledgeable people who will help solve the problem. I really want to exchange files using the Kermit protocol.


Andrey Nikitin

