---------------
3-PARTY LIBRARIES FOR FF
---------------

In order to be used by FF all these libraries must be built in a specific way.  A library itself may have a different API that's easier to use and more suitable for FF.  Library's code may also contain modifications.  The functionality that's not used by FF is either removed or disabled; FF doesn't use the official include files.  The libraries aren't compatible with any applications that use the official builds, so to eliminate ambiguity the filenames of the binaries have "-ff" suffix, e.g. "libNAME-ff.so".  The only platforms supported are linux-amd64 and win-x64.

AUDIO:
. alac-rev2
. fdk-aac-0.1.4
. flac-1.3.1
. lame-3.99.5
. MAC-416
. mad-0.15.1b
. mpg123-1.22.4
. ogg-1.3.2
. soxr-0.1.2
. vorbis-1.3.5
. wavpack-4.75.0

COMPRESSION:
. xz-5.2.2 (liblzma)
. zlib-1.2.8

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

	make -rRf {FF3PT}/{LIB}/Makefile FF3PT={FF3PT} [OS=win COMPILER=mingw]

4. Done, new .so or .dll binaries will be created in the current directory.
