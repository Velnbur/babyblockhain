#ifndef SHA1_H_SENTRY
#define SHA1_H_SENTRY

#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>

#define HASH_SIZE 20 /* size of returned SHA1 value in bytes */

/* Hash-function that will create a hash( an array
 * of bytes with HASH_SIZE size ) from input string.
 *
 * @return value will be allocated inside.
 */
char *SHA1(const char *message, size_t len);
#ifdef __cplusplus
}
#endif

#endif // SHA1_H_SENTRY
