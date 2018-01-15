---------------
3-PARTY LIBRARIES FOR FF
---------------

In order to be used by FF all these libraries must be built in a specific way.  A library itself may have a different API that's easier to use and more suitable for FF.  Library's code may also contain modifications.  The functionality that's not used by FF is either removed or disabled; FF doesn't use the official include files.  The libraries aren't compatible with any applications that use the official builds, so to eliminate ambiguity the filenames of the binaries have "-ff" suffix, e.g. "libNAME-ff.so".

AUDIO:
. alac-rev2
. fdk-aac-0.1.4
. flac-1.3.2
. lame-3.99.5
. MAC-433
. mad-0.15.1b
. mpg123-1.25.3
. musepack-r475
. ogg-1.3.2
. soxr-0.1.2
. vorbis-1.3.5
. wavpack-4.75.0

COMPRESSION:
. xz-5.2.2 (liblzma)
. zlib-1.2.8

PICTURES:
. jpeg-9b
. png-1.6.24

DATABASE
. sqlite-3.16.2

OTHER CODE:
. crc/: Fast CRC32 from liblzma
. vorbis/ogg-crc.h: CRC32 table for OGG page

---------------
HOWTO BUILD
---------------

1. Download library sources, unpack, 'cd' to it.

2. Apply patches if necessary:

	cat {FF3PT}/{LIB}/*.patch | patch -p1
or
	git am {FF3PT}/{LIB}/*.patch

3. Build the library.

	make -rRf {FF3PT}/{LIB}/Makefile FF3PT={FF3PT} [ARCH=i686] [OS=win CPREFIX=x86_64-w64-mingw32-]

4. Done, new .so or .dll binaries will be created in the current directory.


---------------
LICENSE
---------------

This repository contains copies of original and auto-generated code from 3rd party libraries.  This code is the property of their owners.  This code and binary/object files created using this code are licensed accordingly to the licenses of those libraries.

All other code provided here is free for use in open-source and proprietary projects.
You may distribute, redistribute, modify the whole code or the parts of it, just keep the original copyright statement inside the files.


Simon Zolin <stsaz@yandex.ru>
