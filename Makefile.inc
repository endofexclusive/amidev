CFLAGS?= -march=68000 -fomit-frame-pointer -g -Os -mpcrel -mshort -std=gnu99 -Wall -Wextra
CPPFLAGS+= -I$(AMIDEV)/include
ASFLAGS = -quiet -phxass -m68000 -Felf

# File to connect with GDB.
PTY?= $(AMIDEV)/slave_gdb
TARGET?=m68k-elf-

CC = $(TARGET)gcc
LD = $(TARGET)gcc
AS = vasmm68k_mot
GDB = $(TARGET)gdb
SIZE = $(TARGET)size
OBJDUMP = $(TARGET)objdump
OBJCOPY = $(TARGET)objcopy
LDSCRIPT = $(AMIDEV)/a500.ld

VPATH+=$(AMIDEV)
OBJS := $(SSRCS:.s=.o)
OBJS := $(OBJS) $(CSRCS:.c=.o)

$(PROJ): $(OBJS) $(LDSCRIPT)
	$(LD) -nostdlib $(OBJS) -T $(LDSCRIPT) -o $@ -Wl,-Map=$@.map

$(PROJ).asm: $(PROJ)
	$(OBJDUMP) -d $< > $@

.PHONY: size
size: $(OBJS)
	$(SIZE) $^ -t --common

.PHONY: gdb
gdb: $(PROJ)
	$(GDB) $(PROJ) -ex "target remote $(PTY)" -b 230400 -x $(AMIDEV)/gdb.script

clean:
	rm -f $(OBJS) $(PROJ) $(PROJ).asm $(PROJ).map $(CLEANFILES)

DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

%.o : %.c
%.o : %.c $(DEPDIR)/%.d
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(CSRCS)))

