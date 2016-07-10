/** liblzma interface for FF.
Simon Zolin, 2016 */

#include <stdlib.h>


#ifdef WIN32
#define EXP  __declspec(dllexport)
#else
#define EXP  __attribute__((visibility("default")))
#endif

typedef struct lzma_decoder lzma_decoder;

typedef struct lzma_filter_props {
	unsigned long long id;
	unsigned long long prop_len;
	const char *props;
} lzma_filter_props;

enum LZMA_ERR {
	LZMA_DONE = -0x100,
	//any other code is an error
};

#ifdef __cplusplus
extern "C" {
#endif

EXP const char* lzma_errstr(int e);


/** Initialize block decoder.
@fi: filter properties from block header.
Return 0 on success. */
EXP int lzma_decode_init(lzma_decoder **dec, unsigned int check_method, const lzma_filter_props *fi, unsigned int nfilt);

EXP void lzma_decode_free(lzma_decoder *dec);

/** Decode 1 block.
Return the number of bytes written;  0 if more data is needed;  enum LZMA_ERR on error. */
EXP int lzma_decode(lzma_decoder *dec, const char *data, size_t *len, char *dst, size_t cap);

#ifdef __cplusplus
}
#endif

#undef EXP
