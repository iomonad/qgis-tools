#
# (c) iomonad - <clement@trosa.io>
#  https://github.com/iomonad/igc
#

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -O2
RM      = /bin/rm
RMFLAGS = -rf
TARGETS = $(WORLD_TARGET)
STRIPER = /usr/bin/strip
STRIPC  = -s

include worldgen/world.mk

all: world

clean:
	$(RM) $(RMFLAGS) $(TARGETS)

.PHONY: world
