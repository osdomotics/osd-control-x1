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

void action_switch(char *message );
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
    char datfelder[128][255];
    char message[1024];

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

	for(a=0;a<128;a++) // l�sche Felder
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
    	sprintf (message,"relname1=%s\nrelname2=%s\nrelname3=%s\nrelname4=%s\nrelname5=%s\nrelname6=%s\nrelname7=%s\nrelname8=%s\non1=%s\non2=%s\non3=%s\non4=%s\non5=%s\non6=%s\non7=%s\non8=%s\noff1=%s\noff2=%s\noff3=%s\noff4=%s\noff5=%s\noff6=%s\noff7=%s\noff8=%s",
		datfelder[1],datfelder[3],datfelder[5],datfelder[7],datfelder[9],datfelder[11],datfelder[13],datfelder[15],
		datfelder[17],datfelder[19],datfelder[21],datfelder[23],datfelder[25],datfelder[27],datfelder[29],datfelder[31],
		datfelder[33],datfelder[35],datfelder[37],datfelder[39],datfelder[41],datfelder[43],datfelder[45],datfelder[37]);
        for(a=0;a<strlen(message);a++){
		if(message[a]=='+'){
		  message[a]=' ';
		}
	}
	action_switch(message);
    }
    return(0); 
}
/**************************************************/
void action_switch(char *message )
{

	printf("<BR>switch: %s <BR>",message);  // Debug

	// write data to file
  	FILE * pFile;
  	pFile = fopen (UENVFILE,"w");
  	if (pFile==NULL)
  	{
		printf("<BR>file open error\"/%s\"<BR>",UENVFILE);
		return;
	
  	}

    	fprintf (pFile,"%s\n",message);
        fflush (pFile);
    	fclose (pFile);
	// update uenv from filedhcpval
	sprintf(message,"ubootenv -a %s",UENVFILE);
	printf("<BR>system: %s<BR>",message);
	if(system(message)){
		printf ("error: %s\n",message);
	}
}
/**************************************************/

int main(int argc, char *argv[])
{
    print_html_header();
    
    do_cgi_data();
	
  return EXIT_SUCCESS;
}
