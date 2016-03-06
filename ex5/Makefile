PROJ := ex5
CSRCS := $(PROJ).c
SSRCS := head.s

CPPFLAGS = -DCUSTOM_AS_GLOBAL_REG=1
CFLAGS = -march=68000 -g -O1 -mshort
CFLAGS+= -Wall -Wextra -std=gnu99
all: $(PROJ) $(PROJ).asm
$(PROJ).c: clist.c
AMIDEV := ..

include $(AMIDEV)/Makefile.inc

