/** Base64 converter.
Simon Zolin, 2018 */

#include <stdlib.h>

extern size_t base64_encode(char *dst, size_t cap, const void *src, size_t len);
