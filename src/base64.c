
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

typedef enum {
    B64_ENC0,
    B64_ENC1,
    B64_ENC2,
    B64_ENC3,
} b64_enc_block_idx_t;

static const char* B64_ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char* B64URL_ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
static const int8_t B64_DEC[256] = {
    ['A'] = 0,  ['B'] = 1,  ['C'] = 2,  ['D'] = 3,  ['E'] = 4,  ['F'] = 5,  ['G'] = 6,  ['H'] = 7,  ['I'] = 8,
    ['J'] = 9,  ['K'] = 10, ['L'] = 11, ['M'] = 12, ['N'] = 13, ['O'] = 14, ['P'] = 15, ['Q'] = 16, ['R'] = 17,
    ['S'] = 18, ['T'] = 19, ['U'] = 20, ['V'] = 21, ['W'] = 22, ['X'] = 23, ['Y'] = 24, ['Z'] = 25, ['a'] = 26,
    ['b'] = 27, ['c'] = 28, ['d'] = 29, ['e'] = 30, ['f'] = 31, ['g'] = 32, ['h'] = 33, ['i'] = 34, ['j'] = 35,
    ['k'] = 36, ['l'] = 37, ['m'] = 38, ['n'] = 39, ['o'] = 40, ['p'] = 41, ['q'] = 42, ['r'] = 43, ['s'] = 44,
    ['t'] = 45, ['u'] = 46, ['v'] = 47, ['w'] = 48, ['x'] = 49, ['y'] = 50, ['z'] = 51, ['0'] = 52, ['1'] = 53,
    ['2'] = 54, ['3'] = 55, ['4'] = 56, ['5'] = 57, ['6'] = 58, ['7'] = 59, ['8'] = 60, ['9'] = 61, ['+'] = 62,
    ['-'] = 62, ['/'] = 63, ['_'] = 63, ['='] = -2 /* padding sentinel */
};

static inline int b64_alpha_index(const uint8_t* blk, b64_enc_block_idx_t i)
{
    return (i == B64_ENC0 ? blk[0] >> 2
                          : (i == B64_ENC1 ? ((blk[0] & 0x03) << 4) | (blk[1] >> 4)
                                           : (i == B64_ENC2 ? ((blk[1] & 0x0F) << 2) | (blk[2] >> 6)
                                                            : /*i == B64_ENC3*/ blk[2] & 0x3F)));
}

static inline size_t b64_internal_encode(char* dst, const uint8_t* src, size_t len, const char* alpha)
{
    if (dst && src)
    {
        char* p = dst;
        size_t i = 0;

        for (; i + 3 <= len; i += 3)
        {
            *p++ = alpha[b64_alpha_index(src + i, B64_ENC0)];
            *p++ = alpha[b64_alpha_index(src + i, B64_ENC1)];
            *p++ = alpha[b64_alpha_index(src + i, B64_ENC2)];
            *p++ = alpha[b64_alpha_index(src + i, B64_ENC3)];
            //*p++ = alpha[src[i] >> 2];
            //*p++ = alpha[((src[i] & 0x03) << 4) | (src[i + 1] >> 4)];
            //*p++ = alpha[((src[i + 1] & 0x0F) << 2) | (src[i + 2] >> 6)];
            //*p++ = alpha[src[i + 2] & 0x3F];
        }

        size_t rem = len - i;
        if (rem == 1)
        {
            *p++ = alpha[src[i] >> 2];
            *p++ = alpha[(src[i] & 0x03) << 4];
            *p++ = '=';
            *p++ = '=';
        }
        else if (rem == 2)
        {
            *p++ = alpha[src[i] >> 2];
            *p++ = alpha[((src[i] & 0x03) << 4) | (src[i + 1] >> 4)];
            *p++ = alpha[(src[i + 1] & 0x0F) << 2];
            *p++ = '=';
        }

        *p = '\0';
    }
    return B64_ENCODE_SIZE(len);
}

size_t b64_encode(char* dst, const uint8_t* src, size_t len)
{
    return b64_internal_encode(dst, src, len, B64_ALPHA);
}
size_t b64url_encode(char* dst, const uint8_t* src, size_t len)
{
    return b64_internal_encode(dst, src, len, B64URL_ALPHA);
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