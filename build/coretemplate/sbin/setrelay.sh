#! /bin/sh
name="relay1"
relay=`/sbin/ubootenv -p $name`
if [ "$relay" =  "$name=1" ] 
	then
	echo "$name set to 1"
	/bin/relayi2c -a 1
	else
	/bin/relayi2c -a 0
fi
name="relay2"
relay=`/sbin/ubootenv -p $name`
if [ "$relay" =  "$name=1" ] 
	then
	echo "$name set to 1"
	/bin/relayi2c -b 1
	else
	/bin/relayi2c -b 0
fi
name="relay3"
relay=`/sbin/ubootenv -p $name`
if [ "$relay" =  "$name=1" ] 
	then
	echo "$name set to 1"
	/bin/relayi2c -c 1
	else
	/bin/relayi2c -c 0
fi
name="relay4"
relay=`/sbin/ubootenv -p $name`
if [ "$relay" =  "$name=1" ] 
	then
	echo "$name set to 1"
	/bin/relayi2c -d 1
	else
	/bin/relayi2c -d 0
fi
name="relay5"
relay=`/sbin/ubootenv -p $name`
if [ "$relay" =  "$name=1" ] 
	then
	echo "$name set to 1"
	/bin/relayi2c -e 1
	else
	/bin/relayi2c -e 0
fi
name="relay6"
relay=`/sbin/ubootenv -p $name`
if [ "$relay" =  "$name=1" ] 
	then
	echo "$name set to 1"
	/bin/relayi2c -f 1
	else
	/bin/relayi2c -f 0
fi
name="relay7"
relay=`/sbin/ubootenv -p $name`
if [ "$relay" =  "$name=1" ] 
	then
	echo "$name set to 1"
	/bin/relayi2c -g 1
	else
	/bin/relayi2c -g 0
fi
name="relay8"
relay=`/sbin/ubootenv -p $name`
if [ "$relay" =  "$name=1" ] 
	then
	echo "$name set to 1"
	/bin/relayi2c -h 1
	else
	/bin/relayi2c -h 0
fi
exit 0



	
