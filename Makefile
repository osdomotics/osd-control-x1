################################################################################
## Autogenerated. Do not edit.
export DEL_BASE_DIR=/home/harald/digi/digiel5.7
export DEL_TOOL_DIR=$(DEL_BASE_DIR)/x-tools/arm-unknown-linux-uclibcgnueabi
export DEL_SYSR_DIR=$(DEL_TOOL_DIR)/arm-unknown-linux-uclibcgnueabi/sysroot
export DEL_KERN_DIR=$(DEL_BASE_DIR)/kernel/linux-2.6.35
export DEL_PROJ_DIR:=$(shell pwd)
export DEL_PLATFORM=cme9210js
export DEL_TFTP_DIR=/tftpboot
export DEL_NFS_DIR=

SUBPRJ_LIST:=kernel rootfs apps fs20
################################################################################
# Control-X1 --> plug-control
# Control-X2 --> 6lowpan edge-router
# Control-FS20 --> fs20-control 
################################################################################
export OSD_TARGET=Control-X1
export CONFIG_FS20=y
//export CONFIG_X2=y

include rules/makefile.in
include rules/kernel.in
include rules/apps.in
ifdef CONFIG_FS20
  include rules/fs20.in
endif
include rules/rootfs.in
