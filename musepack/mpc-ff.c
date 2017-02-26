/**
Simon Zolin, 2017 */

#include <mpc-ff.h>
#include <mpc/mpcdec.h>


enum {
	MPC_EOK,
	MPC_EMEM,
	MPC_EHDR,
	MPC_EINCOMPLETE,
	MPC_EUNPROCESSED,
};

static const char* const errs[] = {
	"",
	"memory allocation",
	"bad header",
	"incomplete block",
	"unprocessed data inside block",
};

const char* mpc_errstr(int e)
{
	e = -e;
	if (e > sizeof(errs) / sizeof(*errs))
		return "";
	return errs[e];
}


struct mpc_ctx {
	mpc_decoder *d;
	mpc_streaminfo si;
	unsigned int block_frames;
	mpc_bits_reader br;
	size_t buflen;
	unsigned int is_key_frame :1;
};

extern mpc_status streaminfo_read_header_sv8(mpc_streaminfo* si, const mpc_bits_reader * r_in, mpc_size_t block_size);

int mpc_decode_open(mpc_ctx **pc, const void *sh_block, size_t len)
{
	mpc_ctx *c;

	if (NULL == (c = calloc(1, sizeof(mpc_ctx))))
		return -MPC_EMEM;

	c->br.buff = (void*)sh_block;
	c->br.count = 8;
	if (0 != streaminfo_read_header_sv8(&c->si, &c->br, len)) {
		free(c);
		return -MPC_EHDR;
	}

	if (NULL == (c->d = mpc_decoder_init(&c->si))) {
		free(c);
		return -MPC_EMEM;
	}
	*pc = c;
	c->br.buff = NULL;
	c->br.count = 0;
	return 0;
}

void mpc_decode_free(mpc_ctx *c)
{
	mpc_decoder_exit(c->d);
	free(c);
}

void mpc_decode_input(mpc_ctx *c, const void *block, size_t len)
{
	c->br.buff = (void*)block;
	c->br.count = 8;
	c->buflen = len;
	c->block_frames = 1 << c->si.block_pwr;
	c->is_key_frame = 1;
}

int mpc_decode(mpc_ctx *c, float *pcm)
{
	if (c->block_frames == 0) {
		if (c->buflen > 1) {
			c->buflen = 0;
			return -MPC_EUNPROCESSED;
		}
		return 0;
	}

	const char *buf = c->br.buff;
	mpc_frame_info fr;
	fr.buffer = pcm;
	fr.is_key_frame = c->is_key_frame;
	c->is_key_frame = 0;
	mpc_decoder_decode_frame(c->d, &c->br, &fr);
	c->buflen -= (char*)c->br.buff - buf;
	if ((ssize_t)c->buflen < 0)
		return -MPC_EINCOMPLETE;
	c->block_frames--;
	return fr.samples;
}
