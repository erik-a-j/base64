#include <stddef.h>
#include <stdint.h>

static inline char b64_char(uint8_t v)
{
    return (v < 26 ? 'A' + v
                   : (v < 52 ? 'a' + (v - 26) : (v < 62 ? '0' + (v - 52) : (v & 1 ? '/' : '='))));
}

void b64_encode(char* restrict dst, size_t dstlen, const uint8_t* restrict src, size_t srclen)
{
    char* p = dst;
    size_t i = 0;
    for (; i + 3 <= srclen; i += 3)
    {
        *p++ = b64_char((src[i] >> 2) & 0x3F);
        *p++ = b64_char(((src[i] << 4) + (src[i + 1] >> 4)) & 0x3F);
        *p++ = b64_char(((src[i + 1] << 2) + (src[i + 2] >> 6)) & 0x3F);
        *p++ = b64_char(src[i + 2] & 0x3F);
    }
    size_t rem = srclen - i;
    if (rem == 1)
    {
        *p++ = b64_char((src[i] >> 2) & 0x3F);
        *p++ = b64_char((src[i] << 4) & 0x3F);
        *p++ = '=';
        *p++ = '=';
    }
    else if (rem == 2)
    {
        *p++ = b64_char((src[i] >> 2) & 0x3F);
        *p++ = b64_char(((src[i] << 4) + (src[i + 1] >> 4)) & 0x3F);
        *p++ = b64_char((src[i + 1] << 2) & 0x3F);
        *p++ = '=';
    }
    if (dstlen > (size_t)(p - dst)) *p = '\0';
}