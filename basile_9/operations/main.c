#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/bn.h>

int main(int argc, char const *argv[])
{
    BIGNUM *a = BN_new();
    BIGNUM *b = BN_new();
    BIGNUM *res = BN_new();
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *div = BN_new();
    BIGNUM *rem = BN_new();
    BIGNUM *exp = BN_new();
    BIGNUM *modulus = BN_new();

    BN_set_word(a, 200);
    BN_set_word(b, 51);

    BN_add(res, a, b);
    printf("sum = %s\n", BN_bn2dec(res));

    BN_div(div, rem, a, b, ctx);
    printf("div = %s\n", BN_bn2dec(div));
    printf("rem = %s\n", BN_bn2dec(rem));

    BN_set_word(modulus, 14);
    BN_mod_exp(exp, a, b, modulus, ctx);
    printf("exp = %s\n", BN_bn2dec(exp));

    BN_free(a);
    BN_free(b);
    BN_free(exp);
    BN_free(modulus);
    BN_free(div);
    BN_free(rem);
    BN_free(res);
    BN_CTX_free(ctx);

    return 0;
}
