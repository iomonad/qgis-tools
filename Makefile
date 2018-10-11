#
# (c) iomonad - <clement@trosa.io>
#  https://github.com/iomonad/igc
#

CC      = gcc
CFLAGS  = -dD -Wall -Wextra -Werror -O2
RM      = /bin/rm
RMFLAGS = -rf
TARGETS = $(WORLD_TARGET)
STRIPER = /usr/bin/strip
STRIPC  = -s

include worldgen/Makefile.mk

all: world

clean:
	$(RM) $(RMFLAGS) $(TARGETS)

.PHONY: world
