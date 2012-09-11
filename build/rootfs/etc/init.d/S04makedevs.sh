#!/bin/sh
#===============================================================================
#
#  S04makedevs.sh
#
#  Copyright (C) 2008-2009 by Digi International Inc.
#  All rights reserved.
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License version 2 as published by
#  the Free Software Foundation.
#
#
#  !Description: Create device nodes
#
#===============================================================================

set -e

if [ "${1}" != "start" ]; then
	exit 0
fi

MDEV="/sbin/mdev"
MAKEDEVS="/sbin/makedevs"
CONFIG="/etc/makedevs.d/${DEL_PLATFORM}"

# Register mdev as hotplug to create devices.
if [ -f /proc/sys/kernel/hotplug ]; then
	echo > /dev/mdev.seq
	echo "${MDEV}" > /proc/sys/kernel/hotplug
fi

# Create all device nodes scanning /sys.
${MDEV} -s

# Create rest device nodes via configuration file.
if [ -f "${CONFIG}" ]; then
	[ -z "${quietboot}" ] && echo -n "Creating nodes via configuration file... "
	${MAKEDEVS} -d "${CONFIG}" / >/dev/null 2>&1
	[ -z "${quietboot}" ] && echo "done"
fi

# mount storage devices
usbmount
mmc-mount

# fire *add* event for ADC so the nodes are created in case of built-in driver
for i in $(echo /sys/bus/platform/drivers/*adc*/uevent); do
	[ "${i}" = "/sys/bus/platform/drivers/*adc*/uevent" ] && continue
	echo add > $i
done
