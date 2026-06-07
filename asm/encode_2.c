#include <stddef.h>
#include <stdint.h>

void b64_encode(char* restrict dst, size_t dstlen, const uint8_t* restrict src, size_t srclen)
{
    const char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char* p = dst;
    size_t i = 0;
    for (; i + 3 <= srclen; i += 3)
    {
        *p++ = alpha[(src[i] >> 2) & 0x3F];
        *p++ = alpha[((src[i] << 4) + (src[i + 1] >> 4)) & 0x3F];
        *p++ = alpha[((src[i + 1] << 2) + (src[i + 2] >> 6)) & 0x3F];
        *p++ = alpha[src[i + 2] & 0x3F];
    }
    size_t rem = srclen - i;
    if (rem == 1)
    {
        *p++ = alpha[(src[i] >> 2) & 0x3F];
        *p++ = alpha[(src[i] << 4) & 0x3F];
        *p++ = '=';
        *p++ = '=';
    }
    else if (rem == 2)
    {
        *p++ = alpha[(src[i] >> 2) & 0x3F];
        *p++ = alpha[((src[i] << 4) + (src[i + 1] >> 4)) & 0x3F];
        *p++ = alpha[(src[i + 1] << 2) & 0x3F];
        *p++ = '=';
    }
    if (dstlen > (size_t)(p - dst)) *p = '\0';
}