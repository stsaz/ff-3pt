# libMAC for FF
# Simon Zolin, 2016

OPT := SECTIONS
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += -O3 \
	-IShared -IMACLib -I$(FF3PT)/mac -I$(FF3PT)/../ffos

ifeq ($(OS),win)
CFLAGS += -DPLATFORM_WINDOWS -DWINVER=0x0400
LDFLAGS += -static
else
CFLAGS += -DPLATFORM_LINUX
LDFLAGS += -static-libgcc
endif

SRC := \
	MACLib/APEDecompress.cpp \
	MACLib/NewPredictor.cpp \
	MACLib/NNFilter.cpp \
	MACLib/Prepare.cpp \
	MACLib/UnBitArrayBase.cpp \
	MACLib/UnBitArray.cpp \
	Shared/GlobalFunctions.cpp
OBJ := MAC-ff.o $(SRC:.cpp=.o)

all: libMAC-ff.$(SO)

%.o: $(FF3PT)/mac/%.cpp $(wildcard MACLib/*.h)
	$(CXX)  $(CFLAGS) $<  -o$@

%.o: %.cpp $(wildcard MACLib/*.h)
	$(CXX)  $(CFLAGS) $<  -o$@

MACLib/NNFilter.o: MACLib/NNFilter.cpp $(wildcard MACLib/*.h)
	$(CXX)  $(CFLAGS) -msse2 $<  -o$@

libMAC-ff.$(SO): $(OBJ)
	$(LDXX) $(OBJ) $(LDFLAGS) -shared -o$@


MAC_SRC := \
	MACLib/APEDecompress.cpp \
	MACLib/NewPredictor.cpp \
	MACLib/NNFilter.cpp \
	MACLib/Prepare.cpp \
	MACLib/UnBitArrayBase.cpp \
	MACLib/UnBitArray.cpp \
	Shared/GlobalFunctions.cpp \
	\
	MACLib/MACLib.cpp \
	MACLib/md5.cpp \
	MACLib/APEHeader.cpp \
	MACLib/APEInfo.cpp \
	MACLib/APECompressCore.cpp \
	MACLib/APECompress.cpp \
	MACLib/APECompressCreate.cpp \
	MACLib/APESimple.cpp \
	MACLib/WAVInputSource.cpp \
	MACLib/MACProgressHelper.cpp \
	MACLib/APELink.cpp \
	MACLib/BitArray.cpp \
	MACLib/APETag.cpp \
	Shared/CircleBuffer.cpp \
	Shared/StdLibFileIO.cpp \
	Shared/CharacterHelper.cpp \
	Console/Console.cpp
MAC_O := $(MAC_SRC:.cpp=.o)

mac: $(MAC_O)
	$(LDXX) $(MAC_O) $(LDFLAGS) -o$@


clean:
	rm -fv $(OBJ) $(MAC_O) libMAC-ff.$(SO)
