/** libopus interface for FF.
Simon Zolin, 2016 */

#pragma once

#include <stdint.h>


#ifdef WIN32
#define EXP  __declspec(dllexport)
#else
#define EXP  __attribute__((visibility("default")))
#endif

typedef void opus_ctx;

typedef struct opus_conf {
	unsigned int channels;
} opus_conf;

enum {
	OPUS_MAX_PKT = 4000,
};

#ifdef __cplusplus
extern "C" {
#endif

EXP const char* opus_errstr(int e);


/** Initialize decoder.
Return 0 on success;  <0: error. */
EXP int opus_decode_init(opus_ctx **pc, opus_conf *conf);

EXP void opus_decode_free(opus_ctx *c);

#define OPUS_BUFLEN(rate)  (120 * (rate) / 1000)

/** Decode one packet.
Emulate packet loss: (packet=NULL, len=0).
@pcm: output samples.
Return the number of audio samples decoded;  <0 on error. */
EXP int opus_decode_f(opus_ctx *c, const void *packet, unsigned int len, float *pcm);

/** Reset decoder */
EXP void opus_decode_reset(opus_ctx *c);


/** Get vendor string needed for Opus tags packet when encoding. */
EXP const char* opus_vendor(void);

enum OPUS_APP {
	OPUS_AUDIO,
	OPUS_VOIP,
};

typedef struct opus_encode_conf {
	unsigned int channels;
	unsigned int sample_rate;
	unsigned int bitrate;
	unsigned int complexity; //1..11
	unsigned int application; //enum OPUS_APP
	unsigned int bandwidth; //either 4, 6, 8, 12, 20kHz
	unsigned int preskip; //encoder delay samples
} opus_encode_conf;

/** Initialize encoder.
Return 0 on success;  <0: error. */
EXP int opus_encode_create(opus_ctx **pc, opus_encode_conf *conf);

EXP void opus_encode_free(opus_ctx *c);

/** Compress PCM data.
@samples: number of input samples (2.5, 5, 10, 20, 40 or 60 ms).
Return packet length;  <0: error. */
EXP int opus_encode_f(opus_ctx *c, const float *pcm, int samples, void *pkt);

#ifdef __cplusplus
}
#endif

#undef EXP
