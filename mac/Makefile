# libMAC for FF
# Simon Zolin, 2016

OPT := 3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-ISource/Shared -ISource/MACLib -I$(FF3PT)/mac -I$(FF3PT)/../ffos

ifeq ($(OS),win)
CFLAGS += -DPLATFORM_WINDOWS -DWINVER=0x0501
LDFLAGS += -static
else
CFLAGS += -DPLATFORM_LINUX
LDFLAGS += -static-libstdc++
endif

SRC := \
	Source/MACLib/APEDecompress.cpp \
	Source/MACLib/NewPredictor.cpp \
	Source/MACLib/NNFilter.cpp \
	Source/MACLib/Prepare.cpp \
	Source/MACLib/UnBitArrayBase.cpp \
	Source/MACLib/UnBitArray.cpp \
	Source/Shared/GlobalFunctions.cpp
OBJ := MAC-ff.o $(SRC:.cpp=.o)

all:
	find . -name '*.cpp' -print0 | xargs -0 dos2unix
	find . -name '*.h' -print0 | xargs -0 dos2unix
	cat $(FF3PT)/mac/*.patch | patch -p1
	$(MAKE) -f $(firstword $(MAKEFILE_LIST)) libMAC-ff.$(SO)

%.o: $(FF3PT)/mac/%.cpp $(wildcard Source/MACLib/*.h)
	$(CXX)  $(CFLAGS) $<  -o$@

%.o: %.cpp $(wildcard Source/MACLib/*.h)
	$(CXX)  $(CFLAGS) $<  -o$@

Source/MACLib/NNFilter.o: Source/MACLib/NNFilter.cpp $(wildcard Source/MACLib/*.h)
	$(CXX)  $(CFLAGS) -msse2 $<  -o$@

libMAC-ff.$(SO): $(OBJ)
	$(LDXX) $(OBJ) $(LDFLAGS) -shared -o$@


MAC_SRC := \
	Source/MACLib/APEDecompress.cpp \
	Source/MACLib/NewPredictor.cpp \
	Source/MACLib/NNFilter.cpp \
	Source/MACLib/Prepare.cpp \
	Source/MACLib/UnBitArrayBase.cpp \
	Source/MACLib/UnBitArray.cpp \
	Source/Shared/GlobalFunctions.cpp \
	\
	Source/MACLib/MACLib.cpp \
	Source/MACLib/md5.cpp \
	Source/MACLib/APEHeader.cpp \
	Source/MACLib/APEInfo.cpp \
	Source/MACLib/APECompressCore.cpp \
	Source/MACLib/APECompress.cpp \
	Source/MACLib/APECompressCreate.cpp \
	Source/MACLib/APESimple.cpp \
	Source/MACLib/WAVInputSource.cpp \
	Source/MACLib/MACProgressHelper.cpp \
	Source/MACLib/APELink.cpp \
	Source/MACLib/BitArray.cpp \
	Source/MACLib/APETag.cpp \
	Source/Shared/CircleBuffer.cpp \
	Source/Shared/StdLibFileIO.cpp \
	Source/Shared/CharacterHelper.cpp \
	Source/Console/Console.cpp
MAC_O := $(MAC_SRC:.cpp=.o)

mac: $(MAC_O)
	$(LDXX) $(MAC_O) $(LDFLAGS) -o$@


clean:
	rm -fv $(OBJ) $(MAC_O) libMAC-ff.$(SO)
