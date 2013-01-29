#!/bin/sh

# coap.cgi
#
# v0.2 2013-01-25 GS (goesta@smekal.at)

# use internal field separator to split key/value pairs
OLDIFS="$IFS"
IFS="${IFS}&"

# this should come from the environment!
RPL_HOST=`ubootenv -p lowpanprefix | cut -d '=' -f 2`"ff:fe00:1"
NODE=""
URI=".well-known/core"

# we issue a header anyway, the content depends on the context ...
cat <<EOT
Content-Type: text/html

<HTML>
<HEAD><TITLE>CoAP CGI</TITLE></HEAD>
<BODY>
EOT

# check input data length ... URIs are not linited in length, but in our case
# 512 chars might be enough 
# (didn't somebody say something similar about RAM once?)
if [ ${#QUERY_STRING} -gt 512 ]
then
  cat <<EOT
  <h1>URI error!</h1>
  <p>Your query exceeds 512 characters, this is quite odd.</p>
  </BODY></HTML>
EOT
  exit
fi
# blank queries result in RPL table scan ...
if [ -z $QUERY_STRING ]
then
  RPL_DATA=`wget http://[$RPL_HOST] -O - |sed -e 's/<[^>]*>/\n/g'`
  if [ -z "$RPL_DATA" ]
  then
    cat <<EOT
<h1>RPL error!</h1>
<p>Could not fetch routing data from RPL host $RPL_HOST</p>
</BODY></HTML>
EOT
    exit
  else
    echo "<h1>RPL host table:</h1><ul>"
    for RPL_PART in $RPL_DATA
    do
      SLASH_POS=`expr index "$RPL_PART" '/' - 1`
      if [ "$SLASH_POS" -gt 0 ]
      then
        NODE=${RPL_PART:0:$SLASH_POS}
        echo "<li><a href=\"/cgi-bin/coap.cgi?node=$NODE\">$NODE</a></li>"
      fi
    done
    echo "</ul>"
  fi

else
  # process query data ...
  for field in $QUERY_STRING
  do
    IFS="${OLDIFS}="
    set $field
    IFS="${OLDIFS}"
  
    case $1 in
      node) NODE=$2 ;;
      uri) URI=$2 ;;
      *) echo "<b>Warning! $1 is not a valid parameter!</b>" ;;
    esac
  done
  
  VALUE=`coap-client -m get coap://[${NODE}]:5683/${URI}`
  if [ "$URI" == '.well-known/core' ]
  then
    echo "<p>CoAP resources:<ul>"
    IFS="${OLDIFS};,<>"
    for RESOURCE in $VALUE
    do
      if [ "${RESOURCE:0:1}" == '/' ]
      then
        echo "<li><a href=\"/cgi-bin/coap.cgi?node=$NODE&uri=$RESOURCE\">$RESOURCE</a></li>"
      fi
    done
    echo "</ul>"
  else
    cat <<EOT
    <P>CoAP Result:</p>
    Node: $NODE<BR>
    Uri: $URI<BR>
    Value: $VALUE<BR>
EOT
  fi
fi
echo "</BODY></HTML>"