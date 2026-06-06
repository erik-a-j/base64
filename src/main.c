#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        size_t enc_size = b64_encode(NULL, argv[1], strlen(argv[1]));
        char* b64 = malloc(enc_size);
        b64_encode(b64, argv[1], strlen(argv[1]));
        //B64_ENCODE_SIZE(strlen(argv[1]));

        printf("%s\n", b64);
        size_t len;
        uint8_t* original = malloc(B64_DECODE_SIZE(enc_size));
        b64_decode(b64, &len, original);
        printf("%.*s\n", (int)len, (char*)original);
        free(b64);
        free(original);
    }
    return 0;
}