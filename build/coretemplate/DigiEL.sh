#######################################################################
#
#  Copyright 2008-2009 by Harald Krippel.
#  All rights reserved.
#  
#######################################################################

#/***************************************************************************
# *                                                                         *
# *   This program is free software; you can redistribute it and/or modify  *
# *   it under the terms of the GNU General Public License as published by  *
# *   the Free Software Foundation; either version 2 of the License, or     *
# *   (at your option) any later version.                                   *
# *                                                                         *
# ***************************************************************************/

# --- Configuration Settings End --------------------------------------

echo "Starting DigiEL-5.2 Configuration"
echo "=============================="
echo

#export CC="arm-linux-gcc"

PATH=~/digi/digiel5.7/x-tools/arm-unknown-linux-uclibcgnueabi/bin/:$PATH
export PATH

echo $CC
echo -e "\n"
echo $PATH

echo "========= end =================="
