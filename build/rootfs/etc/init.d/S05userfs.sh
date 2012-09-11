#!/bin/sh
#===============================================================================
#
#  S05userfs.sh
#
#  Copyright (C) 2008 by Digi International Inc.
#  All rights reserved.
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License version 2 as published by
#  the Free Software Foundation.
#
#
#  !Revision:    $Revision: 1.5 $:
#  !Description: Mount user filesystems
#
#===============================================================================

# fstab file systems
[ -z "${quietboot}" ] && echo -n "Mounting fstab configured file systems..."
mount -a
[ -z "${quietboot}" ] && echo " done"

# # jffs2 user partitions
# userfs_banner="Mounting jffs2 user partitions:"
# userfs_bool="true"
# for i in `seq 0 10`; do
#     if PART="`nvram print partition select=${i} name flag_fs_type flag_fs_root 2>/dev/null`"; then
#         NAME=`echo ${PART} | sed 's/^.*name=\(.*\) .* .*$/\1/'`
#         TYPE=`echo ${PART} | sed 's/^.*type=\(.*\) .*$/\1/'`
#         ROOT=`echo ${PART} | sed 's/^.*root=\(.*\)$/\1/'`
#         if [ "x${TYPE}" = "xJFFS2"  -a "x${ROOT}" != "x1" ]; then
#             mkdir -p "/mnt/${NAME}"
#             if "${userfs_bool}"; then echo -n "${userfs_banner}"; userfs_bool="false"; fi
#             if mount -t jffs2 "/dev/mtdblock${i}" "/mnt/${NAME}"; then
#                 echo -n " /mnt/${NAME}"
#             fi
#         fi
#     else
#         break
#     fi
# done
# if ! "${userfs_bool}"; then echo "."; fi

exit 0
