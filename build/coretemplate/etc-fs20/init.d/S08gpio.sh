#-------------------------------------------
#! /bin/sh
# GPIO Kernel module
  echo -n "Starting GPIO kernel modul... ";
  /sbin/insmod /lib/modules/2.6.28.10/extra/gpio.ko
  echo "done";
#end
# i2c reset
  echo -n "i2c GPIO reset... ";
  /bin/relayi2c
  echo "done";
#end
#--------------------------------------------
