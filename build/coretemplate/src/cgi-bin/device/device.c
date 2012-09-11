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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UENVFILE	"/tmp/devenv.txt"
#define REBOOTFILE	"/tmp/reboot.txt"

// declarationen
void print_html_header();
long do_convert(char *data, long pos,char *part);

void action_switch(char *feld1, char *feld2, char *feld3, char *feld4, char *feld5, char *feld6, char *feld7, char *feld8 );
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
    char datfelder[32][255];

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

	for(a=0;a<32;a++) // l�sche Felder
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
void action_switch(char *feld1, char *feld2, char *feld3, char *feld4, char *feld5, char *feld6, char *feld7, char *feld8 )
{
//	char message[1024];

	printf("<BR>switch: %s %s %s %s %s %s %s %s<BR>",feld1,feld2,feld3,feld4,feld5,feld6,feld7,feld8);  // Debug

	// write data to file
  	FILE * pFile;
  	pFile = fopen (UENVFILE,"w");
  	if (pFile==NULL)
  	{
		printf("<BR>file open error\"/%s\"<BR>",UENVFILE);
		return;
	
  	}

    	fprintf (pFile,"relname1=%s\nrelname2=%s\nrelname3=%s\nrelname4=%s\nrelname5=%s\nrelname6=%s\nrelname7=%s\nrelname8=%s\n",
			feld1,feld2, feld3,feld4,feld5,feld6, feld7,feld8);
        fflush (pFile);
    	fclose (pFile);
	// update uenv from filedhcpval
	//sprintf(message,"ubootenv -a %s",UENVFILE);
	//printf("<BR>system: %s<BR>",message);
	//if(system(message)){
	//	printf ("error: %s\n",message);
	//}
}
/**************************************************/

int main(int argc, char *argv[])
{
    print_html_header();
    
    do_cgi_data();
	
  return EXIT_SUCCESS;
}
