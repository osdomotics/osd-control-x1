/***************************************************************************
                          option.c  -  description
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UENVFILE	"/tmp/uenv.txt"
#define REBOOTFILE	"/tmp/reboot.txt"

// declarationen
void print_html_header();
long do_convert(char *data, long pos,char *part);

void action_switch(char *feld1, char *feld2, char *feld3, char *feld4 , char *feld5 , char *feld6 , char *feld7, char *feld8);
int checkip(char *feld);

// globale Variablen


/**************************************************/
void  print_html_header()
{
	printf("Content-type: text/html\n\n");
}

/**************************************************/
long do_convert(char *data, long pos,char *part)
{
  long a;
  long b;

  for(a=pos,b=0;a<strlen(data);a++)
  {
    if((data[a]=='=')||(data[a]=='&'))
    {
      part[b]=0;
      return(a+1);
    }
    else
    {
      part[b]=data[a];
      b++;
    }
  }
 part[b]=0;
 return(-1);  
}
/**************************************************/
int do_cgi_data()
{
    int a;
    char data[1024];
    char part[255];
    int  partnum;
    char *lenstr;
    long len;
    long cgipos;
    char datfelder[16][255];

    lenstr= getenv("CONTENT_LENGTH");
    if(lenstr==NULL)
    {
	printf("<BR>ERROR!<BR>");
    }
    else
    {
	sscanf(lenstr,"%ld",&len);
	printf("<BR>%ld<BR>",len);
	fgets(data,len+1,stdin);
	printf("<BR>%s<BR>",data);

	for(a=0;a<16;a++) // l�sche Felder
    	{
      	datfelder[a][0]=0;
    	}

        cgipos=0;
	partnum=0;
	while(cgipos != -1)
	{
          cgipos=do_convert(data,cgipos,part);	
//	  printf("<BR>%d %s %ld<BR>",partnum,part,cgipos);  // debug
	  sprintf(datfelder[partnum],"%s",part);
	  partnum++;
	}
	action_switch(datfelder[1],datfelder[3],datfelder[5],datfelder[7],datfelder[9],datfelder[11],datfelder[13],datfelder[15]);
    }
    return(0); 
}
/**************************************************/
void action_switch(char *feld1, char *feld2, char *feld3, char *feld4 ,char *feld5 ,char *feld6 ,char *feld7 ,char *feld8)
{
	char message[512];
	char dhcpval[128];

	printf("<BR>switch: %s %s %s %s %s %s %s %s<BR>",feld1,feld2,feld3,feld4,feld5,feld6,feld7,feld8);  // Debug
	if(checkip(feld1)){
		printf("<BR>bad ip: %s<BR>",feld1);
		return;
	}
	if(checkip(feld2)){
		printf("<BR>bad gw: %s<BR>",feld2);
		return;
	}
	if(checkip(feld3)){
		printf("<BR>bad mask: %s<BR>",feld2);
		return;
	}
	if(strcmp (feld4,"false")){
		sprintf(dhcpval,"on");
	}else{
		sprintf(dhcpval,"off");
	}
	if(checkip(feld5)){
		printf("<BR>bad dns1: %s<BR>",feld5);
		return;
	}
	if(checkip(feld6)){
		printf("<BR>bad dns2: %s<BR>",feld6);
		return;
	}
	if(checkip(feld7)){
		printf("<BR>bad serverip: %s<BR>",feld7);
		return;
	}
	// write data to file
  	FILE * pFile;
  	pFile = fopen (UENVFILE,"w");
  	if (pFile==NULL)
  	{
		printf("<BR>file open error\"/%s\"<BR>",UENVFILE);
		return;
	
  	}

    	fprintf (pFile,"ipaddr=%s\ngatewayip=%s\nnetmask=%s\ndnsip=%s\ndnsip2=%s\nserverip=%s\ndhcp=%s\nhostname=%s\n",
			feld1,feld2, feld3,feld5, feld6, feld7, dhcpval, feld8);
        fflush (pFile);
    	fclose (pFile);
	// update uenv from filedhcpval
	sprintf(message,"ubootenv -a %s",UENVFILE);
	printf("<BR>system: %s<BR>",message);
	if(system(message)){
		printf ("error: %s\n",message);
	}
	// reboot
  	pFile = fopen (REBOOTFILE,"w");
  	if (pFile==NULL)
  	{
		printf("<BR>file open error\"%s\"<BR>",REBOOTFILE);
		return;
	
  	}

    	fprintf (pFile,"1");
        fflush (pFile);
    	fclose (pFile);
/*
	sprintf(message,"ureboot");
	printf("<BR>system: %s<BR>",message);
	if(system(message)){
		printf ("error: %s\n",message);
	}
*/
}
/**************************************************/
int checkip(char *feld)
{
	int seg[4];
	int a;

	sscanf(feld,"%d.%d.%d.%d",&seg[0],&seg[1],&seg[2],&seg[3]);
//	printf("<BR>checkip: %s = %d %d %d %d<BR>",feld,seg[0],seg[1],seg[2],seg[3]); // debug
	for(a=0;a<4;a++){
		if(seg[a] < 0 || seg[a] > 255){
			return(1);
		}
	}
	return(0);
}

int main(int argc, char *argv[])
{
    print_html_header();
    
    do_cgi_data();
	
  return EXIT_SUCCESS;
}
