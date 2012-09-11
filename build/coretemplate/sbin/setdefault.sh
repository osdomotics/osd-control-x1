#! /bin/sh
defaultpin=`/bin/gpio`
if [ "$defaultpin" = 0 ] 
	then
	echo "set default! network config"
	/sbin/ubootenv -a /etc/network.conf
	/bin/chmod +s /bin/relayi2c
	/bin/chmod +s /bin/ureboot
	/bin/chmod +s /sbin/ubootenv
fi
exit 0



	
