#include <stddef.h>
#include <stdint.h>

void b64_encode(char* restrict dst, size_t dstlen, const uint8_t* restrict src, size_t srclen)
{
    const char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    while (srclen && dstlen)
    {
        *dst++ = alpha[(src[0] >> 2) & 0x3F];
        if (!--dstlen) break;

        *dst++ = alpha[((src[0] << 4) & 0x30) + (--srclen ? (src[1] >> 4) & 0x0F : 0)];
        if (!--dstlen) break;

        *dst++ =
            (srclen ? alpha[((src[1] << 2) & 0x3C) + (--srclen ? (src[2] >> 6) & 0x03 : 0)] : '=');
        if (!--dstlen) break;

        *dst++ = srclen ? alpha[src[2] & 0x3F] : '=';
        if (!--dstlen) break;

        if (srclen && --srclen) src += 3;
    }
    if (dstlen) *dst = '\0';
}