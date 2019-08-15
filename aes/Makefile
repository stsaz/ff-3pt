# Brian Gladman's AES for FF
# Simon Zolin, 2019

OPT := 3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += -I.


SRC := \
	aesaux.c \
	aes_avs.c \
	aescrypt.c \
	aesgav.c \
	aeskey2.c \
	aeskey.c \
	aes_modes.c \
	aes_ni.c \
	aesrav.c \
	aestab.c

OBJ := aes-ff.o $(SRC:.c=.o)

%.o: $(FF3PT)/aes/%.c
	$(C) $(CFLAGS) -I$(FF3PT)/aes $< -o$@

%.o: %.c $(wildcard ./*.h)
	$(C) $(CFLAGS) $< -o$@

all:
	#cat $(FF3PT)/aes/*.patch | patch -p1
	$(MAKE) -f $(firstword $(MAKEFILE_LIST)) AES-ff.a

AES-ff.a: $(OBJ)
	$(AR) rcs $@ $(OBJ)

clean:
	rm -fv $(OBJ) AES-ff.a
