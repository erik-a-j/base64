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

        printf("%s\n", b64);
        size_t dec_size = b64_decode(NULL, b64, enc_size);
        uint8_t* original = malloc(dec_size);
        b64_decode(original, b64, enc_size);
        printf("%.*s\n", (int)dec_size, (char*)original);
        free(b64);
        free(original);
    }
    return 0;
}