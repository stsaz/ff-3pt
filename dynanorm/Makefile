# libDynamicAudioNormalizer for FF
# Simon Zolin, 2018

OPT :=
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += -O3 -Wall -std=gnu++11 -ffast-math -mfpmath=sse -msse -fomit-frame-pointer -fno-tree-vectorize \
	-DNO_JAVA_SUPPORT -DNDEBUG \
	-I$(FF3PT)/dynanorm -I./DynamicAudioNormalizerAPI/src -I./DynamicAudioNormalizerAPI/include -I./DynamicAudioNormalizerShared/include

ifeq ($(OS),win)
LDFLAGS += -static
else
LDFLAGS += -static-libstdc++
endif


SRC_CPP := \
	DynamicAudioNormalizerAPI/src/DynamicAudioNormalizer.cpp \
	DynamicAudioNormalizerAPI/src/GaussianFilter.cpp \
	DynamicAudioNormalizerAPI/src/FrameBuffer.cpp \
	DynamicAudioNormalizerAPI/src/Version.cpp
OBJ := DynamicAudioNormalizer-ff.o $(SRC_CPP:.cpp=.o)

%.o: $(FF3PT)/dynanorm/%.cpp
	$(CXX) $(CFLAGS) $<  -o$@

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -o$@

libdynanorm-ff.$(SO): $(OBJ)
	$(LDXX) $(OBJ) $(LDFLAGS) -shared -o$@

clean:
	rm -fv $(OBJ) libdynanorm-ff.$(SO)
