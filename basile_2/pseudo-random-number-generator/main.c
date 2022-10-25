#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>

#define MAX_BUF 2048

/**
 * Pseudo-Random Number Generator (PRNG)
 */
int main(int argc, char const *argv[])
{
    int n, i;
    unsigned char random_string[MAX_BUF];

    if (argc < 2)
    {
        fprintf(stderr, "Missing parameters. Usage: %s nbytes\n", argv[0]);
        exit(1);
    }

    sscanf(argv[1], "%d", &n);

    int rc = RAND_load_file("/dev/random", 32);
    if (rc != 32)
    {
        fprintf(stderr, "Error with usage of RAND_load_file.\n");
        exit(1);
    }

    RAND_bytes(random_string, n);

    printf("Sequence generated: ");
    for (i = 0; i < n; i++)
        printf("%02x", random_string[i]);
    printf("\n");
    
    return 0;
}
