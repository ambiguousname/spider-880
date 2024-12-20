#pragma once
#include <openssl/types.h>
#include <stddef.h>

OSSL_LIB_CTX* lib_ctx_local_providers(const char* folder);
void free_lib_ctx(OSSL_LIB_CTX* ctx);

int load_legacy_provider();
void unload_legacy_provider();
int  load_default_provider();
void unload_default_provider();

int load_provider(const char* name, OSSL_PROVIDER** pvdr);
int load_provider_with_ctx(const char* name, OSSL_PROVIDER** pvdr, OSSL_LIB_CTX* ctx);
void unload_provider(OSSL_PROVIDER* pvdr);

int start_cipher(const char* ciphername);
int crypt_file_existing_cipher(int do_crypt, unsigned char key[], unsigned char iv[], const char* inpath, const char* outpath);
void end_cipher();

int start_aes_cipher(EVP_CIPHER_CTX** ctx);
int start_rc2_cipher(EVP_CIPHER_CTX** ctx);
int start_des_cipher(OSSL_LIB_CTX* libctx, EVP_CIPHER_CTX** ctx);
void free_cipher(EVP_CIPHER_CTX* ctx);

int derive_key_scrypt(const char password[], unsigned char key[], size_t key_len, unsigned char iv[], size_t iv_len);
int derive_key_md4(OSSL_LIB_CTX* libctx, const char password[], unsigned char key[16]);
int crypt_file(int do_crypt, unsigned char key[], unsigned char iv[], const char* inpath, const char* outpath, EVP_CIPHER_CTX* ctx);