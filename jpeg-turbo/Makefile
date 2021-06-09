# libjpeg-turbo for FF
# Simon Zolin, 2021

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-I./build -I. -I$(FF3PT)/jpeg-turbo

LDFLAGS +=

SRC_C := \
	jcapimin.c \
	jcapistd.c \
	jccoefct.c \
	jccolor.c \
	jcdctmgr.c \
	jchuff.c \
	jcicc.c \
	jcinit.c \
	jcmainct.c \
	jcmarker.c \
	jcmaster.c \
	jcomapi.c \
	jcparam.c \
	jcphuff.c \
	jcprepct.c \
	jcsample.c \
	jctrans.c \
	jdapimin.c \
	jdapistd.c \
	jdatadst.c \
	jdatasrc.c \
	jdcoefct.c \
	jdcolor.c \
	jddctmgr.c \
	jdhuff.c \
	jdicc.c \
	jdinput.c \
	jdmainct.c \
	jdmarker.c \
	jdmaster.c \
	jdmerge.c \
	jdphuff.c \
	jdpostct.c \
	jdsample.c \
	jdtrans.c \
	jerror.c \
	jfdctflt.c \
	jfdctfst.c \
	jfdctint.c \
	jidctflt.c \
	jidctfst.c \
	jidctint.c \
	jidctred.c \
	jquant1.c \
	jquant2.c \
	jutils.c \
	jmemmgr.c \
	jmemnobs.c \
	jaricom.c \
	jcarith.c \
	jdarith.c

SRC_ASM := \
	jsimdcpu.asm \
	jfdctflt-sse.asm \
	jccolor-sse2.asm \
	jcgray-sse2.asm \
	jchuff-sse2.asm \
	jcphuff-sse2.asm \
	jcsample-sse2.asm \
	jdcolor-sse2.asm \
	jdmerge-sse2.asm \
	jdsample-sse2.asm \
	jfdctfst-sse2.asm \
	jfdctint-sse2.asm \
	jidctflt-sse2.asm \
	jidctfst-sse2.asm \
	jidctint-sse2.asm \
	jidctred-sse2.asm \
	jquantf-sse2.asm \
	jquanti-sse2.asm \
	jccolor-avx2.asm \
	jcgray-avx2.asm \
	jcsample-avx2.asm \
	jdcolor-avx2.asm \
	jdmerge-avx2.asm \
	jdsample-avx2.asm \
	jfdctint-avx2.asm \
	jidctint-avx2.asm \
	jquanti-avx2.asm

SRC_C += jsimd.c

OBJ := jpeg-ff.o $(SRC_C:.c=.o) $(SRC_ASM:.asm=.asm.o)

%.o: $(FF3PT)/jpeg-turbo/%.c
	$(C) $(CFLAGS) $< -o$@

%.o: simd/x86_64/%.c $(wildcard ./*.h)
	$(C) $(CFLAGS) $<  -o$@

%.o: %.c $(wildcard ./*.h)
	$(C) $(CFLAGS) $<  -o$@

NASMFLAGS := -I./simd/nasm -I./simd/x86_64 -I. -I$(FF3PT)/jpeg-turbo \
	-D__x86_64__ -DPIC
ifeq ($(OS),win)
	NASMFLAGS += -DWIN64  -f win64
else
	NASMFLAGS += -DELF -f elf64
endif
%.asm.o: simd/x86_64/%.asm
	nasm $(NASMFLAGS) $< -o $@

libjpeg-turbo-ff.$(SO): $(OBJ)
	#mkdir -p build
	#cd build && cmake -G"Unix Makefiles" -DWITH_JPEG8=1 ..
	#cd build && make -j8 VERBOSE=1
	$(LD) $(LDFLAGS) $(LD_INSTNAME_LDRPATH) -shared $+ -o libjpeg-turbo-ff.$(SO)

clean:
	rm -fv $(OBJ) libjpeg-turbo-ff.$(SO)
