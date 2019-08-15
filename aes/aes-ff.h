/** AES interface.
Simon Zolin, 2019 */

#include <stdlib.h>


#ifdef WIN32
#define EXP  __declspec(dllexport)
#else
#define EXP  __attribute__((visibility("default")))
#endif


typedef struct aes_ctx {
	void *ctx;
} aes_ctx;


#ifdef __cplusplus
extern "C" {
#endif

EXP int aes_decrypt_init(aes_ctx *a, const unsigned char *key, size_t key_len);

static inline void aes_decrypt_free(aes_ctx *a)
{
	free(a->ctx);  a->ctx = NULL;
}

EXP int aes_decrypt_chunk(aes_ctx *a, const unsigned char *in, unsigned char *out,
	size_t len, unsigned char *iv);


EXP int aes_encrypt_init(aes_ctx *a, const unsigned char *key, size_t key_len);

static inline void aes_encrypt_free(aes_ctx *a)
{
	free(a->ctx);  a->ctx = NULL;
}

EXP int aes_encrypt_chunk(aes_ctx *a, const unsigned char *in, unsigned char *out,
	size_t len, unsigned char *iv);

#ifdef __cplusplus
}
#endif

#undef EXP
