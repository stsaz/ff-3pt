# libfdk-aac for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += -fno-exceptions -fno-rtti \
	-IlibAACdec/include -IlibMpegTPDec/include -IlibSYS/include -IlibFDK/include -IlibSBRdec/include -IlibPCMutils/include

ifeq ($(OS),win)
LDFLAGS += -static
else
LDFLAGS += -static-libgcc
endif

AACDEC_SRC := \
	libAACdec/src/aacdec_drc.cpp \
	libAACdec/src/aacdec_hcr.cpp \
	libAACdec/src/aacdecoder.cpp \
	libAACdec/src/aacdec_pns.cpp \
	libAACdec/src/aac_ram.cpp \
	libAACdec/src/block.cpp \
	libAACdec/src/channelinfo.cpp \
	libAACdec/src/ldfiltbank.cpp \
	libAACdec/src/rvlcbit.cpp \
	libAACdec/src/rvlc.cpp \
	libAACdec/src/aacdec_hcr_bit.cpp \
	libAACdec/src/aacdec_hcrs.cpp \
	libAACdec/src/aacdecoder_lib.cpp \
	libAACdec/src/aacdec_tns.cpp \
	libAACdec/src/aac_rom.cpp \
	libAACdec/src/channel.cpp \
	libAACdec/src/conceal.cpp \
	libAACdec/src/pulsedata.cpp \
	libAACdec/src/rvlcconceal.cpp \
	libAACdec/src/stereo.cpp

FDK_SRC := \
	libFDK/src/autocorr2nd.cpp \
	libFDK/src/dct.cpp \
	libFDK/src/FDK_bitbuffer.cpp \
	libFDK/src/FDK_core.cpp \
	libFDK/src/FDK_crc.cpp \
	libFDK/src/FDK_hybrid.cpp \
	libFDK/src/FDK_tools_rom.cpp \
	libFDK/src/FDK_trigFcts.cpp \
	libFDK/src/fft.cpp \
	libFDK/src/fft_rad2.cpp \
	libFDK/src/fixpoint_math.cpp \
	libFDK/src/mdct.cpp \
	libFDK/src/qmf.cpp \
	libFDK/src/scale.cpp

MPEGTPDEC_SRC := \
	libMpegTPDec/src/tpdec_adif.cpp \
	libMpegTPDec/src/tpdec_adts.cpp \
	libMpegTPDec/src/tpdec_asc.cpp \
	libMpegTPDec/src/tpdec_latm.cpp \
	libMpegTPDec/src/tpdec_lib.cpp

SBRDEC_SRC := \
	libSBRdec/src/env_calc.cpp \
	libSBRdec/src/env_dec.cpp \
	libSBRdec/src/env_extr.cpp \
	libSBRdec/src/huff_dec.cpp \
	libSBRdec/src/lpp_tran.cpp \
	libSBRdec/src/psbitdec.cpp \
	libSBRdec/src/psdec.cpp \
	libSBRdec/src/psdec_hybrid.cpp \
	libSBRdec/src/sbr_crc.cpp \
	libSBRdec/src/sbr_deb.cpp \
	libSBRdec/src/sbr_dec.cpp \
	libSBRdec/src/sbrdec_drc.cpp \
	libSBRdec/src/sbrdec_freq_sca.cpp \
	libSBRdec/src/sbrdecoder.cpp \
	libSBRdec/src/sbr_ram.cpp \
	libSBRdec/src/sbr_rom.cpp

PCMUTILS_SRC := \
	libPCMutils/src/limiter.cpp \
	libPCMutils/src/pcmutils_lib.cpp

SYS_SRC := \
	libSYS/src/genericStds.cpp

SRC := $(AACDEC_SRC) $(FDK_SRC) $(MPEGTPDEC_SRC) $(SBRDEC_SRC) $(PCMUTILS_SRC) $(SYS_SRC)
OBJ := fdk-aac-ff.o
OBJ += $(SRC:.cpp=.o)

%.o: $(FF3PT)/fdk-aac/%.c
	$(C) $(CFLAGS) -I$(FF3PT)/fdk-aac $< -o$@

%.o: ./%.cpp $(wildcard ./libAACdec/include/*.h)
	$(CXX) $(CFLAGS) $< -o$@

libfdk-aac-ff.$(SO): $(OBJ)
	$(LDXX) $(OBJ) $(LDFLAGS) -shared -o$@

clean:
	rm -fv $(OBJ) libfdk-aac-ff.$(SO)
