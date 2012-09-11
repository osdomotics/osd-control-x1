#!/bin/sh
#===============================================================================
#
#  S40networking.sh
#
#  Copyright (C) 2009 by Digi International Inc.
#  All rights reserved.
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License version 2 as published by
#  the Free Software Foundation.
#
#
#  !Description: Configure network (set DNS, start interfaces)
#
#===============================================================================

resolvconf=/var/run/resolv.conf
[ -n "${quietboot}" ] && tonull=">/dev/null"

print_dns_banner() {
	if [ -z "${printed}" ]; then
		[ -z "${quietboot}" ] && echo -n "  Registering DNS Servers:"
		printed="y"
	fi
}

register_dns() {
	if ! ENV="$(ubootenv -p 'dnsip dnsip2' 2>/dev/null)"; then
		echo "  [FAIL] register_dns: ubootenv unable to read NVRAM"
		return
	fi
	echo "# Automatically generated" > ${resolvconf}
	dnsip="$(echo ${ENV} | sed 's/dnsip=\(.*\) .*/\1/')"
	if [ "${dnsip}" != "0.0.0.0" ]; then
		print_dns_banner
		echo "nameserver ${dnsip}" >> ${resolvconf}
		[ -z "${quietboot}" ] && echo -n " ${dnsip}"
	fi
	dnsip2="$(echo ${ENV} | sed 's/.*dnsip2=\(.*\)/\1/')"
	if [ "${dnsip2}" != "0.0.0.0" ]; then
		print_dns_banner
		echo "nameserver ${dnsip2}" >> ${resolvconf}
		[ -z "${quietboot}" ] && echo -n " ${dnsip2}"
	fi
	if [ -n "${printed}" ]; then
		[ -z "${quietboot}" ] && echo "."
	fi
}

## Set hostname (priority: config file, then platform name, then 'localhost')
set_hostname() {
	if [ -f /etc/hostname ]; then
		hostname -F /etc/hostname
	elif [ -n "${DEL_PLATFORM}" ]; then
		hostname "${DEL_PLATFORM}"
	else
		hostname localhost
	fi
}

[ -d "/var/run" ] || mkdir -p "/var/run"

case "$1" in
start|"")
	[ -z "${quietboot}" ] && echo "Starting network."
	register_dns
	set_hostname
	eval ifup -a ${tonull}
	;;
stop)
	[ -z "${quietboot}" ] && echo "Stopping network."
	eval ifdown -a ${tonull}
	rm -f ${resolvconf}
	;;
*)
	echo "Usage: $0 {start stop}"
	exit 1
	;;
esac
