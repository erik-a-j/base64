#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define B64_ENCODE_SIZE(dec_size) ((4 * (((dec_size) + 2) / 3)) + 1)
#define B64_DECODE_SIZE(enc_size) (3 * ((enc_size) / 4))

size_t b64_encode(char* dst, const uint8_t* src, size_t len);
size_t b64url_encode(char* dst, const uint8_t* src, size_t len);
size_t b64_decode(uint8_t* dst, const char* src, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BASE64_H */
