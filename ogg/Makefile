# libogg for FF.  Used by libvorbis only.
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += -Iinclude -I$(FF3PT) \
	-fvisibility=default

SRC := src/bitwise.c
OBJ := $(SRC:.c=.o)

%.o: %.c
	$(C) $(CFLAGS) $< -o$@

libogg-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) $(LD_INSTNAME_LDRPATH) -shared -o$@

clean:
	rm -fv $(OBJ) libogg-ff.$(SO)
