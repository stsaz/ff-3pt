/** libALAC interface for FF.
Simon Zolin, 2016 */

#include <stdlib.h>


#ifdef WIN32
#define EXP  __declspec(dllexport)
#else
#define EXP  __attribute__((visibility("default")))
#endif

typedef struct alac_ctx alac_ctx;

#ifdef __cplusplus
extern "C" {
#endif

/**
Return NULL on error. */
EXP alac_ctx* alac_init(const char *magic_cookie, size_t len);

EXP void alac_free(alac_ctx *a);

/** Decode 1 frame.
Return the number of decoded samples;  0 if more data is needed;  <0 on error. */
EXP int alac_decode(alac_ctx *a, const char *data, size_t len, void *pcm);

#ifdef __cplusplus
}
#endif

#undef EXP
