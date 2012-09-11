/***************************************************************************
                          i2c.c  -  description
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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int i2c_outp(int port,int value)
{
    int file;
    char filename[40];
    int addr = port;        // The I2C address of the 8574
    char buf[10] = {0};
//    const gchar *buffer;

    sprintf(filename,"/dev/i2c-0");
    if ((file = open(filename,O_RDWR)) < 0) {
        printf("Failed to open the bus.");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        return -1;
    }

    if (ioctl(file,I2C_SLAVE,addr) < 0) {
        printf("Failed to acquire bus access and/or talk to slave. 0x%x\n",addr);
        /* ERROR HANDLING; you can check errno to see what went wrong */
        close(file);
        return -2;
    }

    buf[0] = value;
    if (write(file,buf,1) != 1) {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Failed to write to the i2c bus. 0x%x\n",addr);
//        buffer = g_strerror(errno);
//        printf(buffer);
        printf("\n\n");
        close(file);
        return -3;
    }

    close(file);
    return 0;
}

int i2c_inp(int port)
{
    int file;
    char filename[40];
    char buf[10] = {0};
    const char *buffer;
    int addr = port;        // The I2C address of the 8574 default 0x20

//    const gchar *buffer;
//    int addr = 0b00100000;        // The I2C address of the 8574
 
    sprintf(filename,"/dev/i2c-0");
    if ((file = open(filename,O_RDWR)) < 0) {
        printf("Failed to open the bus. %s",filename);
        /* ERROR HANDLING; you can check errno to see what went wrong */
        return -1;
    }
 
    if (ioctl(file,I2C_SLAVE,addr) < 0) {
        printf("Failed to acquire bus access and/or talk to slave. 0x%x\n",addr);
        /* ERROR HANDLING; you can check errno to see what went wrong */
        close(file);
        return -2;
    }

    // Using I2C Read
    if (read(file,buf,1) != 1) {
	/* ERROR HANDLING: i2c transaction failed */
	printf("Failed to read from the i2c bus. 0x%x\n",addr);
	// buffer = g_strerror(errno);
	// printf(buffer);
	// printf("\n\n");
        close(file);
        return -3;
	} else {
	printf("Data %02d \n",buf[0]);
        return buf[0];
    }

    close(file);
}