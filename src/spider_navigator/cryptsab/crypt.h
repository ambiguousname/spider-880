#pragma once
#include <stdio.h>
#include <openssl/types.h>

int derive_key_scrypt(char password[], unsigned char key[], size_t key_len, unsigned char iv[], size_t iv_len);
int derive_key_md4(char password[], unsigned char key[], size_t key_len, unsigned char iv[], size_t iv_len);
int start_aes_cipher(EVP_CIPHER_CTX** ctx);
int start_rc2_cipher(EVP_CIPHER_CTX** ctx);
int start_des_cipher(EVP_CIPHER_CTX** ctx);
int crypt_file(int do_crypt, unsigned char key[], unsigned char iv[], FILE* in, FILE* out, EVP_CIPHER_CTX* ctx);