/***************************************************************************
                          main.c  -  description
                             -------------------
    copyright            : (C) 2010 by  Harald Pichler
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int file_exists(const char * filename);

/**************************************************/
int file_exists(const char * filename)
{
    FILE * file;

    if (file = fopen(filename, "r")) //I'm sure, you meant for READING =)
    {
        fclose(file);
        return 1;
    }
    return 0;
}

/**************************************************/
int main (int argc, char **argv)
{
	char message[512];
	int count=0;
	// reboot
	while(1){
		if(file_exists("/tmp/devenv.txt")){
			sprintf(message,"ubootenv -a /tmp/devenv.txt; rm /tmp/devenv.txt; rm /tmp/uenv; ubootenv -d >> /tmp/uenv" );
			printf("system: %s\n",message);
			if(system(message)){
				printf ("error: %s\n",message);
			}
		}
		if(count == 10){
			if(file_exists("/tmp/relaynew")){
				sprintf(message,"ubootenv -a /tmp/relaynew ; rm /tmp/relaynew ; rm /tmp/uenv ; ubootenv -d >> /tmp/uenv" );
				printf("system: %s\n",message);
				if(system(message)){
					printf ("error: %s\n",message);
				}
			}
		}
		count++;
		if(count > 10){
			count=0;
		}
		sleep(1);
	}
        return EXIT_SUCCESS;
}

