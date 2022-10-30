#include <stdio.h>
#include <openssl/bn.h>

int main(int argc, char const *argv[])
{
    BIGNUM *b1 = BN_new();
    BIGNUM *b2 = BN_new();
    BIGNUM *b3 = BN_new();
    BN_CTX *ctx = BN_CTX_new();
    char *string_bn;

    BN_set_word(b1, 8);
    BN_set_word(b2, 5);
    BN_set_word(b3, 616);

    BN_print_fp(stdout, b1);
    printf("\n");
    BN_print_fp(stdout, b2);
    printf("\n");
    BN_print_fp(stdout, b3);
    printf("\n");

    BN_mod(b3, b1, b2, ctx);
    
    string_bn = BN_bn2dec(b3);
    printf("mod = %s\n", string_bn);

    BN_free(b1);
    BN_free(b2);
    BN_free(b3);

    BN_CTX_free(ctx);

    return 0;
}
