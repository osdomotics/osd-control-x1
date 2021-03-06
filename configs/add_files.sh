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
rmdir --ignore-fail-on-non-empty "${ROOTFS_DIR}/usr/share/www"
cp -a "${DEL_PROJ_DIR}/build/coretemplate/www"  "${ROOTFS_DIR}/usr/share"
## Control-X1
cp -a "${DEL_PROJ_DIR}/build/coretemplate/etc"  "${ROOTFS_DIR}/"
cp -a "${DEL_PROJ_DIR}/build/coretemplate/sbin"  "${ROOTFS_DIR}/"
chmod +s "${ROOTFS_DIR}/sbin/ubootenv"
## FS20
#ifdef CONFIG_FS20
if [  ${CONFIG_FS20} ]
  then
    echo "add files FS20"
    cp -a "${DEL_PROJ_DIR}/build/coretemplate/etc-fs20/."  "${ROOTFS_DIR}/etc"
    cp -a "${DEL_PROJ_DIR}/build/coretemplate/sbin-fs20/."  "${ROOTFS_DIR}/sbin"
    webgen -d "${DEL_PROJ_DIR}/build/coretemplate/webgen/Control-FS20/" run
    cp -a "${DEL_PROJ_DIR}/build/coretemplate/webgen/Control-FS20/output/."  "${ROOTFS_DIR}/usr/share/www"
fi
#ifdef CONFIG_FS20
if [  ${CONFIG_X2} ]
  then
    echo "add files X2"
    cp -a "${DEL_PROJ_DIR}/build/coretemplate/etc-x2/."  "${ROOTFS_DIR}/etc"
    cp -a "${DEL_PROJ_DIR}/build/coretemplate/usr-sbin-x2/."  "${ROOTFS_DIR}/usr/sbin"
    cp -a "${DEL_PROJ_DIR}/build/coretemplate/usr-bin-x2/."  "${ROOTFS_DIR}/usr/bin"
    webgen -d "${DEL_PROJ_DIR}/build/coretemplate/webgen/Control-X2/" run
    cp -a "${DEL_PROJ_DIR}/build/coretemplate/webgen/Control-X2/output/."  "${ROOTFS_DIR}/usr/share/www"
    cp -a "${DEL_PROJ_DIR}/build/coretemplate/cgi-bin-x2/."  "${ROOTFS_DIR}/usr/share/www/cgi-bin"
fi
#endif
exit 0
