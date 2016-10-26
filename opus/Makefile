# libopus for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-DHAVE_CONFIG_H -DOPUS_EXPORT= \
	-I. -Iinclude -Icelt -Isilk -Isilk/float -I$(FF3PT)/opus \
	-W -Wall -Wextra -Wcast-align -Wnested-externs -Wshadow -Wstrict-prototypes
LDFLAGS += -L$(FF3PT)/$(OS)-$(ARCH) -lm
CFLAGS_SSE41 := -msse4.1

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
	$(C) $(CFLAGS) $(CFLAGS_SSE41) $< -o$@

celt/x86/%.o: celt/x86/%.c
	$(C) $(CFLAGS) $(CFLAGS_SSE41) $< -o$@

%.o: %.c
	$(C) $(CFLAGS) $< -o$@

all: libopus-ff.$(SO)

clean:
	rm -fv $(OBJ) libopus-ff.$(SO)

libopus-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -shared -o$@
