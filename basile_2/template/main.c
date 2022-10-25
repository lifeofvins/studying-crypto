#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#define MAX_BUF 2048

void handleError(void);

int main(int argc, char const *argv[])
{
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);

    

    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
    ERR_free_strings();
    return 0;
}

void handleError() {
    ERR_print_errors_fp(stderr);
    abort();
}
