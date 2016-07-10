# libvorbis, libvorbisenc for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-Ilib -Iinclude -I$(FF3PT) \
	-DUSE_MEMORY_H -DVORB_EXP \
	-Wall -Wextra
LDFLAGS += -L$(FF3PT)/$(OS)-$(ARCH)

ifneq ($(OS),win)
CFLAGS += -DHAVE_ALLOCA_H=1 -ffast-math
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

all: libvorbis-ff.$(SO) libvorbisenc-ff.$(SO)

clean:
	rm -fv $(OBJ) $(OBJ_ENC) libvorbis-ff.$(SO) libvorbisenc-ff.$(SO)

libvorbis-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -shared -logg-ff -o$@

libvorbisenc-ff.$(SO): $(OBJ_ENC)
	$(LD) $(OBJ_ENC) $(LDFLAGS) -shared -logg-ff -L. -lvorbis-ff  -o$@