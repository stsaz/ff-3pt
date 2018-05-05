# libfdk-aac for FF
# Simon Zolin, 2016

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += -fno-exceptions -fno-rtti \
	-IlibAACdec/include -IlibMpegTPDec/include -IlibSBRdec/include \
	-IlibAACenc/include -IlibMpegTPEnc/include -IlibSBRenc/include \
	-IlibSYS/include -IlibFDK/include -IlibPCMutils/include

CFLAGS += -Wno-narrowing
# libAACenc/src/aacEnc_rom.cpp:661:1: error: narrowing conversion of ‘2180108801u’ from ‘unsigned int’ to ‘FIXP_DBL {aka long int}’ inside { } [-Wnarrowing]

ifeq ($(OS),win)
LDFLAGS += -static
else
LDFLAGS += -static-libstdc++
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

AACENC_SRC := \
	libAACenc/src/aacenc.cpp \
	libAACenc/src/aacenc_hcr.cpp \
	libAACenc/src/aacenc_lib.cpp \
	libAACenc/src/aacenc_pns.cpp \
	libAACenc/src/aacEnc_ram.cpp \
	libAACenc/src/aacEnc_rom.cpp \
	libAACenc/src/aacenc_tns.cpp \
	libAACenc/src/adj_thr.cpp \
	libAACenc/src/band_nrg.cpp \
	libAACenc/src/bandwidth.cpp \
	libAACenc/src/bit_cnt.cpp \
	libAACenc/src/bitenc.cpp \
	libAACenc/src/block_switch.cpp \
	libAACenc/src/channel_map.cpp \
	libAACenc/src/chaosmeasure.cpp \
	libAACenc/src/dyn_bits.cpp \
	libAACenc/src/grp_data.cpp \
	libAACenc/src/intensity.cpp \
	libAACenc/src/line_pe.cpp \
	libAACenc/src/metadata_compressor.cpp \
	libAACenc/src/metadata_main.cpp \
	libAACenc/src/ms_stereo.cpp \
	libAACenc/src/noisedet.cpp \
	libAACenc/src/pnsparam.cpp \
	libAACenc/src/pre_echo_control.cpp \
	libAACenc/src/psy_configuration.cpp \
	libAACenc/src/psy_main.cpp \
	libAACenc/src/qc_main.cpp \
	libAACenc/src/quantize.cpp \
	libAACenc/src/sf_estim.cpp \
	libAACenc/src/spreading.cpp \
	libAACenc/src/tonality.cpp \
	libAACenc/src/transform.cpp

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

MPEGTPENC_SRC := \
	libMpegTPEnc/src/tpenc_adif.cpp \
	libMpegTPEnc/src/tpenc_adts.cpp \
	libMpegTPEnc/src/tpenc_asc.cpp \
	libMpegTPEnc/src/tpenc_latm.cpp \
	libMpegTPEnc/src/tpenc_lib.cpp

SBRENC_SRC := \
	libSBRenc/src/bit_sbr.cpp \
	libSBRenc/src/code_env.cpp \
	libSBRenc/src/env_bit.cpp \
	libSBRenc/src/env_est.cpp \
	libSBRenc/src/fram_gen.cpp \
	libSBRenc/src/invf_est.cpp \
	libSBRenc/src/mh_det.cpp \
	libSBRenc/src/nf_est.cpp \
	libSBRenc/src/ps_bitenc.cpp \
	libSBRenc/src/ps_encode.cpp \
	libSBRenc/src/ps_main.cpp \
	libSBRenc/src/resampler.cpp \
	libSBRenc/src/sbrenc_freq_sca.cpp \
	libSBRenc/src/sbr_encoder.cpp \
	libSBRenc/src/sbr_misc.cpp \
	libSBRenc/src/sbr_ram.cpp \
	libSBRenc/src/sbr_rom.cpp \
	libSBRenc/src/ton_corr.cpp \
	libSBRenc/src/tran_det.cpp

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

SRC := $(AACDEC_SRC) $(MPEGTPDEC_SRC) $(SBRDEC_SRC) \
	$(AACENC_SRC) $(MPEGTPENC_SRC) $(SBRENC_SRC) \
	$(FDK_SRC) $(PCMUTILS_SRC) $(SYS_SRC)
OBJ := fdk-aac-ff.o
OBJ += $(SRC:.cpp=.o)

%.o: $(FF3PT)/fdk-aac/%.c $(FF3PT)/fdk-aac/%.h
	$(C) $(CFLAGS) -I$(FF3PT)/fdk-aac $< -o$@

%.o: ./%.cpp $(wildcard libAACdec/include/*.h) $(wildcard libAACenc/include/*.h)
	$(CXX) $(CFLAGS) $< -o$@

libfdk-aac-ff.$(SO): $(OBJ)
	$(LDXX) $(OBJ) $(LDFLAGS) $(LD_INSTNAME_LDRPATH) -shared -o$@

clean:
	rm -fv $(OBJ) libfdk-aac-ff.$(SO)
