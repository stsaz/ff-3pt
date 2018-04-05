# libmpg123 for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += -msse2 \
	-I. -Isrc -Isrc/libmpg123 -I$(FF3PT)/mpg123 -Isrc/compat \
	-DMPG123_SO -DMPG123_EXPORT="" -DHAVE_CONFIG_H -DNO_ID3V2 -DNO_ICY -DNO_WARNING -DNO_ERRORMSG -DNO_ERETURN \
	-DOPT_MULTI -DOPT_GENERIC -DOPT_GENERIC_DITHER -DREAL_IS_FLOAT -DMPG123_NO_LARGENAME \
	-fomit-frame-pointer -funroll-all-loops -finline-functions -ffast-math

SRC := \
	src/compat/compat_str.c \
	src/libmpg123/parse.c \
	src/libmpg123/index.c \
	src/libmpg123/frame.c \
	src/libmpg123/format.c \
	src/libmpg123/dct64.c \
	src/libmpg123/optimize.c \
	src/libmpg123/readers.c \
	src/libmpg123/tabinit.c \
	src/libmpg123/libmpg123.c \
	src/libmpg123/ntom.c \
	src/libmpg123/synth.c  \
	src/libmpg123/layer1.c \
	src/libmpg123/layer2.c \
	src/libmpg123/layer3.c \
	src/libmpg123/dither.c

ifeq ($(CPU),amd64)

CFLAGS += -DOPT_X86_64 -DOPT_AVX

SRC_AS := \
	src/libmpg123/getcpuflags_x86_64.S \
	src/libmpg123/dct36_x86_64.S \
	src/libmpg123/dct64_x86_64_float.S \
	src/libmpg123/dct64_x86_64.S \
	src/libmpg123/dct36_avx.S \
	src/libmpg123/dct64_avx_float.S \
	src/libmpg123/dct64_avx.S \
	src/libmpg123/synth_8bit.S \
	src/libmpg123/synth_s32.S \
	src/libmpg123/synth_real.S \
	src/libmpg123/synth_x86_64_float.S \
	src/libmpg123/synth_x86_64_s32.S \
	src/libmpg123/synth_stereo_x86_64_float.S \
	src/libmpg123/synth_stereo_x86_64_s32.S \
	src/libmpg123/synth_x86_64.S \
	src/libmpg123/synth_stereo_x86_64.S \
	src/libmpg123/synth_stereo_avx_float.S \
	src/libmpg123/synth_stereo_avx_s32.S \
	src/libmpg123/synth_stereo_avx.S

else

CFLAGS += \
	-DOPT_I386 -DOPT_I586 -DOPT_I586_DITHER -DOPT_MMX \
	-DOPT_3DNOW -DOPT_3DNOW_VINTAGE -DOPT_3DNOWEXT -DOPT_3DNOWEXT_VINTAGE \
	-DOPT_SSE -DOPT_SSE_VINTAGE -DNOXFERMEM -DNEWOLD_WRITE_SAMPLE

SRC += \
	src/libmpg123/synth_8bit.c \
	src/libmpg123/synth_s32.c \
	src/libmpg123/synth_real.c

SRC_AS := \
	src/libmpg123/dct64_i386.S \
	src/libmpg123/synth_i586.S \
	src/libmpg123/synth_i586_dither.S \
	src/libmpg123/dct64_mmx.S \
	src/libmpg123/tabinit_mmx.S \
	src/libmpg123/synth_mmx.S \
	src/libmpg123/synth_3dnow.S \
	src/libmpg123/dct64_3dnow.S \
	src/libmpg123/dct36_3dnow.S \
	src/libmpg123/dct64_3dnowext.S \
	src/libmpg123/synth_3dnowext.S \
	src/libmpg123/dct36_3dnowext.S \
	src/libmpg123/dct64_sse_float.S \
	src/libmpg123/synth_sse_float.S \
	src/libmpg123/synth_stereo_sse_float.S \
	src/libmpg123/synth_sse_s32.S \
	src/libmpg123/synth_stereo_sse_s32.S \
	src/libmpg123/dct36_sse.S \
	src/libmpg123/dct64_sse.S \
	src/libmpg123/synth_sse.S \
	src/libmpg123/getcpuflags.S
endif

OBJ := mpg123-ff.o $(SRC:.c=.o)
OBJ += $(SRC_AS:.S=.o)

ifeq ($(OS),win)
CONFIGURE_FLAGS := --host=x86_64-w64-mingw32
endif

all:
	./configure $(CONFIGURE_FLAGS)
	cat $(FF3PT)/mpg123/*.patch | patch -p1
	$(MAKE) -f $(firstword $(MAKEFILE_LIST)) libmpg123-ff.$(SO)

libmpg123-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -lm -shared -o$@

%.o: $(FF3PT)/mpg123/%.c
	$(C) $(CFLAGS) $< -o$@

%.o: %.c $(wildcard ./*.h)
	$(C) $(CFLAGS) $<  -o$@

%.o: %.S $(wildcard ./*.h)
	$(C) $(CFLAGS) $<  -o$@

clean:
	rm -fv $(OBJ) libmpg123-ff.$(SO)
