#!/bin/sh
#===============================================================================
#
#  S07syslogd.sh
#
#  Copyright (C) 2008 by Digi International Inc.
#  All rights reserved.
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License version 2 as published by
#  the Free Software Foundation.
#
#
#  !Revision:    $Revision: 1.8 $:
#  !Description: Start syslogd
#
#===============================================================================

set -e

SYSLOGD="/sbin/syslogd"
PIDFILE="/var/run/syslogd.pid"

[ -x "${SYSLOGD}" ] || exit 0

for dir in "/var/log" "/var/run"; do
	[ -d "${dir}" ] || mkdir -p "${dir}"
done

case "${1}" in
start)
	[ -z "${quietboot}" ] && echo -n "Starting syslog daemon: "
	if [ -s "${PIDFILE}" ]; then
		pid="$(cat ${PIDFILE})"
		if kill -0 "${pid}" 2>/dev/null; then
			[ -z "${quietboot}" ] && echo " already running."
			exit 0
		fi
	fi
	start-stop-daemon --start --background --pidfile "${PIDFILE}" --make-pidfile --exec "${SYSLOGD}" -- -n -D
	[ -z "${quietboot}" ] && echo "OK"
	;;
stop)
	echo -n "Stopping syslog daemon: "
	start-stop-daemon --stop --quiet --pidfile "${PIDFILE}"
	rm "${PIDFILE}"
	echo "OK"
	;;
*)
	echo "Usage: $0 {start|stop}"
	exit 1
	;;
esac
