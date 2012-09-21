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
 
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "gpio.h"

#define PROGRAM		"gpio"
//#define VERSION		"1.00"

/*
 * Function:    check_module_loaded
 * Description: check if gpio module is loaded by parsing "/proc/modules"
 */
static char check_module_loaded(void)
{
	static const char *modules = "/proc/modules";
	static const char *module = "gpio ";
	char buffer[80];
	char found = 0;
	FILE *fp;

	fp = fopen(modules, "r");
	if (fp == NULL) {
		printf("[ERROR] open %s: %s\n", modules, strerror(errno));
		exit(EXIT_FAILURE);
	}

	while (fgets(buffer, sizeof(buffer) - 1, fp)) {
		if (!strncmp(buffer, module, sizeof(module))) {
			found = 1;
			break;
		}
	}
	fclose(fp);

	return found;
}
int main(int argc, char *argv[])
{
	int ret_val = 0;
	int fd0;
	int inval=EXIT_FAILURE;
        int outval;

	/* Check if gpio kernel module is loaded */
	if (!check_module_loaded()) {
		printf("[ERROR] gpio driver not loaded, please run 'modprobe gpio'\n\n");
		exit(EXIT_FAILURE);
	}

 	if( (fd0 = open( "/dev/gpio/0", O_RDWR )) < 0 ){ 
		/* ERROR */
		printf("[ERROR] gpio open'\n\n");
		exit(EXIT_FAILURE);
 	}
	/* Configure GPIO as OUTPUT */  
	if( ioctl( fd0, GPIO_CONFIG_AS_OUT, 0 ) < 0 )
	{
        	/* ERROR */
		printf("[ERROR]  gpio as output %s\n", strerror(errno));
//		printf("[ERROR] gpio as output'\n\n");
	} 
	/* Set the output to 1 */
	outval = 1;
	if( ( ret_val = ioctl( fd0, GPIO_WRITE_PIN_VAL, &outval ) ) < 0 ) 
	{
        	/* ERROR */
		printf("[ERROR] gpio write'\n\n");
	}
	/* Configure GPIO as INPUT */           
	if( ioctl( fd0, GPIO_CONFIG_AS_INP, 0 ) < 0 ){
        	/* ERROR */
		printf("[ERROR] gpio as input'\n\n");
//		goto err_close;
	}
	if( ( ret_val = ioctl( fd0, GPIO_READ_PIN_VAL, &inval ) ) < 0 ){
        	/* ERROR */
		printf("[ERROR] gpio read'\n\n");
		goto err_close;
	}
	printf("%d\n",inval);
 err_close:
	close(fd0);

	return ret_val;
}