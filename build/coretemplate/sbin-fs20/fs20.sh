#! /bin/sh
# FS20 - UART-FS20 Gateway send tool

VERSION=0.01

SERPORT=/dev/ttyFIM0
BAUD=9600

usage()
{
	echo `basename $0`" - V${VERSION} by Koarl, Harald, Nov 2011"
	echo "usage: " `basename $0`" {-s serialport} {-b baud} {-d(ebug)} {-v(erbose)} -c:COMMAND"
}

# main

if [ -z "$1" ]; then 
	usage 
	exit 1
fi

# parse cmd line parameters

while [ -n "$1" ]; do
	OPT="`echo $1|cut -b1,2`"
	case $OPT in
	"-s")
		if [ -z "`echo $1|cut -b3 `" ]; then
			shift
			SERPORT="$1"
		else
			SERPORT="`echo $1|cut -b3-`"
		fi	
	;;
	"-b")
		if [ -z "`echo $1|cut -b3`" ]; then
			shift
			BAUD="$1"
		else
			BAUD="`echo $1|cut -b3-`"
		fi
	;;
	"-d")
		DEBUG=YES
	;;
	"-v")
		VERSBOSE=YES
	;;
	"-c")
		COMMAND="`echo $1|cut -b4-`"
	;;
	*)
		usage
		exit 1
	;;
	esac
	shift
done

# set serial interface
stty -F $SERPORT $BAUD -echo

# send command
if [ -n "$COMMAND" ]; then
	echo -e "$COMMAND" > $SERPORT
#	read REPLY < $SERPORT
#	echo $REPLY
fi

exit 0

