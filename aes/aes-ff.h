/** AES interface.
Simon Zolin, 2019 */

#include <stdlib.h>


#ifdef WIN32
#define EXP  __declspec(dllexport)
#else
#define EXP  __attribute__((visibility("default")))
#endif


enum AES_MODE {
	AES_CBC,
	AES_CFB,
	AES_OFB,
};

typedef struct aes_ctx {
	void *ctx;
	unsigned int mode;
} aes_ctx;


#ifdef __cplusplus
extern "C" {
#endif

EXP int aes_decrypt_init(aes_ctx *a, const unsigned char *key, size_t key_len, unsigned int flags);

static inline void aes_decrypt_free(aes_ctx *a)
{
	free(a->ctx);  a->ctx = NULL;
}

EXP int aes_decrypt_chunk(aes_ctx *a, const unsigned char *in, unsigned char *out,
	size_t len, unsigned char *iv);


EXP int aes_encrypt_init(aes_ctx *a, const unsigned char *key, size_t key_len, unsigned int flags);

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
