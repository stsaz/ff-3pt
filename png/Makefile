# libpng for FF
# Simon Zolin, 2016

OPT := LTO
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-I. -I$(FF3PT)/png -I$(FF3PT)/zlib \
	-DHAVE_CONFIG_H

LDFLAGS += -lm

SRC := png.o \
	pngerror.o \
	pngget.o \
	pngmem.o \
	pngpread.o \
	pngread.o \
	pngrio.o \
	pngrtran.o \
	pngrutil.o \
	pngset.o \
	pngtrans.o \
	pngwio.o \
	pngwrite.o \
	pngwtran.o \
	pngwutil.o

OBJ := png-ff.o $(SRC:.c=.o)

%.o: $(FF3PT)/png/%.c
	$(C) $(CFLAGS) $< -o$@

%.o: %.c $(wildcard ./*.h)
	$(C) $(CFLAGS) $<  -o$@

libpng-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) $(LD_INSTNAME_LDRPATH) $(FF3PT)-bin/$(OS)-$(ARCH)/libz.a -shared -o$@

clean:
	rm -fv $(OBJ) libpng-ff.$(SO)
