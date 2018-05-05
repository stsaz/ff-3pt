# libALAC for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += -Icodec -Wall

ifeq ($(OS),win)
LDFLAGS += -static
else
LDFLAGS += -static-libstdc++
endif


SRC_CPP := \
	codec/ALACDecoder.cpp \
	codec/ALACEncoder.cpp
SRC := \
	codec/EndianPortable.c \
	codec/ALACBitUtilities.c \
	codec/ag_dec.c \
	codec/ag_enc.c \
	codec/dp_dec.c \
	codec/dp_enc.c \
	codec/matrix_dec.c \
	codec/matrix_enc.c
OBJ := ALAC-ff.o $(SRC_CPP:.cpp=.o) $(SRC:.c=.o)

%.o: $(FF3PT)/alac/%.cpp
	$(CXX) $(CFLAGS) -I$(FF3PT)/alac $< -o$@

%.o: %.c $(wildcard codec/*.h)
	$(C) $(CFLAGS) $< -o$@

%.o: %.cpp $(wildcard codec/*.h)
	$(CXX) $(CFLAGS) $< -o$@

all:
	cat $(FF3PT)/alac/*.patch | patch -p1
	$(MAKE) -f $(firstword $(MAKEFILE_LIST)) libALAC-ff.$(SO)

libALAC-ff.$(SO): $(OBJ)
	$(LDXX) $(OBJ) $(LDFLAGS) $(LD_INSTNAME_LDRPATH) -shared -o$@

clean:
	rm -fv $(OBJ) libALAC-ff.$(SO)
