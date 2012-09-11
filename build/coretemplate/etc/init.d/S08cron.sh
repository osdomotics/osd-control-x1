#-------------------------------------------
#! /bin/sh
# cron init
  echo -n "Starting cron... ";
  /bin/mkdir /var/spool 
  /bin/mkdir /var/spool/cron
  /bin/mkdir /var/spool/cron/crontabs
  /usr/sbin/crond &
  echo "done";
#end
#--------------------------------------------
