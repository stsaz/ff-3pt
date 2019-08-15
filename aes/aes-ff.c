/**
Simon Zolin, 2019 */

#include <aes-ff.h>
#include <aes.h>


int aes_decrypt_init(aes_ctx *a, const unsigned char *key, size_t key_len)
{
	a->ctx = calloc(1, sizeof(aes_decrypt_ctx));
	return aes_decrypt_key(key, key_len, a->ctx);
}

int aes_decrypt_chunk(aes_ctx *a, const unsigned char *in, unsigned char *out,
	size_t len, unsigned char *iv)
{
	return aes_cbc_decrypt(in, out, len, iv, a->ctx);
}


int aes_encrypt_init(aes_ctx *a, const unsigned char *key, size_t key_len)
{
	a->ctx = calloc(1, sizeof(aes_encrypt_ctx));
	return aes_encrypt_key(key, key_len, a->ctx);
}

int aes_encrypt_chunk(aes_ctx *a, const unsigned char *in, unsigned char *out,
	size_t len, unsigned char *iv)
{
	return aes_cbc_encrypt(in, out, len, iv, a->ctx);
}
