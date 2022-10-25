#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>

int main(int argc, char const *argv[])
{
    unsigned char key[EVP_MAX_KEY_LENGTH];
    FILE *key_file;
    int key_size;

    if (argc < 3)
    {
        fprintf(stderr, "Missing parameters. Usage: %s alg outfile \n", argv[0]);
        exit(1);
    }

    int rc = RAND_load_file("/dev/random", 32);
    if (rc != 32)
    {
        fprintf(stderr, "Error with usage of RAND_load_file.\n");
        exit(-1);
    }

    if ((key_file = fopen(argv[2], "w")) == NULL)
    {
        fprintf(stderr, "Error with memory.\n");
        exit(-2);
    }

    const EVP_CIPHER *algo;
    algo = EVP_get_cipherbyname(argv[1]);
    key_size = EVP_CIPHER_key_length(algo);
    printf("key_size = %d\n", key_size);

    RAND_load_file("/dev/random", 32);
    RAND_bytes(key, key_size);

    if(fwrite(key, 1, key_size, key_file) != key_size) {
        printf("err\n");
        exit(-3);
    }

    fclose(key_file);

    return 0;
}
