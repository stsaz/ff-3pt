/** FDK-AAC interface for FF.
Simon Zolin, 2016 */

#include <fdk-aac-ff.h>
#include <aacdecoder_lib.h>


int fdkaac_decode_open(fdkaac_decoder **pdec, const char *conf, size_t len)
{
	int r;
	HANDLE_AACDECODER dec;
	if (NULL == (dec = aacDecoder_Open(TT_MP4_RAW, 1))) {
		r = AAC_DEC_OUT_OF_MEMORY;
		goto end;
	}

	unsigned char *bdata = (void*)conf;
	unsigned int ulen = len;
	if (0 != (r = aacDecoder_ConfigRaw(dec, &bdata, &ulen))) {
		aacDecoder_Close(dec);
		goto end;
	}

	/*if (0 != (r = aacDecoder_SetParam(dec, AAC_PCM_OUTPUT_INTERLEAVED, 0))) {
		aacDecoder_Close(dec);
		goto end;
	}*/

	*pdec = dec;
	r = 0;

end:
	return r;
}

void fdkaac_decode_free(fdkaac_decoder *dec)
{
	aacDecoder_Close(dec);
}

int fdkaac_decode(fdkaac_decoder *dec, const char *data, size_t len, short *pcm)
{
	int r;
	unsigned char *bdata = (void*)data;
	unsigned int ulen = len, valid = len;
	if (0 != (r = aacDecoder_Fill(dec, &bdata, &ulen, &valid)))
		return -r;

	r = aacDecoder_DecodeFrame(dec, pcm, 0, 0);
	if (r == AAC_DEC_NOT_ENOUGH_BITS)
		return 0;
	else if (r != 0)
		return -r;

	const CStreamInfo *si = aacDecoder_GetStreamInfo(dec);
	return si->frameSize;
}
