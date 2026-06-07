#include <immintrin.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static void b64_encode_scalar(char* restrict dst,
                              size_t dstlen,
                              const uint8_t* restrict src,
                              size_t srclen);

static const uint8_t expand_shuf[64] = {
    1,  0,  2,  1,  4,  3,  5,  4,  7,  6,  8,  7,  10, 9,  11, 10, 13, 12, 14, 13, 16, 15,
    17, 16, 19, 18, 20, 19, 22, 21, 23, 22, 25, 24, 26, 25, 28, 27, 29, 28, 31, 30, 32, 31,
    34, 33, 35, 34, 37, 36, 38, 37, 40, 39, 41, 40, 43, 42, 44, 43, 46, 45, 47, 46,
};

__attribute__((target("avx512f,avx512vbmi,avx512bw"))) void b64_encode(char* restrict dst,
                                                                       size_t dstlen,
                                                                       const uint8_t* restrict src,
                                                                       size_t srclen)
{
    const __m512i shuf = _mm512_loadu_si512(expand_shuf);
    const __m512i alpha =
        _mm512_loadu_si512("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
    const __m512i mask0 = _mm512_set1_epi32(0x0FC0FC00);
    const __m512i mask1 = _mm512_set1_epi32(0x003F03F0);
    const __m512i mul0 = _mm512_set1_epi32(0x04000040);
    const __m512i mul1 = _mm512_set1_epi32(0x01000010);

    char* p = dst;
    size_t i = 0;

    // 48 bytes in → 64 chars out per iteration
    // Load reads 64 bytes: only run while 64 bytes are safely readable
    for (; i + 64 <= srclen; i += 48)
    {
        __m512i in = _mm512_loadu_si512(src + i);  // load 64, use 48
        in = _mm512_permutexvar_epi8(shuf, in);    // expand
        __m512i t0 = _mm512_and_si512(in, mask0);
        __m512i t1 = _mm512_and_si512(in, mask1);
        t0 = _mm512_mulhi_epu16(t0, mul0);
        t1 = _mm512_mullo_epi16(t1, mul1);
        __m512i chars = _mm512_permutexvar_epi8(_mm512_or_si512(t0, t1), alpha);
        _mm512_storeu_si512(p, chars);  // write 64 chars
        p += 64;
    }

    // Scalar remainder
    b64_encode_scalar(p, dstlen - (p - dst), src + i, srclen - i);
}

void b64_encode_scalar(char* restrict dst,
                       size_t dstlen,
                       const uint8_t* restrict src,
                       size_t srclen)
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

#if 1
#include <stdio.h>
int main(void)
{
    uint8_t data[256];
    for (uint8_t* p = data; (size_t)(p - data) < sizeof(data); ++p)
    {
        *p = (uint8_t)(p - data);
    }
    char b64[(4 * ((sizeof(data) + 2) / 3)) + 1] = {0};

    b64_encode(b64, sizeof(b64), data, sizeof(data));
    printf("%s\n", b64);
    return 0;
}
#endif