# libjpeg for FF
# Simon Zolin, 2016

OPT := LTO
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-I. -I$(FF3PT)/jpeg

LDFLAGS +=

SRC := jaricom.c \
	jcapimin.c \
	jcapistd.c \
	jcarith.c \
	jccoefct.c \
	jccolor.c \
	jcdctmgr.c \
	jchuff.c \
	jcinit.c \
	jcmainct.c \
	jcmarker.c \
	jcmaster.c \
	jcomapi.c \
	jcparam.c \
	jcprepct.c \
	jcsample.c \
	jctrans.c \
	jdapimin.c \
	jdapistd.c \
	jdarith.c \
	jdcoefct.c \
	jdcolor.c \
	jddctmgr.c \
	jdhuff.c \
	jdinput.c \
	jdmainct.c \
	jdmarker.c \
	jdmaster.c \
	jdmerge.c \
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
	jquant1.c \
	jquant2.c \
	jutils.c \
	jmemmgr.c \
	jmemnobs.c

OBJ := jpeg-ff.o $(SRC:.c=.o)

%.o: $(FF3PT)/jpeg/%.c
	$(C) $(CFLAGS) $< -o$@

%.o: %.c $(wildcard ./*.h)
	$(C) $(CFLAGS) $<  -o$@

libjpeg-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -shared -o$@

clean:
	rm -fv $(OBJ) libjpeg-ff.$(SO)
