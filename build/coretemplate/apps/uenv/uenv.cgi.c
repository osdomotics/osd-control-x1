/***************************************************************************
                          uenv.c  -  description
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
int do_cgi_data();
int readenvall();

// globale Variablen

/**************************************************/
void  print_html_header()
{
     printf("Content-type: application/json-rpc\r\n\r\n");
}

/**************************************************/
int do_cgi_data()
{
    readenvall();
    return(0); 
}

/**************************************************/
int readenvall()
{
    FILE *fpipe;
//    char *command = "ubootenv -d";
    char *command = "cat /tmp/uenv";
    char line[256];

    char delimiter = '=';
    char *ptr=NULL;
    int  ctmp;

   if ( !(fpipe = (FILE*)popen(command,"r")) )
   {  // If fpipe is NULL
      perror("Problems with pipe");
      exit(1);
   }
   // convert to json
//   printf("{\"relay0\":\"1\",\"relay1\":\"0\",\"relay2\":\"0\",\"relay3\":\"0\"}\n");
   printf("{");
   while ( fgets( line, sizeof line, fpipe))
   { 
    // todo convert from "name=value" to "{\"name\" : \"value\" , ... }"
//    printf("%s", line);
    	if(strlen(line) >0 && line[strlen(line)-1]=='\n'){
    		ptr = strchr(line, delimiter);
    		if(ptr != NULL) {
			line[strlen(line)-1]='\0';
			*ptr='\0';
			printf("\"%s\":", line);
			printf("\"%s\",\n", ptr+1);
    		}
   	}else{
		perror("line too long");
		do{
		ctmp=fgetc(fpipe);
		}while(ctmp != EOF && ctmp != '\n');
   	}
   }
   printf("\"NOP\":\"0\"\n");
   printf("}");

   pclose(fpipe);
   return(0);
}

/**************************************************/
int main(int argc, char *argv[])
{
    print_html_header();
    do_cgi_data();

  return EXIT_SUCCESS;
}
