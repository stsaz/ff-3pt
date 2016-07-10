# libMAC for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-DHAVE_CONFIG_H -I. -I./api -I./common -I./check -I./lz -I./rangecoder -I./lzma -I./delta -I./simple -I../common -I$(FF3PT)/lzma \
	-DTUKLIB_SYMBOL_PREFIX=lzma_ \
	-pthread -fvisibility=hidden -Wall -Wextra -Wvla -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-aliasing -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Wlogical-op -Waggregate-return -Wstrict-prototypes -Wold-style-definition -Wmissing-prototypes -Wmissing-declarations -Wmissing-noreturn -Wredundant-decls

SRC := ../common/tuklib_physmem.c \
	../common/tuklib_cpucores.c \
	\
	./common/common.c \
	./common/block_util.c \
	./common/easy_preset.c \
	./common/filter_common.c \
	./common/hardware_physmem.c \
	./common/index.c \
	./common/stream_flags_common.c \
	./common/vli_size.c \
	./common/alone_encoder.c \
	./common/block_buffer_encoder.c \
	./common/block_encoder.c \
	./common/block_header_encoder.c \
	./common/easy_buffer_encoder.c \
	./common/easy_encoder.c \
	./common/easy_encoder_memusage.c \
	./common/filter_buffer_encoder.c \
	./common/filter_encoder.c \
	./common/filter_flags_encoder.c \
	./common/index_encoder.c \
	./common/stream_buffer_encoder.c \
	./common/stream_encoder.c \
	./common/stream_flags_encoder.c \
	./common/vli_encoder.c \
	./common/hardware_cputhreads.c \
	./common/outqueue.c \
	./common/stream_encoder_mt.c \
	./common/alone_decoder.c \
	./common/auto_decoder.c \
	./common/block_decoder.c \
	./common/easy_decoder_memusage.c \
	./common/filter_buffer_decoder.c \
	./common/filter_decoder.c \
	./common/filter_flags_decoder.c \
	./common/index_decoder.c \
	./common/index_hash.c \
	./common/vli_decoder.c \
	\
	./check/check.c \
	./check/crc32_table.c \
	./check/crc32_fast.c \
	./check/crc64_table.c \
	./check/crc64_fast.c \
	./check/sha256.c \
	\
	./lz/lz_encoder.c \
	./lz/lz_encoder_mf.c \
	./lz/lz_decoder.c \
	\
	./lzma/lzma_encoder.c \
	./lzma/lzma_encoder_presets.c \
	./lzma/lzma_encoder_optimum_fast.c \
	./lzma/lzma_encoder_optimum_normal.c \
	./lzma/fastpos_table.c \
	./lzma/lzma_decoder.c \
	./lzma/lzma2_encoder.c \
	./lzma/lzma2_decoder.c \
	\
	./rangecoder/price_table.c \
	\
	./delta/delta_common.c \
	./delta/delta_encoder.c \
	./delta/delta_decoder.c \
	\
	./simple/simple_coder.c \
	./simple/simple_encoder.c \
	./simple/simple_decoder.c \
	./simple/x86.c \
	./simple/powerpc.c \
	./simple/ia64.c \
	./simple/arm.c \
	./simple/armthumb.c \
	./simple/sparc.c

OBJ := lzma-ff.o $(SRC:.c=.o)

%.o: $(FF3PT)/lzma/%.c
	$(C) $(CFLAGS) -I$(FF3PT)/lzma $<  -o$@

%.o: %.c $(wildcard ./check/*.h) $(wildcard ./common/*.h) $(wildcard ./delta/*.h) $(wildcard ./lz/*.h) $(wildcard ./lzma/*.h) $(wildcard ./rangecoder/*.h) $(wildcard ./simple/*.h)
	$(C) $(CFLAGS) $<  -o$@

liblzma-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -shared -o$@

clean:
	rm -fv $(OBJ) liblzma-ff.$(SO)
