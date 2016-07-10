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
	$(LD) $(OBJ) $(LDFLAGS) -shared -o$@

clean:
	rm -fv $(OBJ) libz-ff.$(SO)
