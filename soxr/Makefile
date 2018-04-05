# libsoxr for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-I. -Isrc \
	-DNDEBUG -DSOXR_LIB -D_DEFAULT_SOURCE \
	-Wconversion -Wall -W -pedantic -Wundef -Wcast-align -Wpointer-arith -Wno-long-long -Wnested-externs -Wmissing-prototypes -Wstrict-prototypes

ifeq ($(OS),win)
CFLAGS += -DSOXR_DLL -Dsoxr_EXPORTS -D_USE_MATH_DEFINES
else
CFLAGS += -DSOXR_VISIBILITY
endif

SRC := \
	src/cr.c \
	src/cr32.c \
	src/cr32s.c \
	src/cr64.c \
	src/cr64s.c \
	src/data-io.c \
	src/dbesi0.c \
	src/fft4g32.c \
	src/fft4g64.c \
	src/filter.c \
	src/pffft32s.c \
	src/pffft64s.c \
	src/soxr.c \
	src/util32s.c \
	src/util64s.c \
	src/vr32.c
OBJ := $(SRC:.c=.o)

all:
	cmake -Wno-dev -DCMAKE_BUILD_TYPE="Release" .
	$(MAKE) -f $(firstword $(MAKEFILE_LIST)) libsoxr-ff.$(SO)

%.o: %.c $(wildcard ./src/*.h)
	$(C) $(CFLAGS) $<  -o$@

src/cr64s.o: src/cr64s.c $(wildcard ./src/*.h)
	$(C) $(CFLAGS) -mavx $<  -o$@
src/pffft64s.o: src/pffft64s.c $(wildcard ./src/*.h)
	$(C) $(CFLAGS) -mavx $<  -o$@
src/util64s.o: src/util64s.c $(wildcard ./src/*.h)
	$(C) $(CFLAGS) -mavx $<  -o$@

libsoxr-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -lm -shared -o$@

clean:
	rm -fv $(OBJ) libsoxr-ff.$(SO)
