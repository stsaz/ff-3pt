# libFLAC for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-funroll-loops \
	-I. -Isrc/libFLAC/include -Iinclude -I$(FF3PT)/flac \
	-DHAVE_CONFIG_H -DFLAC_EXP -D_FORTIFY_SOURCE=2 \
	-Wall -Wextra -Wstrict-prototypes -Waggregate-return \
	-Wcast-align -Wnested-externs -Wshadow -Wundef -Wunreachable-code \
	-Winline -Wdeclaration-after-statement \
	-Wno-unused-function -Wno-unused-variable -Wno-unused-parameter \
	-Wno-implicit-fallthrough

LDFLAGS += $(LD_LMATH)

SRC := \
	src/libFLAC/bitmath.c \
	src/libFLAC/bitreader.c \
	src/libFLAC/bitwriter.c \
	src/libFLAC/cpu.c \
	src/libFLAC/crc.c \
	src/libFLAC/fixed.c \
	src/libFLAC/fixed_intrin_sse2.c \
	src/libFLAC/fixed_intrin_ssse3.c \
	src/libFLAC/float.c \
	src/libFLAC/format.c \
	src/libFLAC/lpc.c \
	src/libFLAC/lpc_intrin_sse.c \
	src/libFLAC/lpc_intrin_sse2.c \
	src/libFLAC/lpc_intrin_sse41.c \
	src/libFLAC/lpc_intrin_avx2.c \
	src/libFLAC/md5.c \
	src/libFLAC/memory.c \
	src/libFLAC/stream_decoder.c \
	src/libFLAC/stream_encoder.c \
	src/libFLAC/stream_encoder_intrin_sse2.c \
	src/libFLAC/stream_encoder_intrin_ssse3.c \
	src/libFLAC/stream_encoder_intrin_avx2.c \
	src/libFLAC/stream_encoder_framing.c \
	src/libFLAC/window.c
OBJ := FLAC-ff.o $(SRC:.c=.o)

%.o: $(FF3PT)/flac/%.c
	$(C) $(CFLAGS) $<  -o$@

%.o: %.c $(wildcard include/*.h) $(wildcard include/FLAC/*.h) $(wildcard src/libFLAC/include/private/*.h) $(wildcard src/libFLAC/include/protected/*.h)
	$(C) $(CFLAGS) $<  -o$@

libFLAC-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -shared -o$@

clean:
	rm -fv $(OBJ) libFLAC-ff.$(SO)
