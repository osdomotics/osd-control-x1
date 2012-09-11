# Per platform config files used in S04makedevs.sh script.
# Use the file according to your platform to configure device nodes.

# Device table entries take the form of:
# <name> <type> <mode> <uid> <gid> <major> <minor> <start> <inc> <count>
# Where:
#   * name is the file name.
#   * type can be one of:
#	f       A regular file
#	d       Directory
#	c       Character special device file
#	b       Block special device file
#	p       Fifo (named pipe)
#   * uid is the user id for the target file.
#   * gid is the group id for the target file.
# The rest of the entries (major, minor, etc) apply to device special files.
# A '-' may be used for blank entries.
#
# Example:
#<name>   <type><mode><uid><gid><major><minor><start><inc><count>
#/dev/hda   b    640    0    0    3       1      1     1    15
