#
# (c) iomonad - <clement@trosa.io>
#  https://github.com/iomonad/igc
#

CC      = clang
CFLAGS  = -dD -Wall -Wextra -Werror -O2
RM      = /bin/rm
RMFLAGS = -rf
TARGETS = $(AS_TARGET)
STRIPER = /usr/bin/strip
STRIPC  = -s

include assembler/Makefile.mk

all: assembler

clean:
	$(RM) $(RMFLAGS) $(TARGETS)

.PHONY: assembler
