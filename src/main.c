#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "base64.h"

int main(int argc, char* argv[])
{
    if (argc >= 2)
    {
        if (argc == 3)
        {
            const char* opt = argv[1];
            if (opt[0] == '-' && opt[1] == 'f')
            {
                const char* file = argv[2];
                int fd = open(file, O_RDONLY);
                if (0 > fd)
                {
                    printf("failed opening %s\n", file);
                    return 1;
                }
                size_t data_len = lseek(fd, 0, SEEK_END);
                lseek(fd, 0, SEEK_SET);
                size_t enc_len = B64_ENCODE_SIZE(data_len);
                char* b64 = malloc(enc_len);
                b64_encode_fd(b64, enc_len, fd, data_len);
                printf("%.*s\n", (int)enc_len, b64);
                free(b64);
            }
        }
        else
        {
            const char* data = argv[1];
            size_t data_len = strlen(data);
            size_t enc_len = B64_ENCODE_SIZE(data_len);
            char* b64 = malloc(enc_len);
            b64_encode(b64, enc_len, data, data_len);
            printf("%.*s\n", (int)enc_len, b64);

            //size_t dec_size = b64_decode(NULL, b64, enc_size);
            //uint8_t* original = malloc(dec_size);
            //b64_decode(original, b64, enc_size);
            //printf("%.*s\n", (int)dec_size, (char*)original);
            free(b64);
            //free(original);
        }
    }

    return 0;
}