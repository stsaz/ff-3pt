/** FDK-AAC interface for FF.
Simon Zolin, 2016 */

#include <stdlib.h>


#ifdef WIN32
#define EXP  __declspec(dllexport)
#else
#define EXP  __attribute__((visibility("default")))
#endif

typedef void fdkaac_decoder;

#ifdef __cplusplus
extern "C" {
#endif

EXP int fdkaac_decode_open(fdkaac_decoder **dec, const char *conf, size_t len);

EXP void fdkaac_decode_free(fdkaac_decoder *dec);

/**
Return the number of decoded samples;  0 if more data is needed;  <0 on error. */
EXP int fdkaac_decode(fdkaac_decoder *dec, const char *data, size_t len, short *pcm);

#ifdef __cplusplus
}
#endif

#undef EXP
