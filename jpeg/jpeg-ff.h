/** libjpeg interface for FF.
Simon Zolin, 2016 */

#include <stdlib.h>


#ifdef WIN32
#define EXP  __declspec(dllexport)
#else
#define EXP  __attribute__((visibility("default")))
#endif

struct jpeg_reader;
struct jpeg_writer;

struct jpeg_conf {
	unsigned int width;
	unsigned int height;
	unsigned int quality;
	unsigned int buf_size;
};

enum {
	JPEG_RMORE,
	JPEG_RDONE = -2,
};

#ifdef __cplusplus
extern "C" {
#endif

EXP const char* jpeg_errstr(void *j);


/** Read header.
@j: must point to NULL object on the first call.
Return 1 on success;  0 if more data is needed;  <0 on error (note: *j may be allocated). */
EXP int jpeg_open(struct jpeg_reader **j, const void *data, size_t *len, struct jpeg_conf *conf);

EXP void jpeg_free(struct jpeg_reader *j);

/** Read one line.
@line: receives uncompressed data;  must be large enough for a full line.
Return 1 if line is ready;  0 if more data is needed;  -2 if done;  <0 on error. */
EXP int jpeg_read(struct jpeg_reader *j, const void *data, size_t *len, void *line);


/** Prepare to write.
@conf: 'width', 'height', 'quality', 'buf_size' are required parameters.
Return 0 on success;  <0 on error (note: *j may be allocated). */
EXP int jpeg_create(struct jpeg_writer **j, struct jpeg_conf *conf);

EXP void jpeg_wfree(struct jpeg_writer *j);

/** Write one line.
@data: JPEG data;  must be of size 'jpeg_conf.buf_size'.
Return number of bytes written;  0 if more data is needed;  -2 if done;  <0 on error. */
EXP int jpeg_write(struct jpeg_writer *j, const void *line, void *data);

#ifdef __cplusplus
}
#endif

#undef EXP
