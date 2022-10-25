#include <stdio.h>
#include <stdlib.h>
#include <openssl/crypto.h>
#include <openssl/evp.h>

#define BUF_SIZE 1024

int main(int argc, char const *argv[])
{
    unsigned char md_value[EVP_MAX_MD_SIZE];
    int n, i, md_len;
    unsigned char buf[BUF_SIZE];
    FILE *fin;

    if ((fin = fopen(argv[1], "r")) == NULL)
        return -1;

    EVP_MD_CTX *md;
    md = EVP_MD_CTX_new();
    EVP_DigestInit_ex(md, EVP_sha1(), NULL);
    while ((n = fread(buf, 1, BUF_SIZE, fin)) > 0)
        EVP_DigestUpdate(md, buf, n);

    EVP_DigestFinal_ex(md, md_value, &md_len);

    EVP_MD_free(md);

    for (i = 0; i < md_len; i++)
        printf("%02x", md_value[i]);
    printf("\n");

    return 0;
}
