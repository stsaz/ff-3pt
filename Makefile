# Download and build libraries

include ./makeconf

FF3PT := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
DL := curl -L
COPY := cp -v
TAR_XZ := tar cJf
UNTAR_XZ := tar xJf
UNTAR_GZ := tar xzf
UNTAR_BZ2 := tar xjf
UNZIP := unzip
MAKE := make -j8 -rR FF3PT=$(FF3PT)
SRCDIR := $(FF3PT)/_src
BUILDDIR := /tmp/ff3pt-build
BINDIR := $(FF3PT)/_bin/$(OS)-$(ARCH)
ALIBS := alac dynanorm fdk-aac flac lame mac mpg123 musepack ogg opus soxr vorbis wavpack
PLIBS := jpeg-turbo png
ENCLIBS := aes


help:
	mkdir -p $(SRCDIR) $(BUILDDIR) $(BINDIR)
	@echo Specify the library to build: $(ALIBS) $(PLIBS) $(ENCLIBS)

.PHONY: $(ALIBS) $(PLIBS) $(ENCLIBS)

package:
	$(TAR_XZ) _bin/$(OS)-$(ARCH)-$(VER).tar.xz -C _bin $(OS)-$(ARCH)

# AUDIO

$(SRCDIR)/alac-master.zip:
	cd $(SRCDIR) && $(DL) -o alac-master.zip https://github.com/macosforge/alac/archive/master.zip
$(BUILDDIR)/alac-master: $(SRCDIR)/alac-master.zip
	$(UNZIP) $(SRCDIR)/alac-master.zip -d $(BUILDDIR)
alac: $(BUILDDIR)/alac-master
	$(MAKE) -f $(FF3PT)/alac/Makefile -C $(BUILDDIR)/alac-master
	$(COPY) $(BUILDDIR)/alac-master/*.$(SO) $(BINDIR)

DYNANORM_VER := 2.10
$(SRCDIR)/DynamicAudioNormalizer-$(DYNANORM_VER).tar.gz:
	cd $(SRCDIR) && $(DL) -o DynamicAudioNormalizer-$(DYNANORM_VER).tar.gz https://github.com/lordmulder/DynamicAudioNormalizer/archive/$(DYNANORM_VER).tar.gz
$(BUILDDIR)/DynamicAudioNormalizer-$(DYNANORM_VER): $(SRCDIR)/DynamicAudioNormalizer-$(DYNANORM_VER).tar.gz
	$(UNTAR_GZ) $(SRCDIR)/DynamicAudioNormalizer-$(DYNANORM_VER).tar.gz -C $(BUILDDIR)
dynanorm: $(BUILDDIR)/DynamicAudioNormalizer-$(DYNANORM_VER)
	$(MAKE) -f $(FF3PT)/dynanorm/Makefile -C $(BUILDDIR)/DynamicAudioNormalizer-$(DYNANORM_VER)
	$(COPY) $(BUILDDIR)/DynamicAudioNormalizer-$(DYNANORM_VER)/*.$(SO) $(BINDIR)

FDK_VER := 0.1.6
$(SRCDIR)/fdk-aac-v$(FDK_VER).tar.gz:
	cd $(SRCDIR) && $(DL) -o fdk-aac-v$(FDK_VER).tar.gz https://github.com/mstorsjo/fdk-aac/archive/v$(FDK_VER).tar.gz
$(BUILDDIR)/fdk-aac-$(FDK_VER): $(SRCDIR)/fdk-aac-v$(FDK_VER).tar.gz
	$(UNTAR_GZ) $(SRCDIR)/fdk-aac-v$(FDK_VER).tar.gz -C $(BUILDDIR)
fdk-aac: $(BUILDDIR)/fdk-aac-$(FDK_VER)
	$(MAKE) -f $(FF3PT)/fdk-aac/Makefile -C $(BUILDDIR)/fdk-aac-$(FDK_VER)
	$(COPY) $(BUILDDIR)/fdk-aac-$(FDK_VER)/*.$(SO) $(BINDIR)

FLAC_VER := 1.3.2
$(SRCDIR)/flac-$(FLAC_VER).tar.xz:
	cd $(SRCDIR) && $(DL) -O http://downloads.xiph.org/releases/flac/flac-$(FLAC_VER).tar.xz
$(BUILDDIR)/flac-$(FLAC_VER): $(SRCDIR)/flac-$(FLAC_VER).tar.xz
	$(UNTAR_XZ) $(SRCDIR)/flac-$(FLAC_VER).tar.xz -C $(BUILDDIR)
flac: $(BUILDDIR)/flac-$(FLAC_VER)
	$(MAKE) -f $(FF3PT)/flac/Makefile -C $(BUILDDIR)/flac-$(FLAC_VER)
	$(COPY) $(BUILDDIR)/flac-$(FLAC_VER)/*.$(SO) $(BINDIR)

LAME_VER := 3.100
$(SRCDIR)/lame-$(LAME_VER).tar.gz:
	@echo Please download lame-$(LAME_VER).tar.gz from https://sourceforge.net/projects/lame/files/lame/ and put it into $(SRCDIR) directory
	@exit 1
$(BUILDDIR)/lame-$(LAME_VER): $(SRCDIR)/lame-$(LAME_VER).tar.gz
	$(UNTAR_GZ) $(SRCDIR)/lame-$(LAME_VER).tar.gz -C $(BUILDDIR)
lame: $(BUILDDIR)/lame-$(LAME_VER)
	$(MAKE) -f $(FF3PT)/mp3lame/Makefile -C $(BUILDDIR)/lame-$(LAME_VER)
	$(COPY) $(BUILDDIR)/lame-$(LAME_VER)/*.$(SO) $(BINDIR)

MAC_VER := 433
$(SRCDIR)/MAC_SDK_$(MAC_VER).zip:
	# cd $(SRCDIR) && $(DL) -O http://monkeysaudio.com/files/MAC_SDK_$(MAC_VER).zip
	cd $(SRCDIR) && $(DL) -O https://github.com/stsaz/ff-3pt/files/3720271/MAC_SDK_433.zip
$(BUILDDIR)/mac: $(SRCDIR)/MAC_SDK_$(MAC_VER).zip
	$(UNZIP) $(SRCDIR)/MAC_SDK_$(MAC_VER).zip -d $(BUILDDIR)/mac
mac: $(BUILDDIR)/mac
	$(MAKE) -f $(FF3PT)/mac/Makefile -C $(BUILDDIR)/mac
	$(COPY) $(BUILDDIR)/mac/*.$(SO) $(BINDIR)

MPG123_VER := 1.25.10
$(SRCDIR)/mpg123-$(MPG123_VER).tar.bz2:
	cd $(SRCDIR) && $(DL) -O http://mpg123.de/download/mpg123-$(MPG123_VER).tar.bz2
$(BUILDDIR)/mpg123-$(MPG123_VER): $(SRCDIR)/mpg123-$(MPG123_VER).tar.bz2
	$(UNTAR_BZ2) $(SRCDIR)/mpg123-$(MPG123_VER).tar.bz2 -C $(BUILDDIR)
mpg123: $(BUILDDIR)/mpg123-$(MPG123_VER)
	$(MAKE) -f $(FF3PT)/mpg123/Makefile -C $(BUILDDIR)/mpg123-$(MPG123_VER)
	$(COPY) $(BUILDDIR)/mpg123-$(MPG123_VER)/*.$(SO) $(BINDIR)

MUSEPACK_VER := r475
$(SRCDIR)/musepack_src_$(MUSEPACK_VER).tar.gz:
	cd $(SRCDIR) && $(DL) -O https://files.musepack.net/source/musepack_src_$(MUSEPACK_VER).tar.gz
$(BUILDDIR)/musepack_src_$(MUSEPACK_VER): $(SRCDIR)/musepack_src_$(MUSEPACK_VER).tar.gz
	$(UNTAR_GZ) $(SRCDIR)/musepack_src_$(MUSEPACK_VER).tar.gz -C $(BUILDDIR)
musepack: $(BUILDDIR)/musepack_src_$(MUSEPACK_VER)
	$(MAKE) -f $(FF3PT)/musepack/Makefile -C $(BUILDDIR)/musepack_src_$(MUSEPACK_VER)
	$(COPY) $(BUILDDIR)/musepack_src_$(MUSEPACK_VER)/*.$(SO) $(BINDIR)

OGG_VER := 1.3.3
$(SRCDIR)/libogg-$(OGG_VER).tar.xz:
	cd $(SRCDIR) && $(DL) -O http://downloads.xiph.org/releases/ogg/libogg-$(OGG_VER).tar.xz
$(BUILDDIR)/libogg-$(OGG_VER): $(SRCDIR)/libogg-$(OGG_VER).tar.xz
	$(UNTAR_XZ) $(SRCDIR)/libogg-$(OGG_VER).tar.xz -C $(BUILDDIR)
ogg: $(BUILDDIR)/libogg-$(OGG_VER)
	$(MAKE) -f $(FF3PT)/ogg/Makefile -C $(BUILDDIR)/libogg-$(OGG_VER)
	$(COPY) $(BUILDDIR)/libogg-$(OGG_VER)/*.$(SO) $(BINDIR)

OPUS_VER := 1.3.1
OPUS_URL := https://archive.mozilla.org/pub/opus/opus-$(OPUS_VER).tar.gz
$(SRCDIR)/opus-$(OPUS_VER).tar.gz:
	cd $(SRCDIR) && $(DL) -O $(OPUS_URL)
$(BUILDDIR)/opus-$(OPUS_VER): $(SRCDIR)/opus-$(OPUS_VER).tar.gz
	$(UNTAR_GZ) $< -C $(BUILDDIR)
opus: $(BUILDDIR)/opus-$(OPUS_VER)
	$(MAKE) -f $(FF3PT)/opus/Makefile -C $<
	$(COPY) $</*.$(SO) $(BINDIR)

SOXR_VER := 0.1.3
$(SRCDIR)/soxr-$(SOXR_VER)-Source.tar.xz:
	@echo Please download soxr-$(SOXR_VER)-Source.tar.xz from https://sourceforge.net/projects/soxr/files/ and put it into $(SRCDIR) directory
	@exit 1
$(BUILDDIR)/soxr-$(SOXR_VER)-Source: $(SRCDIR)/soxr-$(SOXR_VER)-Source.tar.xz
	$(UNTAR_XZ) $(SRCDIR)/soxr-$(SOXR_VER)-Source.tar.xz -C $(BUILDDIR)
soxr: $(BUILDDIR)/soxr-$(SOXR_VER)-Source
	$(MAKE) -f $(FF3PT)/soxr/Makefile -C $(BUILDDIR)/soxr-$(SOXR_VER)-Source
	$(COPY) $(BUILDDIR)/soxr-$(SOXR_VER)-Source/*.$(SO) $(BINDIR)

VORBIS_VER := 1.3.7
VORBIS_URL := http://downloads.xiph.org/releases/vorbis/libvorbis-$(VORBIS_VER).tar.xz
$(SRCDIR)/libvorbis-$(VORBIS_VER).tar.xz:
	cd $(SRCDIR) && $(DL) -O $(VORBIS_URL)
$(BUILDDIR)/libvorbis-$(VORBIS_VER): $(SRCDIR)/libvorbis-$(VORBIS_VER).tar.xz
	$(UNTAR_XZ) $< -C $(BUILDDIR)
vorbis: $(BUILDDIR)/libvorbis-$(VORBIS_VER) ogg
	$(MAKE) -f $(FF3PT)/vorbis/Makefile -C $<
	$(COPY) $</*.$(SO) $(BINDIR)

WAVPACK_VER := 4.75.0
$(SRCDIR)/wavpack-$(WAVPACK_VER).tar.bz2:
	cd $(SRCDIR) && $(DL) -O http://www.wavpack.com/wavpack-$(WAVPACK_VER).tar.bz2
$(BUILDDIR)/wavpack-$(WAVPACK_VER): $(SRCDIR)/wavpack-$(WAVPACK_VER).tar.bz2
	$(UNTAR_BZ2) $(SRCDIR)/wavpack-$(WAVPACK_VER).tar.bz2 -C $(BUILDDIR)
wavpack: $(BUILDDIR)/wavpack-$(WAVPACK_VER)
	$(MAKE) -f $(FF3PT)/wavpack/Makefile -C $(BUILDDIR)/wavpack-$(WAVPACK_VER)
	$(COPY) $(BUILDDIR)/wavpack-$(WAVPACK_VER)/*.$(SO) $(BINDIR)


# ENCRYPTION

$(SRCDIR)/aes:
	cd $(SRCDIR) && git clone --depth=1 https://github.com/BrianGladman/aes.git

$(BUILDDIR)/aes: $(SRCDIR)/aes
	$(COPY) -r $(SRCDIR)/aes $(BUILDDIR)

aes: $(BUILDDIR)/aes
	$(MAKE) -f $(FF3PT)/aes/Makefile -C $(BUILDDIR)/aes
	$(COPY) $(BUILDDIR)/aes/*.a $(BINDIR)


# PIC

JPEGTURBO_VER := 2.1.0
JPEGTURBO_URL := https://github.com/libjpeg-turbo/libjpeg-turbo/archive/refs/tags/$(JPEGTURBO_VER).zip
$(SRCDIR)/libjpeg-turbo-$(JPEGTURBO_VER).zip:
	cd $(SRCDIR) && $(DL) -O $(JPEGTURBO_URL)
$(BUILDDIR)/libjpeg-turbo-$(JPEGTURBO_VER): $(SRCDIR)/libjpeg-turbo-$(JPEGTURBO_VER).zip
	$(UNZIP) $< -d $(BUILDDIR)
jpeg-turbo: $(BUILDDIR)/libjpeg-turbo-$(JPEGTURBO_VER)
	$(MAKE) -f $(FF3PT)/jpeg-turbo/Makefile -C $<
	$(COPY) $</*.$(SO) $(BINDIR)

PNG_VER := 1.6.37
PNG_URL := https://download.sourceforge.net/libpng/libpng-$(PNG_VER).tar.xz
$(SRCDIR)/libpng-$(PNG_VER).tar.xz:
	cd $(SRCDIR) && $(DL) -O $(PNG_URL)
$(BUILDDIR)/libpng-$(PNG_VER): $(SRCDIR)/libpng-$(PNG_VER).tar.xz
	$(UNTAR_XZ) $< -C $(BUILDDIR)
png: $(BUILDDIR)/libpng-$(PNG_VER)
	$(MAKE) -f $(FF3PT)/png/Makefile -C $<
	$(COPY) $</*.$(SO) $(BINDIR)
