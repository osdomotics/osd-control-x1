#!/bin/sh
#===============================================================================
#
#  S03kernelfs.sh
#
#  Copyright (C) 2008 by Digi International Inc.
#  All rights reserved.
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License version 2 as published by
#  the Free Software Foundation.
#
#
#  !Revision:    $Revision: 1.9 $:
#  !Description: Mount kernel filesystems
#
#===============================================================================

set -e

if [ "${1}" != "start" ]; then
	exit 0
fi

kernfs_bool="true"
print_kernfs_banner() {
	if "${kernfs_bool}"; then
		[ -z "${quietboot}" ] && echo -n "Mounting kernel file systems:"
		kernfs_bool="false"
	fi
}

# /proc
if ! mountpoint -q /proc; then
	print_kernfs_banner
	[ -z "${quietboot}" ] && echo -n " /proc"
	mount -t proc proc /proc
fi

# /sys
if grep -q -E "^nodev[[:space:]]+sysfs\$" "/proc/filesystems"; then
	if ! mountpoint -q /sys; then
		print_kernfs_banner
		[ -z "${quietboot}" ] && echo -n " /sys"
		mount -t sysfs sysfs /sys
	fi
fi

# /dev/pts
if grep -q -E "^nodev[[:space:]]+devpts\$" "/proc/filesystems"; then
	mkdir -p /dev/pts
	if ! mountpoint -q /dev/pts; then
		print_kernfs_banner
		[ -z "${quietboot}" ] && echo -n " /dev/pts"
		mount -t devpts devpts /dev/pts
	fi
fi

# /proc/bus/usb
if grep -q -E "^nodev[[:space:]]+usbfs\$" "/proc/filesystems"; then
	if ! mountpoint -q /proc/bus/usb; then
		print_kernfs_banner
		[ -z "${quietboot}" ] && echo -n " /proc/bus/usb"
		mount -t usbfs procbususb /proc/bus/usb
	fi
fi

if ! "${kernfs_bool}"; then [ -z "${quietboot}" ] && echo "."; fi

# tmpfs
memtotal="$(sed -ne 's/^MemTotal\: \+\([^ ]\+\) kB/\1/g;T;p' /proc/meminfo)"
##[ -n "${memtotal}" ] && tmpsize="-o size=$(( (${memtotal} + 4096) / 8192 ))m"
tmpsize="-o size=500K"
tmpfs_bool="true"
tmpfs_banner="Mounting tmp file systems (tmpfs):"
for path in "/tmp"; do
	if ! mountpoint -q "${path}"; then
		if "${tmpfs_bool}"; then
			[ -z "${quietboot}" ] && echo -n "${tmpfs_banner}"
			tmpfs_bool="false"
		fi
		[ -z "${quietboot}" ] && echo -n " ${path}"
		mount ${tmpsize} -t tmpfs tmpfs "${path}"
		[ "${path}" = "/tmp" ] && mkdir -p /tmp/var /tmp/media /tmp/mnt
	fi
done
if ! "${tmpfs_bool}"; then [ -z "${quietboot}" ] && echo "."; fi

# Remount rootfs with noatime option
mount -o remount,noatime /dev/root

exit 0
