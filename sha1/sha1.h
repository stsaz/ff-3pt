/** SHA-1 generator.
Simon Zolin, 2018 */


#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
typedef unsigned char u_char;

#ifdef WIN32
#define EXP  __declspec(dllexport)
#else
#define EXP  __attribute__((visibility("default")))
#endif


typedef struct sha1_ctx {
	uint64_t bytes;
	uint32_t a, b, c, d, e, f;
	u_char buffer[64];
} sha1_ctx;
#define SHA1_LENGTH 20

#ifdef __cplusplus
extern "C" {
#endif

EXP void sha1_init(sha1_ctx *ctx);

EXP void sha1_fin(sha1_ctx *ctx, u_char result[SHA1_LENGTH]);

EXP void sha1_update(sha1_ctx *ctx, const void *data, size_t size);

#ifdef __cplusplus
}
#endif

#undef EXP
