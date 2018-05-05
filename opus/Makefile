# libopus for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-DHAVE_CONFIG_H -DOPUS_EXPORT= \
	-I. -Iinclude -Icelt -Isilk -Isilk/float \
	-W -Wall -Wextra -Wcast-align -Wnested-externs -Wshadow -Wstrict-prototypes
LDFLAGS += -lm
CFLAGS_SSE += -msse -msse2 -msse4.1

include ./celt_sources.mk
include ./silk_sources.mk
include ./opus_sources.mk

CELT_SOURCES += $(CELT_SOURCES_SSE) $(CELT_SOURCES_SSE2) $(CELT_SOURCES_SSE4_1)
SILK_SOURCES += $(SILK_SOURCES_SSE4_1) $(SILK_SOURCES_FLOAT)
OPUS_SOURCES += $(OPUS_SOURCES_FLOAT)

SRC := $(CELT_SOURCES) $(SILK_SOURCES) $(OPUS_SOURCES)
OBJ := opus-ff.o $(SRC:.c=.o)

%.o: $(FF3PT)/opus/%.c
	$(C) $(CFLAGS) -I$(FF3PT)/opus $< -o$@

silk/x86/%.o: silk/x86/%.c
	$(C) $(CFLAGS) $(CFLAGS_SSE) $< -o$@

celt/x86/%.o: celt/x86/%.c
	$(C) $(CFLAGS) $(CFLAGS_SSE) $< -o$@

%.o: %.c
	$(C) $(CFLAGS) $< -o$@

all:
	./configure
	$(MAKE) -f $(firstword $(MAKEFILE_LIST)) libopus-ff.$(SO)

clean:
	rm -fv $(OBJ) libopus-ff.$(SO)

libopus-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) $(LD_INSTNAME_LDRPATH) -shared -o$@
