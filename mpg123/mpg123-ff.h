/** libmpg123 interface for FF.
Simon Zolin, 2016 */

#include <stdlib.h>


#ifdef WIN32
#define EXP  __declspec(dllexport)
#else
#define EXP  __attribute__((visibility("default")))
#endif

typedef struct mpg123 mpg123;

#ifndef MPG123_EXP
enum MPG123_F {
	MPG123_FORCE_FLOAT = 0x400,
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

EXP const char* mpg123_errstr(int e);

EXP int mpg123_init(void);

/**
@flags: enum MPG123_F.
Return 0 on success. */
EXP int mpg123_open(mpg123 **m, unsigned int flags);

EXP void mpg123_free(mpg123 *m);

/**
@audio: interleaved audio buffer
If data==-1 and size==-1, reset internal input buffer.
Return the number of bytes in audio buffer;  0 if more data is needed;  <0 on error. */
EXP int mpg123_decode(mpg123 *m, const char *data, size_t size, unsigned char **audio);

#ifdef __cplusplus
}
#endif

#undef EXP
