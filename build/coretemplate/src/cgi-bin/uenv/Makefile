ROOTFS_DIR = $(strip $(wildcard $(DEL_PROJ_DIR)/build/rootfs))
STRIP      = $(CROSS_COMPILE)strip
CC         = $(CROSS_COMPILE)gcc
CFLAGS     = -Wall
BINARY     = uenv.cgi
all: $(BINARY)
install: $(BINARY)
ifneq ($(ROOTFS_DIR),)
    $(STRIP) $<
    install -D -m 0755 $< $(ROOTFS_DIR)/usr/bin$<
else
    $(info *** Directory $(ROOTFS_DIR) not found, $< not installed.)
endif
clean:
    rm -f $(BINARY)
