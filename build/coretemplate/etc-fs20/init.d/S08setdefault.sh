#-------------------------------------------
#! /bin/sh
# GPIO Kernel module
  echo -n "testing set default... ";
  /sbin/setdefault.sh
  echo "done";
  echo -n "init tmp files... ";
  /sbin/ubootenv -p relay1 > /tmp/relay
  /sbin/ubootenv -p relay2 >> /tmp/relay
  /sbin/ubootenv -p relay3 >> /tmp/relay
  /sbin/ubootenv -p relay4 >> /tmp/relay
  /sbin/ubootenv -p relay5 >> /tmp/relay
  /sbin/ubootenv -p relay6 >> /tmp/relay
  /sbin/ubootenv -p relay7 >> /tmp/relay
  /sbin/ubootenv -p relay8 >> /tmp/relay
  /bin/chown nobody /tmp/relay
  echo "done";

#end
#--------------------------------------------
