# libmp3lame for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-DHAVE_CONFIG_H -I. -Iinclude -Ilibmp3lame -I$(FF3PT)/mp3lame \
	-ffast-math -funroll-loops -Wall

SRC := \
	libmp3lame/bitstream.c \
	libmp3lame/encoder.c \
	libmp3lame/fft.c \
	libmp3lame/gain_analysis.c \
	libmp3lame/lame.c \
	libmp3lame/newmdct.c \
	libmp3lame/presets.c \
	libmp3lame/psymodel.c \
	libmp3lame/quantize.c \
	libmp3lame/quantize_pvt.c \
	libmp3lame/reservoir.c \
	libmp3lame/set_get.c \
	libmp3lame/tables.c \
	libmp3lame/takehiro.c \
	libmp3lame/util.c \
	libmp3lame/vbrquantize.c \
	libmp3lame/VbrTag.c \
	libmp3lame/version.c \
	libmp3lame/vector/xmm_quantize_sub.c
OBJ := lame-ff.o $(SRC:.c=.o)

all: libmp3lame-ff.$(SO)

%.o: $(FF3PT)/mp3lame/%.c
	$(C) $(CFLAGS) $< -o$@

%.o: %.c $(wildcard include/*.h) $(wildcard libmp3lame/*.h) $(wildcard libmp3lame/vector/*.h)
	$(C) $(CFLAGS) $<  -o$@

libmp3lame/vector/xmm_quantize_sub.o: libmp3lame/vector/xmm_quantize_sub.c $(wildcard include/*.h) $(wildcard libmp3lame/*.h) $(wildcard libmp3lame/vector/*.h)
	$(C) $(CFLAGS) -msse $<  -o$@

libmp3lame-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -shared -o$@

clean:
	rm -fv $(OBJ) libmp3lame-ff.$(SO)
