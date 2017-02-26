# libmpc for FF
# Simon Zolin, 2017

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-Iinclude -Ilibmpcenc -Ilibmpcpsy -Ilibwavformat
LDFLAGS += -lm

SRC_ENCLIB := \
	common/crc32.c \
	common/huffman-bcl.c \
	libmpcenc/analy_filter.c \
	libmpcenc/bitstream.c \
	libmpcenc/encode_sv7.c \
	libmpcenc/huffsv7.c \
	libmpcenc/quant.c

SRC_DECLIB := \
	libmpcdec/huffman.c \
	libmpcdec/mpc_bits_reader.c \
	libmpcdec/mpc_decoder.c \
	libmpcdec/mpc_demux.c \
	libmpcdec/requant.c \
	libmpcdec/streaminfo.c \
	libmpcdec/synth_filter.c

SRC_COMM := \
	common/tags.c

SRC_PSY := \
	libmpcpsy/ans.c \
	libmpcpsy/cvd.c \
	libmpcpsy/fft4g.c \
	libmpcpsy/fft_routines.c \
	libmpcpsy/profile.c \
	libmpcpsy/psy.c \
	libmpcpsy/psy_tab.c

SRC_WF := \
	libwavformat/input.c \
	libwavformat/output.c

SRC_DEC := \
	mpcdec/mpcdec.c \
	libmpcdec/mpc_reader.c

SRC_ENC := \
	common/fastmath.c \
	mpcenc/keyboard.c \
	mpcenc/mpcenc.c \
	mpcenc/pipeopen.c \
	mpcenc/stderr.c \
	mpcenc/wave_in.c \
	mpcenc/winmsg.c

OBJ := mpc-ff.o $(SRC_DECLIB:.c=.o)
OBJ_DEC := $(SRC_DEC:.c=.o) $(SRC_COMM:.c=.o) $(SRC_DECLIB:.c=.o) $(SRC_WF:.c=.o)
OBJ_ENC := $(SRC_ENC:.c=.o) $(SRC_COMM:.c=.o) $(SRC_ENCLIB:.c=.o) $(SRC_PSY:.c=.o)

%.o: $(FF3PT)/vorbis/%.c
	$(C) $(CFLAGS) -I$(FF3PT)/vorbis $< -o$@

%.o: %.c $(wildcard lib/*.h)
	$(C) $(CFLAGS) $< -o$@

all: libmpc-ff.$(SO)

clean:
	rm -fv $(OBJ) $(OBJ_ENC) $(OBJ_DEC) libmpc-ff.$(SO) mpcdec-bin mpcenc-bin

%.o: $(FF3PT)/musepack/%.c
	$(C) $(CFLAGS) -I$(FF3PT)/musepack $< -o$@

libmpc-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) -shared $(LDFLAGS) -o$@

mpcdec-bin: $(OBJ_DEC)
	$(LD) $(OBJ_DEC) $(LDFLAGS) -o$@

mpcenc-bin: $(OBJ_ENC)
	$(LD) $(OBJ_ENC) $(LDFLAGS) -o$@
