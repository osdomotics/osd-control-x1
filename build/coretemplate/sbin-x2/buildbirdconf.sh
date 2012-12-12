#! /bin/sh

echo "set default bird.conf"
eth0ip="$(ifconfig eth0 | grep 'inet addr:' | awk '{ print $2 }'|  sed 's!addr:!!g')"
eth0ip6="$(ifconfig eth0 | grep ':Global' | head -n1 | awk '{ print $3 }'|  sed 's!addr:!!g'| sed 's!/64!!g')"
tun0ip6="$(ifconfig tun0 | grep ':Global' | head -n1 | awk '{ print $3 }'|  sed 's!addr:!!g'| sed 's!/64!!g')"
rm /etc/bird.conf

echo "# bird.conf
#
# dynamic routing configuration
#
# v0.1 2011-10-21 GS (goesta@smekal.at)

# global parameters

log syslog all;
debug protocols { routes, events, packets };

router id ${eth0ip};

## routing protocols

# device parameters
protocol device {
  scan time 10;
  primary \"eth0\" ${eth0ip6};
  primary \"tun0\" ${tun0ip6};
}

protocol direct{
  interface \"*\";
}

# kernel routing table
protocol kernel {
  scan time 10;
  persist yes;
  learn yes;
  import all;
  export all;
}

# router advertisments
protocol radv {
  interface \"tun0\";
  interface \"eth0\";
}

# dynamic routing using RIPng
protocol rip myrip{
  authentication none;
#  authentication md5;
#  password \"verysecure\";
  honor neighbor;
  import all;
  export all;
  interface \"eth0\" { metric 1; };
}

" > /etc/bird.conf

exit 0



	
