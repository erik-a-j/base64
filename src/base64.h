#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define B64_ENCODE_SIZE(dec_size) (4 * (((dec_size) + 2) / 3))
#define B64_DECODE_SIZE(enc_size) (3 * ((enc_size) / 4))

void b64_encode(char* dst, size_t dstlen, const uint8_t* src, size_t srclen);
void b64_encode_fd(char* dst, size_t dstlen, int fd, size_t srclen);
void b64url_encode(char* dst, size_t dstlen, const uint8_t* src, size_t srclen);
size_t b64_decode(uint8_t* dst, const char* src, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BASE64_H */
