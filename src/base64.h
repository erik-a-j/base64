#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define B64_ENCODE_SIZE(dec_size) ((4 * (((dec_size) + 2) / 3)) + 1)
#define B64_DECODE_SIZE(enc_size) (3 * ((enc_size) / 4))

char* b64_encode(const uint8_t* src, size_t src_len, char* out);
char* b64url_encode(const uint8_t* src, size_t src_len, char* out);
uint8_t* b64_decode(const char* src, size_t* out_len, uint8_t* out);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BASE64_H */
