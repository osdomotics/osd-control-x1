# Place holder for utility shell functions

# Function:    imx51_touch_selection
# Description: read GPIO for touchscreen selection
#       +-------+------------+-----------+
#       | _gpio |  display_1 | display_2 |
#       +-------+------------+-----------+
#       |   0   |  external  |  internal |
#       |   1   |  internal  |  external |
#       +-------+------------+-----------+
imx51_touch_selection() {
	[ -f /sys/class/gpio/export ] || return

	# If second touch is not enabled the GPIO cannot be read.
	# In that case assume _gpio=1, i.e. internal touch connected to display_1.
	if zcat /proc/config.gz | grep -qs 'CONFIG_CCWMX51_SECOND_TOUCH=y'; then
		echo -n 68 > /sys/class/gpio/export
		_gpio="$(cat /sys/class/gpio/gpio68/value)"
		echo -n 68 > /sys/class/gpio/unexport
	else
		_gpio="1"
	fi
	echo "${_gpio}"
}
