#-------------------------------------------
#! /bin/sh
# GPIO Kernel module
  echo -n "Starting ureboot demon... ";
  /bin/ureboot&
  echo "ok";
  echo -n "Starting urelay demon...";
  /bin/urelay&
  echo "ok";

#end
#--------------------------------------------
