
/** ===== The Base 64 Alphabet =====
 *   0 A     17 R     34 i     51 z
 *   1 B     18 S     35 j     52 0
 *   2 C     19 T     36 k     53 1
 *   3 D     20 U     37 l     54 2
 *   4 E     21 V     38 m     55 3
 *   5 F     22 W     39 n     56 4
 *   6 G     23 X     40 o     57 5
 *   7 H     24 Y     41 p     58 6
 *   8 I     25 Z     42 q     59 7
 *   9 J     26 a     43 r     60 8
 *  10 K     27 b     44 s     61 9
 *  11 L     28 c     45 t     62 +
 *  12 M     29 d     46 u     63 /
 *  13 N     30 e     47 v
 *  14 O     31 f     48 w  (pad) =
 *  15 P     32 g     49 x
 *  16 Q     33 h     50 y
 *
 *  === The Base 64 URL Alphabet ===
 *   0-61 same
 *   62 - (minus)
 *   63 _ (underline)
 */

#include "base64.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#if 0
#ifndef B64_FD_READ_BUFSIZE
#define B64_FD_READ_BUFSIZE (1200)
#endif
_Static_assert(B64_FD_READ_BUFSIZE % 3 == 0, "B64_FD_READ_BUFSIZE has to be a multiple of 3");
#endif

#define B64_INDEX_WIDTH (6)
#define B64_INDEX_MASK  ((1U << B64_INDEX_WIDTH) - 1)

static const char* B64_ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

#if 0
static const char* B64URL_ALPHA =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

static const int8_t B64_DEC[256] = {
    ['A'] = 0,  ['B'] = 1,  ['C'] = 2,  ['D'] = 3,  ['E'] = 4,  ['F'] = 5,  ['G'] = 6,  ['H'] = 7,
    ['I'] = 8,  ['J'] = 9,  ['K'] = 10, ['L'] = 11, ['M'] = 12, ['N'] = 13, ['O'] = 14, ['P'] = 15,
    ['Q'] = 16, ['R'] = 17, ['S'] = 18, ['T'] = 19, ['U'] = 20, ['V'] = 21, ['W'] = 22, ['X'] = 23,
    ['Y'] = 24, ['Z'] = 25, ['a'] = 26, ['b'] = 27, ['c'] = 28, ['d'] = 29, ['e'] = 30, ['f'] = 31,
    ['g'] = 32, ['h'] = 33, ['i'] = 34, ['j'] = 35, ['k'] = 36, ['l'] = 37, ['m'] = 38, ['n'] = 39,
    ['o'] = 40, ['p'] = 41, ['q'] = 42, ['r'] = 43, ['s'] = 44, ['t'] = 45, ['u'] = 46, ['v'] = 47,
    ['w'] = 48, ['x'] = 49, ['y'] = 50, ['z'] = 51, ['0'] = 52, ['1'] = 53, ['2'] = 54, ['3'] = 55,
    ['4'] = 56, ['5'] = 57, ['6'] = 58, ['7'] = 59, ['8'] = 60, ['9'] = 61, ['+'] = 62, ['-'] = 62,
    ['/'] = 63, ['_'] = 63, ['='] = -2 /* padding sentinel */
};
#endif

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
                // clang-format off
                
                //uint8_t octlet0 = src[0];
                //uint8_t octlet1 = src[1];
                //uint8_t octlet2 = src[2];
                
                /* ┍━━━╸octlet0╺━━━┯━━━╸octlet1╺━━━┯━━━╸octlet2╺━━━┑
                   ┊7 6 5 4 3 2 1 0┊7 6 5 4 3 2 1 0┊7 6 5 4 3 2 1 0┊
                   ┝━━━━━━━━━━━┯━━━┷━━━━━━━┯━━━━━━━┷━━━┯━━━━━━━━━━━┥
                   ┊5 4 3 2 1 0┊5 4 3 2 1 0┊5 4 3 2 1 0┊5 4 3 2 1 0┊
                   ┕━━━━╸0╺━━━━┷━━━━╸1╺━━━━┷━━━━╸2╺━━━━┷━━━━╸3╺━━━━┙ */

                *dst++ = alpha[(src[0] >> 2) & 0x3F];
                if (!--dstlen) break;

                *dst++ = alpha[((src[0] << 4) & 0x30) + (--srclen ? (src[1] >> 4) & 0x0F : 0)];
                if (!--dstlen) break;

                *dst++ = (srclen ? alpha[((src[1] << 2) & 0x3C) + (--srclen ? (src[2] >> 6) & 0x03 : 0)] 
                                 : '=');
                if (!--dstlen) break;

                *dst++ = srclen ? alpha[src[2] & 0x3F] 
                                : '=';
                if (!--dstlen) break;

                if (srclen && --srclen) src += 3;
                // clang-format on
            }
            if (dstlen) *dst = '\0';
        }
    }
}

void b64_encode(char* dst, size_t dstlen, const uint8_t* src, size_t srclen)
{
    b64_internal_encode(dst, dstlen, src, srclen, B64_ALPHA);
}
#if 0
void b64url_encode(char* dst, size_t dstlen, const uint8_t* src, size_t srclen)
{
    b64_internal_encode(dst, dstlen, src, srclen, B64URL_ALPHA);
}
void b64_encode_fd(char* dst, size_t dstlen, int fd, size_t srclen)
{
    uint8_t buf[B64_FD_READ_BUFSIZE];
    while (srclen && dstlen)
    {
        size_t nwant = B64_FD_READ_BUFSIZE < srclen ? B64_FD_READ_BUFSIZE : srclen;
        size_t nread = 0;
        while (nread != nwant)
        {
            ssize_t n = read(fd, buf + nread, nwant - nread);
            if (0 > n) return;
            nread += (size_t)n;
        }

        size_t enclen = B64_ENCODE_SIZE(nread);
        b64_encode(dst, enclen, buf, nread);

        srclen -= nread;
        dstlen -= enclen;
        dst += enclen;
    }
}
size_t b64_decode(uint8_t* dst, const char* src, size_t len)
{
    size_t out_len = len;
    if (dst && src && len % 4 != 0)
    {
        uint8_t* p = dst;

        for (size_t i = 0; i < len; i += 4)
        {
            int8_t c0 = B64_DEC[(uint8_t)src[i]];
            int8_t c1 = B64_DEC[(uint8_t)src[i + 1]];
            int8_t c2 = B64_DEC[(uint8_t)src[i + 2]];
            int8_t c3 = B64_DEC[(uint8_t)src[i + 3]];

            if (c0 < 0 || c1 < 0)
            {
                p = NULL;
                break;
            }

            *p++ = (uint8_t)((c0 << 2) | (c1 >> 4));

            if (c2 == -2) break;
            *p++ = (uint8_t)((c1 << 4) | (c2 >> 2));

            if (c3 == -2) break;
            *p++ = (uint8_t)((c2 << 6) | c3);
        }

        if (p)
        {
            out_len = (size_t)(p - dst);
        }
    }
    else if (len % 4 != 0)
    {
        out_len = B64_DECODE_SIZE(len);
    }

    return out_len;
}
#endif