/** libDynamicAudioNormalizer interface for FF.
Simon Zolin, 2018 */

#include <stdlib.h>


#ifdef WIN32
#define EXP  __declspec(dllexport)
#else
#define EXP  __attribute__((visibility("default")))
#include <sys/types.h>
#endif


struct dynanorm_conf {
	unsigned int channels;
	unsigned int sampleRate;
	unsigned int frameLenMsec;
	unsigned int filterSize;
	double peakValue;
	double maxAmplification;
	double targetRms;
	double compressFactor;
	unsigned int channelsCoupled :1;
	unsigned int enableDCCorrection :1;
	unsigned int altBoundaryMode :1;
};

#ifdef __cplusplus
extern "C" {
#endif

EXP void dynanorm_init(struct dynanorm_conf *conf);

/**
Return 0 on success. */
EXP int dynanorm_open(void **c, struct dynanorm_conf *conf);

EXP void dynanorm_close(void *c);

/** Process audio data.
@samples: input samples;  on return contains number of samples processed.
Return the number of output samples;  <0 on error. */
EXP ssize_t dynanorm_process(void *cc, const double *const *in, size_t *samples, double **out, size_t max_samples);

#ifdef __cplusplus
}
#endif

#undef EXP
