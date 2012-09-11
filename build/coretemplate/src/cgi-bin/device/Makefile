VERSION = 3.02
# X86
#CC      = gcc
# ME9210
CC      = arm-linux-gcc
# sheevaplug
#CC      = arm-linux-gnueabi-gcc

CFLAGS  = -Wall -g -D_REENTRANT -DVERSION=\"$(VERSION)\"
LDFLAGS =

OBJ = device.o

prog: $(OBJ)
	$(CC) $(CFLAGS) -o device.cgi $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(OBJ) device.cgi
