# libvorbis, libvorbisenc for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-Ilib -Iinclude -I$(FF3PT) \
	-DUSE_MEMORY_H -DVORB_EXP \
	-Wall -Wextra
LDFLAGS += -L$(FF3PT)/_bin/$(OS)-$(ARCH) -lm

ifeq ($(OS),linux)
CFLAGS += -DHAVE_ALLOCA_H=1 -ffast-math

else ifeq ($(OS),bsd)
CFLAGS += -ffast-math
endif

SRC := \
	lib/mdct.c \
	lib/smallft.c \
	lib/block.c \
	lib/envelope.c \
	lib/window.c \
	lib/lsp.c \
	lib/lpc.c \
	lib/analysis.c \
	lib/synthesis.c \
	lib/psy.c \
	lib/info.c \
	lib/floor1.c \
	lib/floor0.c \
	lib/res0.c \
	lib/mapping0.c \
	lib/registry.c \
	lib/codebook.c \
	lib/sharedbook.c \
	lib/lookup.c \
	lib/bitrate.c
OBJ := vorbis-ff.o $(SRC:.c=.o)

SRC_ENC := lib/vorbisenc.c
OBJ_ENC := vorbisenc-ff.o $(SRC_ENC:.c=.o)

%.o: $(FF3PT)/vorbis/%.c
	$(C) $(CFLAGS) -I$(FF3PT)/vorbis $< -o$@

%.o: %.c $(wildcard lib/*.h)
	$(C) $(CFLAGS) $< -o$@

all:
	cat $(FF3PT)/vorbis/*.patch | patch -p1
	$(MAKE) -f $(firstword $(MAKEFILE_LIST)) libvorbis-ff.$(SO) libvorbisenc-ff.$(SO)

clean:
	rm -fv $(OBJ) $(OBJ_ENC) libvorbis-ff.$(SO) libvorbisenc-ff.$(SO)

libvorbis-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) $(LD_INSTNAME_LDRPATH) -logg-ff -shared -o$@

libvorbisenc-ff.$(SO): $(OBJ_ENC) libvorbis-ff.$(SO)
	$(LD) $(OBJ_ENC) $(LDFLAGS) $(LD_INSTNAME_LDRPATH) -logg-ff -L. -lvorbis-ff -shared -o$@
