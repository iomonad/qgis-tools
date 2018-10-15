#
# (c) iomonad - <clement@trosa.io>
#  https://github.com/iomonad/igc
#

CC      = gcc
CFLAGS  = -dD -Wall -Wextra -Werror -O2
RM      = /bin/rm
RMFLAGS = -rf
TARGETS =
STRIPER = /usr/bin/strip
STRIPC  = -s

all:

clean:
	$(RM) $(RMFLAGS) $(TARGETS)

.PHONY:
