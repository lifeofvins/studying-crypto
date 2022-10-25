#include <stdio.h>
#include </usr/include/openssl/evp.h>
#include </usr/include/stdlib.h>
#include <string.h>

#define ENC 1
#define DEC 0

#define BUFFER_SIZE 1024

int main(int argc, char const *argv[])
{
    unsigned char ibuf[BUFFER_SIZE], obuf[BUFFER_SIZE], decrypted[BUFFER_SIZE];
    int key_size, ilen, olen, tlen;
    int i;

    // key
    unsigned char *key = (unsigned char *)"0123456789012345";
    // iv
    unsigned char *iv = (unsigned char *)"aaaaaaaaaaaaaaaaa";

    // print the key and the
    // initialization vector
    // as hexadecimal values.
    printf("key: ");
    for (i = 0; i < 16; i++)
        printf("%02x", key[i]);
    printf("\n");
    printf("iv: ");
    for (i = 0; i < 16; i++)
        printf("%02x", iv[i]);
    printf("\n");

    // key generation
    key_size = EVP_CIPHER_key_length(EVP_aes_128_cbc());
    printf("key_size = %d\n", key_size);

    // Creation of the object for the context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init(ctx);
    EVP_CipherInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv, ENC);

    unsigned char *message = (unsigned char *)"this is the message";
    printf("plain message: ");
    for (i = 0; i < 16; i++)
        printf("%02x", obuf[i]);
    printf("\n");

    // Excecution of the algorithm
    int tot = 0;
    EVP_CipherUpdate(ctx, obuf, &olen, message, strlen(message));
    tot += olen;

    // Finalization of the process
    EVP_CipherFinal_ex(ctx, obuf + tot, &tlen);
    tot += tlen;

    // destruction of the objext
    EVP_CIPHER_CTX_free(ctx);

    tot = 0;
    ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_init(ctx);
    EVP_CipherInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv, DEC);
    EVP_CipherUpdate(ctx, decrypted, &olen, obuf, strlen(obuf));
    tot += olen;
    EVP_CipherFinal_ex(ctx, decrypted + tot, &tlen);
    tot += tlen;

    printf("encrypted message: ");
    printf("%s", decrypted);
    printf("\n");

    return 0;
}
