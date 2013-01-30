#!/bin/sh

# coap.cgi
# v0.4 2013-01-30 GS (goesta@smekal.at)
#
# this script is part of the Smart-SARAH project
# http://osdomotics.com
#
# Smart-SARAH is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# use internal field separator to split key/value pairs
OLDIFS="$IFS"

COAP_TIMEOUT=15	# coap client stops after that time
WGET_TIMEOUT=15	# timeout for rpl table fetch
CREATE_FORM='1'	# set to something true to create CoAP put forms
		# WARNING: this may be _extremely_ slow !

if [ "$CREATE_FORM" ]
then
# decode CGI data
## this part is derived from work by Philippe Kehl
## http://oinkzwurgl.org/bash_cgi
  # replace all + with whitespace and append %%
  t="${QUERY_STRING//+/ }%%"
  while [ ${#t} -gt 0 -a "${t}" != "%" ]
  do
    v="${v}${t%%\%*}" # digest up to the first %
    t="${t#*%}"       # remove digested part
  # decode if there is anything to decode and if not at end of string
    if [ ${#t} -gt 0 -a "${t}" != "%" ]; then
      h=${t:0:2} # save first two chars
      t="${t:2}" # remove these
      v="${v}"`echo -e \\\\x${h}` # convert hex to special char
    fi
  done
## end of borrowed code
  QUERY_STRING="${v}"
fi

# fetch 6LoWPAN prefix from uboot environment
UB_PREFIX=`ubootenv -p lowpanprefix`
IFS="="
set $UB_PREFIX
RPL_HOST=$2"ff:fe00:1"
IFS="$OLDIFS"

NODE=""
URI=".well-known/core"
METHOD='get'

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
#
### blank queries result in RPL table scan ...
#
if [ -z "$QUERY_STRING" ]
then
  # sed removes html-tags from response
  RPL_DATA=`wget -T $WGET_TIMEOUT http://[$RPL_HOST] -O - |sed -e 's/<[^>]*>/\n/g'`
  if [ -z "$RPL_DATA" ]
  then
    cat <<EOT
<h1>RPL error!</h1>
<p>Could not fetch routing data from RPL host $RPL_HOST</p>
</BODY></HTML>
EOT
    exit
  else
    ### RPL host table
    echo "<h1>RPL host table:</h1><ul>"
    for RPL_PART in $RPL_DATA
    do
      IFS="${OLDIFS}/"
      set $RPL_PART
      if [ "$2" == '128' ]
      then
        NODE=$1
        echo "<li><a href=\"$SCRIPT_NAME?node=$NODE\">$NODE</a></li>"
      fi
    done
    echo "</ul>"
  fi
else
#
### process query data ...
#
  IFS="${IFS}&"
  for field in $QUERY_STRING
  do
    IFS="${OLDIFS}="
    set $field
    IFS="${OLDIFS}"
  
    case $1 in
      node) NODE=$2 ;;
      uri) URI=$2 ;;
      method) METHOD=$2 ;;
      *) PARAMS="$PARAMS$1=$2,"
    esac
  done
#
### perform CoAP get/put request
#
  if [ "$METHOD" == 'get' ]
  then
    VALUE=`coap-client -B $COAP_TIMEOUT -m get coap://[${NODE}]:5683/${URI}`
    if [ "$URI" == '.well-known/core' ]
    then
      #
      ### create resource table
      #
      echo "<H1>CoAP resources</H1>Node <a href=\"$SCRIPT_NAME?node=$NODE\">$NODE</a> :<ul>"
      IFS="${OLDIFS};,<>"
      for RESOURCE in $VALUE
      do
        if [ "${RESOURCE:0:1}" == '/' ]
        then
          echo "<li><a href=\"$SCRIPT_NAME?node=$NODE&uri=$RESOURCE\">$RESOURCE</a></li>"
        fi
      done
      echo "</ul>"
    else
      #
      ### show resource value
      #
      cat <<EOT
      <H1>CoAP get result:</H1>
      Node: <a href="/cgi-bin/coap.cgi?node=$NODE">$NODE</a><BR>
      Uri: $URI<BR>
      Value: $VALUE<BR>
EOT
      if [ "$CREATE_FORM" ]
      then
        IFS=",{}"
        for PROP in $VALUE
        do
          if [ "${#PROP}" -gt 1 ]
          then
            IFS=': "'
            set $PROP
            TITLE=$2
            STATE=$5
            cat <<EndOfForm
            <FORM METHOD="GET" ACTION="$SCRIPT_NAME">
            $TITLE=
            <INPUT TYPE="HIDDEN" NAME="node" VALUE="$NODE">
            <INPUT TYPE="HIDDEN" NAME="uri" VALUE="$URI">
            <INPUT TYPE="HIDDEN" NAME="method" VALUE="put">
            <INPUT TYPE="TEXT" NAME="$TITLE" VALUE="$STATE">
            <INPUT TYPE="SUBMIT" VALUE="PUT">
            </FORM>
EndOfForm
          fi
        done
      else
        IFS="${OLDIFS}="
        RAW_IP=`ubootenv -p ipaddr`
        set $RAW_IP
        IP=$2
        echo "<p>You may change values by an URL like<BR> 'http://${IP}${SCRIPT_NAME}?node=$NODE&uri=$URI&method=put&amp;&lt;label&gt;=&lt;value&gt;'"
      fi
    fi
  elif [ "$METHOD" == 'put' ]
  then
    IFS="${OLDIFS},"
    for PARAMETER in $PARAMS
    do
      if [ ${#PARAMETER} -gt 1 ]
      then
        RESPONSE=`coap-client -B $COAP_TIMEOUT -m put coap://[${NODE}]:5683/${URI} -e "$PARAMETER" 2>&1`
        ERRLVL=$?
        if [ -n "$RESPONSE" ]
        then
          cat <<EndOfPutError
          <H1>CoAP put went wrong!</H1>
          CoAP Response: $RESPONSE<BR>
          CoAP Errorlevel: $ERRLVL<BR>
          see <a href="http://tools.ietf.org/html/draft-ietf-core-coap-08#page-33">CoAP draft</a> for response codes<BR>
EndOfPutError
        else
          cat <<EndOfPut
            <H1>CoAP put ok.</H1>
            Node: $NODE<BR>
            URI: $URI<BR>
            Data: $PARAMETER<BR>
EndOfPut
        fi 
      fi
    done
  else
    cat <<EndOfMethodError
    <H1>Illegal method "$METHOD"!</H1>
    Try 'method=get' or 'method=put&amp;&lt;label&gt;=&lt;value&gt;'
EndOfMethodError
  fi
fi
echo "</BODY></HTML>"
