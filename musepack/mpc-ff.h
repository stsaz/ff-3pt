/** libmpc interface for FF.
Simon Zolin, 2017 */

#pragma once

#include <stdlib.h>


#ifdef WIN32
#define EXP  __declspec(dllexport)
#else
#define EXP  __attribute__((visibility("default")))
#endif

typedef struct mpc_ctx mpc_ctx;

enum {
	MPC_ABUF_CAP = 36 * 32 * 4 * sizeof(float), // required capacity of output audio buffer
	MPC_FRAME_MAXSIZE = 4352, // max. frame size
};

#ifdef __cplusplus
extern "C" {
#endif

EXP const char* mpc_errstr(int e);


/** Initialize decoder.
@sh_block: SH block body
Return 0 on success;  <0: error. */
EXP int mpc_decode_open(mpc_ctx **pc, const void *sh_block, size_t len);

EXP void mpc_decode_free(mpc_ctx *c);

EXP void mpc_decode_input(mpc_ctx *c, const void *block, size_t len);

/** Decode one frame in a block.
@pcm: output samples.  Its size must be MPC_ABUF_CAP.
Return the number of audio samples decoded;  0 if need next block;  <0 on error. */
EXP int mpc_decode(mpc_ctx *c, float *pcm);

#ifdef __cplusplus
}
#endif

#undef EXP