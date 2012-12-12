#! /bin/sh
echo -n "start slip .. ";
mkdir /dev/net
ln -s /dev/tun /dev/net/tun
# disable autoconfiguration, enable eth0
echo 0 > /proc/sys/net/ipv6/conf/default/accept_ra
echo 1 > /proc/sys/net/ipv6/conf/eth0/accept_ra

# get panid from uboot
if ! ENV="$(ubootenv -p 'panid' 2>/dev/null)"; then
		echo "  [FAIL] unable to read pamid from NVRAM"
		return
	fi
	panid="$(echo ${ENV} | sed 's!panid=!!g')"
# get lowpanprefix from uboot
if ! ENV="$(ubootenv -p 'lowpanprefix' 2>/dev/null)"; then
		echo "  [FAIL] unable to read lowpanprefix from NVRAM"
		return
	fi
	lowpanprefix="$(echo ${ENV} | sed 's!lowpanprefix=!!g')"
# start daemon
#tunslip6 -B 115200 -L -v3 -s ttyFIM0 aaaa::1/64 &
tunslip6 -B 38400 -L -v3 -s ttyFIM0 ${lowpanprefix}1/64 &
sleep 10
ifconfig tun0 inet  up
ifconfig tun0 fe80::1/64
ifconfig tun0 ${lowpanprefix}1/64

# get mac address from uboot and calculate devaddr
if ! ENV="$(nvram print module ethaddr1 2>/dev/null)"; then
		echo "  [FAIL] unable to read ethaddr1 from NVRAM"
		return
	fi
mac2=`echo $ENV|sed 's/://g'|cut -d= -f2|cut -b 3-6`
mac3=`echo $ENV|sed 's/://g'|cut -d= -f2|cut -b 7-12`
mac2d=`echo $mac2|cut -b 1-2`:`echo $mac2|cut -b 3-4`
mac3d=`echo $mac3|cut -b 1-2`:`echo $mac3|cut -b 3-6`
devaddr="02"$mac2d"ff:fe"$mac3d
# get ipprefix from uboot
echo "set eth0 ipv6 address"
if ! ENV="$(ubootenv -p 'ipprefix' 2>/dev/null)"; then
		echo "  [FAIL] unable to read ipprefix from NVRAM"
		return
	fi
	ipprefix="$(echo ${ENV} | sed 's!ipprefix=!!g')"

ifconfig eth0 ${ipprefix}${devaddr}/64
echo 1 > /proc/sys/net/ipv6/conf/all/forwarding
sleep 2
# bird ripng
/sbin/buildbirdconf.sh
sleep 2
bird -s var/run/bird6.ctl -c /etc/bird.conf
echo -n "done ";
#end

