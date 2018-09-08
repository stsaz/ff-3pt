# libmad for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-I. -I$(FF3PT)/mad \
	-DHAVE_CONFIG_H -DFPM_64BIT -Wall -fforce-addr -fthread-jumps -fcse-follow-jumps -fcse-skip-blocks -fexpensive-optimizations -fregmove -fschedule-insns2

ifeq ($(OS),win)
CFLAGS += -DDLL_EXPORT
endif
CFLAGS += -fvisibility=default

SRC := \
	bit.c \
	fixed.c \
	frame.c \
	huffman.c \
	layer12.c \
	layer3.c \
	stream.c \
	synth.c \
	timer.c
OBJ := $(SRC:.c=.o)

%.o: %.c $(wildcard ./*.h)
	$(C) $(CFLAGS) $<  -o$@

libmad-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) $(LD_INSTNAME_LDRPATH) -shared -o$@

clean:
	rm -fv $(OBJ) libmad-ff.$(SO)
