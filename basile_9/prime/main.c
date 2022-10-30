#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/bn.h>

int main(int argc, char const *argv[])
{
    BIGNUM *prime1 = BN_new();
    BIGNUM *prime2 = BN_new();

    int rc = RAND_load_file("/dev/random", 32);
    if (rc != 32)
    {
        ERR_print_errors(stderr);
        exit(-1);
    }

    if (!BN_generate_prime_ex(prime1, 16, 0, NULL, NULL, NULL))
    {
        ERR_print_errors(stderr);
        exit(-2);
    }

    if (!BN_generate_prime_ex(prime2, 16, 0, NULL, NULL, NULL))
    {
        ERR_print_errors(stderr);
        exit(-3);
    }

    printf("p1 = %s\n", BN_bn2dec(prime1));
    printf("p2 = %s\n", BN_bn2dec(prime2));

    if (BN_is_prime_ex(prime1, 8, NULL, NULL))
        printf("yey it's a freaking prime wow!!!\n");
    else
        printf("no way kinda a plain number mate won't lie...\n");

    BIGNUM *composite = BN_new();
    BN_set_word(composite, 32);

    if (BN_is_prime_ex(composite, 8, NULL, NULL))
        printf("yey it's a freaking prime wow!!!\n");
    else
        printf("no way kinda a plain number mate won't lie...\n");

    BIGNUM *rand_num = BN_new();
    BN_rand(rand_num, 1024, 0, 1);
    printf("rand = %s\n", BN_bn2dec(rand_num));

    if (BN_is_prime_ex(rand_num, 8, NULL, NULL))
        printf("yey it's a freaking prime wow!!!\n");
    else
        printf("no way kinda a plain number mate won't lie...\n");

    BN_free(prime1);
    BN_free(prime2);
    BN_free(composite);
    BN_free(rand_num);

    return 0;
}
