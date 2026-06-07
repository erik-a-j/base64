
#include <stddef.h>
#include <stdint.h>

static const char* B64_ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static inline void b64_internal_encode_fast(char* restrict dst,
                                            const uint8_t* restrict src,
                                            size_t srclen,
                                            const char* alpha)
{
    while (srclen)
    {
        *dst++ = alpha[(src[0] >> 2) & 0x3F];
        *dst++ = alpha[((src[0] << 4) + (src[1] >> 4)) & 0x3F];
        *dst++ = alpha[((src[1] << 2) + (src[2] >> 6)) & 0x3F];
        *dst++ = alpha[src[2] & 0x3F];

        srclen -= 3;
        src += 3;
    }
}

static inline void b64_internal_encode(char* restrict dst,
                                       size_t dstlen,
                                       const uint8_t* restrict src,
                                       size_t srclen,
                                       const char* alpha)
{
    if (dst && src)
    {
        if (dstlen % 4 == 0 && srclen == (dstlen >> 2) * 3)
        {
            b64_internal_encode_fast(dst, src, srclen, alpha);
        }
        else
        {
            while (srclen && dstlen)
            {
                uint8_t idx = (src[0] >> 2) & 0x3F;
                *dst++ = alpha[idx];
                if (!--dstlen) break;

                idx = ((src[0] << 4) & 0x30) + (--srclen ? (src[1] >> 4) & 0x0F : 0);
                *dst++ = alpha[idx];
                if (!--dstlen) break;

                idx =
                    srclen ? ((src[1] << 2) & 0x3C) + (--srclen ? (src[2] >> 6) & 0x03 : 0) : 0x40;
                *dst++ = (idx <= 0x3F ? alpha[idx] : '=');
                if (!--dstlen) break;

                idx = src[2] & 0x3F;
                *dst++ = srclen ? alpha[idx] : '=';
                if (!--dstlen) break;

                if (srclen && --srclen) src += 3;
            }
            if (dstlen) *dst = '\0';
        }
    }
}

void b64_encode(char* dst, size_t dstlen, const uint8_t* src, size_t srclen)
{
    b64_internal_encode(dst, dstlen, src, srclen, B64_ALPHA);
}