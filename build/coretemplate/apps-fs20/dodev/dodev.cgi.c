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


// declarationen
void print_html_header();
long do_convert(char *data, long pos,char *part);
void action_switch(char *feld1, char *feld2, char *feld3, char *feld4, char *feld5, char *feld6, char *feld7, char *feld8 );
int  updataenv(char name,int val);
int  updataenvtmp(char name,int val);

// globale Variablen

#define RELAYFILE	"/tmp/relay"
#define RELAYFILENEW	"/tmp/relaynew"

/**************************************************/
void  print_html_header()
{
	printf("Content-type: text/html\n\n");
}

/**************************************************/
void	print_html_tail()	
{
	printf("</BODY>\n");
	printf("</HTML>      \n");
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
	if(system("relayi2c -a 0 -b 0 -c 0 -d 0 -a 0 -b 0 -c 0 -d 0")){
		printf ("error: relais off\n");
	}else{
		printf("<BR>relay off<BR>");
	}
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
	  printf("<BR>%d %s %ld<BR>",partnum,part,cgipos);  // debug
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
//	int plug[]={0,0,0,0};
	char plugname = ' ';
	int plugval = 0;
	char message[256];

	printf("switch: %s %s %s %s %s %s %s %s <BR>",feld1,feld2,feld3,feld4,feld5,feld6,feld7,feld8);  // Debug
	// FS20-Funk
	if(feld1[0] != 0 && feld2[0] != 0)
	{
		if(feld1[0]=='A') plugname='1';
		if(feld1[0]=='B') plugname='2';
		if(feld1[0]=='C') plugname='3';
		if(feld1[0]=='D') plugname='4';
		if(feld1[0]=='E') plugname='5';
		if(feld1[0]=='F') plugname='6';
		if(feld1[0]=='G') plugname='7';
		if(feld1[0]=='H') plugname='8';
		if(feld2[0]=='t') plugval = 1;
		if(feld2[0]=='f') plugval = 0;

	}
	if(plugval==0){
		sprintf(message,"sendfs20 -coff%c",plugname);
	}
	if(plugval==1){
		sprintf(message,"sendfs20 -con%c",plugname);
	}
	printf("%s",message); // debug
	if(system(message)){
		printf ("error: %s\n",message);
	}else{
		printf("%s",message); // debug
	}
	// HX2206
	if(feld1[0] != 0 && feld2[0] != 0)
	{
		if(feld1[0]=='A') plugname='a';
		if(feld1[0]=='B') plugname='b';
		if(feld1[0]=='C') plugname='c';
		if(feld1[0]=='D') plugname='d';
		if(feld1[0]=='E') plugname='e';
		if(feld1[0]=='F') plugname='f';
		if(feld1[0]=='G') plugname='g';
		if(feld1[0]=='H') plugname='h';
		if(feld2[0]=='t') plugval = 1;
		if(feld2[0]=='f') plugval = 0;

	}
	sprintf(message,"relayi2c -%c %d",plugname,plugval);
	if(system(message)){
		printf ("error: %s\n",message);
	}else{
		printf("%s",message); // debug
	}
	updataenvtmp(plugname,plugval);
}
/**************************************************/
int  updataenv(char name,int val)
{
	char message[256];
	char envname[128];
	
	if(name=='a') sprintf(envname,"relay1");
	if(name=='b') sprintf(envname,"relay2");
	if(name=='c') sprintf(envname,"relay3");
	if(name=='d') sprintf(envname,"relay4");
	if(name=='e') sprintf(envname,"relay5");
	if(name=='f') sprintf(envname,"relay6");
	if(name=='g') sprintf(envname,"relay7");
	if(name=='h') sprintf(envname,"relay8");

	sprintf(message,"ubootenv -e %s -s %s=%d",envname,envname,val);
	if(system(message)){
		printf ("error: %s\n",message);
	}
	return 0;
}
/**************************************************/
int  updataenvtmp(char name,int val)
{
        FILE *fptr;			/* Pointer to the file */
        FILE *fptrnew;			/* Pointer to the file */
	char message[256];
	char envname[128];
	char line[256];
	char delimiter = '=';
	char *ptr=NULL;
	int  ctmp;

	if(name=='a') sprintf(envname,"relay1");
	if(name=='b') sprintf(envname,"relay2");
	if(name=='c') sprintf(envname,"relay3");
	if(name=='d') sprintf(envname,"relay4");
	if(name=='e') sprintf(envname,"relay5");
	if(name=='f') sprintf(envname,"relay6");
	if(name=='g') sprintf(envname,"relay7");
	if(name=='h') sprintf(envname,"relay8");

	fptr = fopen(RELAYFILE,"r");   /* open tmp file */
	if(fptr == NULL)
	{
		printf("<BR>File I/O Error<BR>");
  		return (-1);
	}
	fptrnew = fopen(RELAYFILENEW,"w");   /* open tmp file */
	if(fptr == NULL)
	{
		printf("<BR>File I/O Error<BR>");
  		return (-1);
	}
	while ( fgets( line, sizeof line, fptr)){
    	if(strlen(line) >0 && line[strlen(line)-1]=='\n'){
    		ptr = strchr(line, delimiter);
    		if(ptr != NULL) {
			line[strlen(line)-1]='\0';
			*ptr='\0';
			fprintf(fptrnew,"%s=", line);
			if(strcmp(line,envname)){
				fprintf(fptrnew,"%s\n", ptr+1);
			}else{
				fprintf(fptrnew,"%d\n", val);
			}
    		}
   	}else{
		perror("line too long");
		do{
		ctmp=fgetc(fptr);
		}while(ctmp != EOF && ctmp != '\n');
   	}

	}
	fclose(fptrnew);			/* Close the file.			*/
	fclose(fptr);			/* Close the file.			*/
	sprintf(message,"cp %s %s", RELAYFILENEW, RELAYFILE);
	if(system(message)){
		printf ("error: %s\n",message);
	}

	return 0;
}
/**************************************************/
int main(int argc, char *argv[])
{
    print_html_header();
    
    do_cgi_data();
	
  return EXIT_SUCCESS;
}
