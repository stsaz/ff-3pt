/**
Simon Zolin, 2016 */

#include <lzma-ff.h>
#include <common.h>
#include <lzma.h>
#include <common/block_decoder.h>


static const char* const errs[] = {
	"LZMA_OK",
	"LZMA_STREAM_END",
	"LZMA_NO_CHECK",
	"LZMA_UNSUPPORTED_CHECK",
	"LZMA_GET_CHECK",
	"LZMA_MEM_ERROR",
	"LZMA_MEMLIMIT_ERROR",
	"LZMA_FORMAT_ERROR",
	"LZMA_OPTIONS_ERROR",
	"LZMA_DATA_ERROR",
	"LZMA_BUF_ERROR",
	"LZMA_PROG_ERROR",
};

const char* lzma_errstr(int e)
{
	e = -e;
	if ((unsigned int)e > sizeof(errs) / sizeof(*errs))
		return "unknown error";
	return errs[e];
}


struct lzma_decoder {
	lzma_next_coder blk_dec;
	lzma_block blk;
};

int lzma_decode_init(lzma_decoder **pdec, unsigned int check_method, const lzma_filter_props *fp, unsigned int nfilt)
{
	int r;
	unsigned int i;

	lzma_filter filters[LZMA_FILTERS_MAX + 1] = {0};
	for (i = 0;  i != nfilt;  i++) {
		filters[i].id = fp[i].id;
		filters[i].options = NULL;
		r = lzma_properties_decode(&filters[i], NULL, (void*)fp[i].props, fp[i].prop_len);
		if (r != LZMA_OK)
			goto end;
	}
	filters[i].id = LZMA_VLI_UNKNOWN;
	filters[i].options = NULL;

	lzma_block blk = {0};
	blk.header_size = LZMA_BLOCK_HEADER_SIZE_MIN;
	blk.check = check_method;
	blk.version = 1;
	blk.ignore_check = 0;
	blk.compressed_size = LZMA_VLI_UNKNOWN;
	blk.uncompressed_size = LZMA_VLI_UNKNOWN;
	blk.filters = filters;

	lzma_decoder *dec;
	if (NULL == (dec = calloc(1, sizeof(lzma_decoder)))) {
		r = LZMA_MEM_ERROR;
		goto end;
	}

	lzma_next_coder blk_dec = LZMA_NEXT_CODER_INIT;
	dec->blk_dec = blk_dec;
	dec->blk = blk;
	r = lzma_block_decoder_init(&dec->blk_dec, NULL, &dec->blk);

	if (r != LZMA_OK) {
		lzma_decode_free(dec);
		goto end;
	}
	*pdec = dec;
	r = 0;

end:
	for (i = 0;  i != nfilt;  i++)
		lzma_free(filters[i].options, NULL);
	return -r;
}

void lzma_decode_free(lzma_decoder *dec)
{
	lzma_next_end(&dec->blk_dec, NULL);
	free(dec);
}

int lzma_decode(lzma_decoder *dec, const char *data, size_t *len, char *dst, size_t cap)
{
	size_t inpos = 0, outpos = 0;
	int r = dec->blk_dec.code(dec->blk_dec.coder, NULL
		, (void*)data, &inpos, *len, (void*)dst, &outpos, cap
		, LZMA_FINISH);
	*len = inpos;

	switch (r) {
	case LZMA_STREAM_END:
		if (outpos == 0) {
			lzma_next_end(&dec->blk_dec, NULL);
			return LZMA_DONE;
		}
		// break

	case LZMA_OK:
		return outpos;
	}

	return -r;
}

lzma_ret lzma_stream_decoder_init(lzma_next_coder *next, const lzma_allocator *allocator, uint64_t memlimit, uint32_t flags){}
