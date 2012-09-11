#!/bin/bash
###############################################################################
##
## @File:       $RCSfile: add_files.sh,v $
## @Author:     Digi International Inc.
## @Revision:   $Revision: 1.2 $
## @Date:       $Date: 2007-03-13 15:57:09 $
##
## @Description:
##
##  Template script available for customers to edit so they can install
##  their own files in the rootfs.
##
##  It is installed in each project so it can be per-project customized.
##  This script has access to following project variables:
##
##      DEL_TOOL_DIR -> Digi Embedded Linux path.
##      DEL_PROJ_DIR -> Project path.
##      DEL_PLATFORM -> Target platform.
##      DEL_TFTP_DIR -> TFTPBOOT path.
##      DEL_NFS_DIR  -> Rootfs nfs-exported path.
##
##  These variables are exported in topdir Makefile.
##
##  Though you can use all above variables, the recommended way is to customize
##  the project rootfs (see ROOTFS_DIR below). Doing this way, your changes
##  will be included in rootfs images and in nfs-exported rootfs as well.
##
###############################################################################

ROOTFS_DIR="${DEL_PROJ_DIR}/build/rootfs"

## Example: create a custom directory in rootfs etc dir.
# mkdir -p "${ROOTFS_DIR}/etc/myfolder"
cp  "${DEL_PROJ_DIR}/build/coretemplate/src/relayi2c/relayi2c"  "${ROOTFS_DIR}/bin/relayi2c"
cp  "${DEL_PROJ_DIR}/build/coretemplate/src/ureboot/ureboot"  "${ROOTFS_DIR}/bin/ureboot"
cp  "${DEL_PROJ_DIR}/build/coretemplate/src/urelay/urelay"  "${ROOTFS_DIR}/bin/urelay"
cp  "${DEL_PROJ_DIR}/build/coretemplate/src/gpio/gpio"  "${ROOTFS_DIR}/bin/gpio"
chmod +s "${ROOTFS_DIR}/bin/relayi2c"
chmod +s "${ROOTFS_DIR}/bin/ureboot"
chmod +s "${ROOTFS_DIR}/sbin/ubootenv"
rmdir --ignore-fail-on-non-empty "${ROOTFS_DIR}/usr/share/www"
cp -a "${DEL_PROJ_DIR}/build/coretemplate/www"  "${ROOTFS_DIR}/usr/share"
## entryeasy
cp -a "${DEL_PROJ_DIR}/build/coretemplate/etc"  "${ROOTFS_DIR}/"
cp -a "${DEL_PROJ_DIR}/build/coretemplate/sbin"  "${ROOTFS_DIR}/"
exit 0
