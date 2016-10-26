# libsoxr for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-I. -Isrc -I$(FF3PT)/soxr \
	-DNDEBUG -DSOXR_LIB -D_DEFAULT_SOURCE \
	-Wconversion -Wall -W -pedantic -Wundef -Wcast-align -Wpointer-arith -Wno-long-long -Wnested-externs -Wmissing-prototypes -Wstrict-prototypes

ifeq ($(OS),win)
CFLAGS += -DSOXR_DLL -Dsoxr_EXPORTS -D_USE_MATH_DEFINES
else
CFLAGS += -DSOXR_VISIBILITY
endif

SRC := \
	src/soxr.c \
	src/data-io.c \
	src/dbesi0.c \
	src/filter.c \
	src/fft4g64.c \
	src/rate32.c \
	src/fft4g32.c \
	src/vr32.c \
	src/rate64.c \
	src/rate32s.c \
	src/pffft32s.c \
	src/simd.c
OBJ := $(SRC:.c=.o)

%.o: %.c $(wildcard ./src/*.h)
	$(C) $(CFLAGS) $<  -o$@

libsoxr-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -lm -shared -o$@

clean:
	rm -fv $(OBJ) libsoxr-ff.$(SO)
