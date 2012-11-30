/***************************************************************************
                          main.c  -  description
                             -------------------
    begin                : Fr September  24 11:00:16 CET 2011
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

#include <signal.h>
#include <termios.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
/**************************************************/

// fuer Serielle
struct termios pts;
//struct termios sts;

static struct termios pots;	/* alte Porteinstellung */
//static struct termios sots; /* alte stdin/out Einstellung */

int pf;

/**************************************************/
void wait()
{
	usleep(500000);
}
int init_serial(char *port,int boud)
{
	pf=open(port,O_RDWR);
	if (pf <0)
	{
		perror(port);
		exit(-1);
	}
	/* Port - Konfig modifiziern */
	tcgetattr(pf, &pts);
	pots = pts;
	pts.c_lflag &= ~ICANON; /* Alle zeichen gleich behandeln */
//	pts.c_lflag &= ~(ECHO | ICANON | ISIG | ECHOE | ECHOK | ECHONL);
//
//	pts.c_cc[VMIN] = 0; /* muss ich noch richtig eintragen */
//	pts.c_cc[VTIME] = 0;/* muss ich noch richtig eintragen */

/*	pts.c_oflag &= ~ONLCR;*/
//	pts.c_oflag &= ~ICRNL;
//	pts.c_oflag &= ~OPOST;
	/* keine Flusskontrolle */
/*	pts.c_cflag &= ~CRTSCTS;*/
	pts.c_iflag &= ~(IXON | IXOFF );
	pts.c_cflag &= ~CSIZE;
	pts.c_cflag |= CS8;	/* 8 Bits */
	pts.c_cflag &= ~PARENB;
/*	pts.c_cflag &= ~PARODD;  EVEN Parity */
	pts.c_cflag &= ~CSTOPB; /* 1 Stop */
	/* Boudrate */
	cfsetospeed(&pts, B9600);
	cfsetispeed(&pts, B9600);

	/* die Einstellungen Setzen */
	tcsetattr(pf, TCSANOW, &pts);
	return(0);
}
/**************************************************/
// Sende die Daten
/**************************************************/
void send_seriell(int fd, char* vString, int length)
{
	int res;
//	int i;
//	int a;
//	char recivbuf[256];

	res=write(fd,vString,length);
	printf("Send: %i \n",res);
/*
	wait();
	i=read(pf,recivbuf,sizeof(recivbuf));

	for(a=0;a<i;a++)
	{
		printf("%d Zeichen: %x\n",a,recivbuf[a]); // debug
	}
*/
}
void close_serial()
{
	tcsetattr(pf, TCSANOW, &pots);
}

int fs20(char command)
{
	return 0;
}

int getuboot( char * env, char * val )
{

  FILE *fp;
  char path[1035];

  /* Open the command for reading. */
  fp = popen(env, "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }

  /* Read the output a line at a time - output it. */
  while (fgets(path, sizeof(path)-1, fp) != NULL) {
    printf("%s", path);
    strcpy(val,path);
  }

  /* close */
  pclose(fp);

  return 0;
}

int main (int argc, char **argv)
{
       char message[256];
       char envmessage[256];
       char mvalue[256];
       int i;
       char *dvalue = NULL;
       char *vvalue = NULL;
       char *cvalue = NULL;

       int index;
       int c;
     
       opterr = 0;
     
       while ((c = getopt (argc, argv, "d:v:c:")) != -1)
         switch (c)
           {
           case 'd':
             dvalue = optarg;
             break;
           case 'v':
             vvalue = optarg;
             break;
           case 'c':
             cvalue = optarg;
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
     
       printf ("d = %s, v = %s, c = %s\n",
               dvalue, vvalue, cvalue);
 
     
       for (index = optind; index < argc; index++)
         printf ("Non-option argument %s\n", argv[index]);

// go and interprete c value
	sprintf(envmessage,"ubootenv -p %s | cut -f2 -d'='",cvalue);
        getuboot(envmessage,mvalue);
	printf("getuboot: %s",mvalue);

	int value[10];
	for(i=0;i<10;i++){
		value[i]=0;
	}
	sscanf(mvalue,"%x %x %x %x %x %x %x %x %x %x",&value[0],&value[1],&value[2],&value[3],&value[4],&value[5],&value[6],&value[7],&value[8],&value[9]);
	for(i=0;i<10;i++){
		message[i]=value[i];
	}
	printf("init seriell\n");
	init_serial("/dev/ttyFIM0",9600);
// test
/*
	message[0]=0x02;
	message[1]=0x01;
	message[2]=0xF3;
	message[3]=0x00;
*/
	printf("send seriell\n");
	send_seriell(pf,message, value[1]+2);
	printf("close seriell\n");
	close_serial();

       return EXIT_SUCCESS;
}

