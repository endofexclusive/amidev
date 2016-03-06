PROJ := ex2
CSRCS := $(PROJ).c
SSRCS := head.s

CPPFLAGS = -DCUSTOM_AS_GLOBAL_REG=1
all: $(PROJ) $(PROJ).asm
AMIDEV := ..

include $(AMIDEV)/Makefile.inc

