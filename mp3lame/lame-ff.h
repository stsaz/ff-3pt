/** libmp3lame interface for FF.
Simon Zolin, 2016 */

#include <stdlib.h>


#ifdef WIN32
#define EXP  __declspec(dllexport)
#else
#define EXP  __attribute__((visibility("default")))
#endif

typedef struct lame lame;

typedef struct lame_params {
	unsigned int format;
	unsigned int interleaved;
	unsigned int channels;
	unsigned int rate;
	unsigned int quality;
} lame_params;

#ifdef __cplusplus
extern "C" {
#endif

EXP const char* lame_errstr(int e);

/**
Return 0 on success. */
EXP int lame_create(lame **lm, lame_params *conf);

EXP void lame_free(lame *lm);

/**
Return the number of bytes written;  0 if more data is needed;  <0 on error. */
EXP int lame_encode(lame *lm, const void **pcm, unsigned int samples, char *buf, size_t cap);

/** Get LAME-tag frame. */
EXP int lame_lametag(lame *lm, char *buf, size_t cap);

#ifdef __cplusplus
}
#endif

#undef EXP
