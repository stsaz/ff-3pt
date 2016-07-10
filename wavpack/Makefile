# libwavpack for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-I$(FF3PT)/wavpack \
	-DWVPK_EXP -DOPT_ASM_X64=1 -DHAVE___BUILTIN_CLZ=1 -DHAVE___BUILTIN_CTZ=1 -I. -DVER4_ONLY -DNO_SEEKING -DNO_TAGS -DNO_USE_FSTREAMS

SRC := \
	src/common_utils.c \
	src/decorr_utils.c \
	src/entropy_utils.c \
	src/open_utils.c \
	src/read_words.c \
	src/unpack.c \
	src/unpack_floats.c \
	src/unpack_utils.c
SRC_AS := src/unpack_x64.s
OBJ := $(SRC:.c=.o)
OBJ += $(SRC_AS:.s=.o)

%.o: %.c $(wildcard src/*.h)
	$(C) $(CFLAGS) $<  -o$@

%.o: %.s $(wildcard src/*.h)
	$(C) $(CFLAGS) $<  -o$@

libwavpack-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -shared -o$@

clean:
	rm -fv $(OBJ) libwavpack-ff.$(SO)
