#include <stdio.h>
#include <stdlib.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

int main(int argc, char const *argv[])
{
    int ret = 0;
    RSA *rsa_keypair = NULL;
    BIGNUM *bne = BN_new();
    int bits = 2048;
    unsigned long e = RSA_F4;

    BN_set_word(bne, e);
    rsa_keypair = RSA_new();

    ret = RSA_generate_key_ex(rsa_keypair, bits, bne, NULL);

    if (ret != 1)
    {
        ERR_print_errors_fp(stderr);
        exit(-1);
    }

    BIO *bio_public;
    bio_public = BIO_new_file("public.pem", "w+");
    PEM_write_bio_RSAPublicKey(bio_public, rsa_keypair);

    BIO *bio_private;
    bio_private = BIO_new_file("private.pem", "w+");
    PEM_write_bio_RSAPrivateKey(bio_private, rsa_keypair, NULL, NULL, 0, NULL, NULL);

    RSA_free(rsa_keypair);
    BN_free(bne);
    BIO_free_all(bio_private);
    BIO_free_all(bio_public);

    return 0;
}
