# libz for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-I. \
	-DZ_EXP -DNO_GZIP -D_LARGEFILE64_SOURCE=1

ifneq ($(OS),win)
CFLAGS += -DHAVE_HIDDEN
# CFLAGS += -O3 -fvisibility=default
endif

SRC := adler32.c \
	deflate.c \
	infback.c \
	inffast.c \
	inflate.c \
	inftrees.c \
	trees.c \
	zutil.c
OBJ := zlib-ff.o $(SRC:.c=.o)

%.o: $(FF3PT)/zlib/%.c
	$(C) $(CFLAGS) -I$(FF3PT)/zlib $< -o$@

%.o: %.c $(wildcard ./*.h)
	$(C) $(CFLAGS) $<  -o$@

libz-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) $(LD_INSTNAME_LDRPATH) -shared -o$@

OBJ_A := $(SRC:.c=.o) crc32.o
libz.a: $(OBJ_A)
	$(AR) rcs $@ $(OBJ_A)

clean:
	rm -fv $(OBJ) crc32.o libz-ff.$(SO) libz.a
