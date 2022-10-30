#include <stdio.h>
#include <openssl/bn.h>

int main(int argc, char const *argv[])
{
    char num_string[] = "123156198651684168154981513741675146146751465147651476541675167514675";
    char *hex_string;
    BIGNUM *bn = BN_new();

    BN_dec2bn(&bn, num_string);
    BN_print_fp(stdout, bn);
    printf("\n");
    hex_string = BN_bn2hex(bn);
    printf("hex-string: %s\n", hex_string);

    BN_free(bn);

    /**
     * This has to be called when data has been
     * allocated into the heap by BN functions.
    */
    OPENSSL_free(hex_string);

    return 0;
}
