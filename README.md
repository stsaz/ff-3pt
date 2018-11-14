---------------
THIRD-PARTY LIBRARIES FOR FF
---------------

In order to be used by FF all these libraries must be built in a specific way.
A library itself may have a different API that's easier to use and more suitable for FF.
Library's code may also contain modifications.
The functionality that's not used by FF is either removed or disabled; FF doesn't use the official include files.
The libraries aren't compatible with any applications that use the official builds, so to eliminate ambiguity the filenames of the binaries have "-ff" suffix, e.g. "libNAME-ff.so".

AUDIO:
* alac-rev2
* DynamicAudioNormalizer-2.10
* fdk-aac-0.1.4
* flac-1.3.2
* lame-3.100
* MAC-433
* mad-0.15.1b (obsolete)
* mpg123-1.25.10
* musepack-r475
* ogg-1.3.3
* opus-1.2.1
* soxr-0.1.3
* vorbis-1.3.6
* wavpack-4.75.0

COMPRESSION:
* xz-5.2.2 (liblzma)
* zlib-1.2.8

PICTURES:
* jpeg-9b
* png-1.6.24

DATABASE
* sqlite-3.16.2
* postgresql-9.2.4-1

OTHER CODE:
* crc/: Fast CRC32 from liblzma
* ogg/ogg-crc.h: CRC32 table for OGG page
* sha1/: SHA-1 generator from nginx
* base64/: Base64 encoder from nginx

---------------
HOWTO BUILD
---------------

Requirements:
* Internet connection (if an archive doesn't exist in `./_src/` directory)
* make
* cmake (for libsoxr)
* dos2unix (for libMAC)
* patch
* gcc/clang
* g++/clang++

The build process consists of these steps:
* Download an archive with the third-party library's source code from Internet to `./_src/` directory
* Unpack an archive to `/tmp/ff3pt-build/` directory
* Execute `/tmp/ff3pt-build/{LIB}/configure` script if necessary
* Apply patch files `./{LIB_NAME}/*.patch` if necessary
* Run makefile `./{LIB_NAME}/Makefile`
* Copy the resulting binary file from `/tmp/ff3pt-build/{LIB}/` to `./_bin/{OS}-{ARCH}` directory

`./Makefile` file automates this process.  Here's how you can use it:

Build for AMD64:

	make {LIB_NAME}

Build for IA-32:

	make ARCH=i686 {LIB_NAME}

Build on Linux for Windows:

	make OS=win CPREFIX=x86_64-w64-mingw32- {LIB_NAME}

Build on Linux for Windows 32-bit:

	make OS=win CPREFIX=i686-w64-mingw32- ARCH=i686 {LIB_NAME}

For example, this command executes all the steps described above.  It builds libFLAC binary and copies it into `./_bin/linux-amd64/libFLAC-ff.so`:

	make
	make flac

`make` command without arguments is needed to create all necessary directories (_src, _bin, /tmp/ff3pt-build).

Note: archives for 'lame' and 'soxr' must be downloaded manually.

---------------
LICENSE
---------------

This repository contains copies of original and auto-generated code from 3rd party libraries.  This code is the property of their owners.  This code and binary/object files created using this code are licensed accordingly to the licenses of those libraries.

All other code provided here is free for use in open-source and proprietary projects.
You may distribute, redistribute, modify the whole code or the parts of it, just keep the original copyright statement inside the files.

---------------

Simon Zolin
