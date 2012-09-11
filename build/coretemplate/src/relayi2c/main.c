/***************************************************************************
                          main.c  -  description
                             -------------------
    begin                : Fr September  24 11:00:16 CET 2010
    copyright            : (C) 2010 by Harald Pichler
    email                : harald@the-develop.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
//#include <unistd.h>
//#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/io.h>
#include <limits.h>

#include "i2c.h"

// 0010 0001
#define AOFF	0x21
#define BOFF	0x22
#define COFF	0x24
#define DOFF	0x28
#define EOFF	0x31
#define FOFF	0x32
#define GOFF	0x34
#define HOFF	0x38
// 0100 0001
#define AON	0x41
#define BON	0x42
#define CON	0x44
#define DON	0x48
#define EON	0x51
#define FON	0x52
#define GON	0x54
#define HON	0x58
#define NOP     0x00

/**************************************************/
void wait()
{
	usleep(500000);
}

int main (int argc, char **argv)
{
       char *avalue = NULL;
       char *bvalue = NULL;
       char *cvalue = NULL;
       char *dvalue = NULL;
       char *evalue = NULL;
       char *fvalue = NULL;
       char *gvalue = NULL;
       char *hvalue = NULL;

       int index;
       int c;
     
       opterr = 0;
     
       while ((c = getopt (argc, argv, "a:b:c:d:e:f:g:h:")) != -1)
         switch (c)
           {
           case 'a':
             avalue = optarg;
             break;
           case 'b':
             bvalue = optarg;
             break;
           case 'c':
             cvalue = optarg;
             break;
           case 'd':
             dvalue = optarg;
             break;
           case 'e':
             evalue = optarg;
             break;
           case 'f':
             fvalue = optarg;
             break;
           case 'g':
             gvalue = optarg;
             break;
           case 'h':
             hvalue = optarg;
             break;

           case '?':
             if (optopt == 'c')
               fprintf (stderr, "Option -%c requires an argument.\n", optopt);
             else if (isprint (optopt))
               fprintf (stderr, "Unknown option `-%c'.\n", optopt);
             else
               fprintf (stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
             return 1;
           default:
             abort ();
           }
     
       printf ("a = %s, b = %s, c = %s, d = %s\n",
               avalue, bvalue, cvalue, dvalue);
       printf ("e = %s, f = %s, g = %s, h = %s\n",
               evalue, fvalue, gvalue, hvalue);

     
       for (index = optind; index < argc; index++)
         printf ("Non-option argument %s\n", argv[index]);

	if(avalue && avalue[0]=='0'){
		i2c_outp(0x20,AON);
		wait();
	}
	if(avalue && avalue[0]=='1'){
		i2c_outp(0x20,AOFF);
		wait();
	}
	if(bvalue && bvalue[0]=='0'){
		i2c_outp(0x20,BON);
		wait();
	}
	if(bvalue && bvalue[0]=='1'){
		i2c_outp(0x20,BOFF);
		wait();
	}
	if(cvalue && cvalue[0]=='0'){
		i2c_outp(0x20,CON);
		wait();
	}
	if(cvalue && cvalue[0]=='1'){
		i2c_outp(0x20,COFF);
		wait();
	}
	if(dvalue && dvalue[0]=='0'){
		i2c_outp(0x20,DON);
		wait();
	}
	if(dvalue && dvalue[0]=='1'){
		i2c_outp(0x20,DOFF);
		wait();
	}
	if(evalue && evalue[0]=='0'){
		i2c_outp(0x20,EON);
		wait();
	}
	if(evalue && evalue[0]=='1'){
		i2c_outp(0x20,EOFF);
		wait();
	}
	if(fvalue && fvalue[0]=='0'){
		i2c_outp(0x20,FON);
		wait();
	}
	if(fvalue && fvalue[0]=='1'){
		i2c_outp(0x20,FOFF);
		wait();
	}
	if(gvalue && gvalue[0]=='0'){
		i2c_outp(0x20,GON);
		wait();
	}
	if(gvalue && gvalue[0]=='1'){
		i2c_outp(0x20,GOFF);
		wait();
	}
	if(hvalue && hvalue[0]=='0'){
		i2c_outp(0x20,HON);
		wait();
	}
	if(hvalue && hvalue[0]=='1'){
		i2c_outp(0x20,HOFF);
		wait();
	}
	i2c_outp(0x20,NOP);

       return EXIT_SUCCESS;
}

