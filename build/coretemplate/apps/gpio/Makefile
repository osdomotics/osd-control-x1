##########################################################################
##
## Sample makefile to show how to include user apps.
##
## This makefile has access to following project variables:
##
##	DEL_TOOL_DIR -> Digi Embedded Linux path.
##	DEL_PROJ_DIR -> Project path.
##	DEL_PLATFORM -> Target platform.
##	DEL_TFTP_DIR -> TFTPBOOT path.
##	DEL_NFS_DIR  -> Rootfs nfs-exported path.
##
## These variables are configured in topdir Makefile.
##
## Though you can use DEL_NFS_DIR to install your application to the
## exported rootfs directly, the recommended way is to install it in
## the project rootfs (see ROOTFS_DIR below). Doing this way, your
## application will be check for library dependences and then installed
## both in DEL_NFS_DIR and in rootfs images.
##
##########################################################################

ROOTFS_DIR = $(strip $(wildcard $(DEL_PROJ_DIR)/build/rootfs))
STRIP      = $(CROSS_COMPILE)strip
CC         = $(CROSS_COMPILE)gcc
CFLAGS     = -Wall
BINARY     = gpio

#-include $(DEL_PROJ_DIR)/build/.config-$(DEL_PLATFORM)

#ifdef CONFIG_APPS_HELLOWORLD_C
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))

all: $(BINARY)   $(OBJS)

$(BINARY): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@

install: $(BINARY)
ifneq ($(ROOTFS_DIR),)
	$(STRIP) $<
	install -D -m 0755 $< $(ROOTFS_DIR)/usr/bin/$<
else
	@printf "\n"
	@printf "[ WARNING ] $<: installation directory not found, application not installed\n"
	@printf "\n"
	@printf "            This could be due to support for rootfs was not included in the project.\n"
	@printf "\n"
	@printf "            Please, create a project with rootfs support or edit the application makefile\n"
	@printf "            and set the ROOTFS_DIR variable to the installation directory.\n"
	@printf "\n"
endif
#else
#install:
#	@: # Do nothing if the application is not selected
#endif # CONFIG_APPS_HELLOWORLD_C

clean:
	rm -f $(BINARY) $(OBJS)
