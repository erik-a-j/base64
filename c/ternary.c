#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#define USEDp(p) asm volatile("" : : "r,m"(p) : "memory")
#define USEDv(v) asm volatile("" : "+r"(v))

int get_error_2nd_param(void)
    __attribute__((error("param i has to be a constant value in range 0-3")));

#define get1(blk, i)                                                                           \
    __builtin_choose_expr(                                                                     \
        __builtin_constant_p(i),                                                               \
        (__builtin_choose_expr(                                                                \
            i == 0, (blk)[0] >> 2,                                                             \
            __builtin_choose_expr(                                                             \
                i == 1, (((blk)[0] & 0x03) << 4) | ((blk)[1] >> 4),                            \
                __builtin_choose_expr(                                                         \
                    i == 2, (((blk)[1] & 0x0F) << 2) | ((blk)[2] >> 6),                        \
                    __builtin_choose_expr(i == 3, (blk)[2] & 0x3F, get_error_2nd_param()))))), \
        get_error_2nd_param())

#define get(blk, i)                                                                      \
    (({_Static_assert(i >= 0 && i <= 3, "i has to be a constant value in range 0-3");}), \
     (i == 0 ? (blk)[0] >> 2                                                             \
   : (i == 1 ? (((blk)[0] & 0x03) << 4) | ((blk)[1] >> 4)                                \
   : (i == 2 ? (((blk)[1] & 0x0F) << 2) | ((blk)[2] >> 6)                                \
             : (blk)[2] & 0x3F))))

static __attribute__((noinline)) void work(int* dst, const uint8_t* src, size_t len)
{
    int* p = dst;
    for (size_t i = 0; i + 3 <= len; i += 3)
    {
        *p++ = get(src + i, 0);
        *p++ = get(src + i, 1);
        *p++ = get(src + i, 2);
        *p++ = get(src + i, 3);
    }
}

int main(void)
{
    uint8_t data[3] = {0x10, 0x20, 0x30};
    int res[4 * ((sizeof(data) + 2) / 3)] = {0};
    size_t size = sizeof(data);
    USEDp(data);
    USEDp(res);
    USEDv(size);
    work(res, data, size);
    return 0;
}