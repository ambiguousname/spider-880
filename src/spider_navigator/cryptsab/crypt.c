#include "crypt.h"

#include <openssl/evp.h>
#include <openssl/kdf.h>
#include <openssl/err.h>
#include <openssl/provider.h>
#include <string.h>

#define ERROR(e) fprintf(stderr, e); ERR_print_errors_fp(stderr);

// Each password *should* be unique when we generate, so I'm not gonna bother with a salt or anything like that.

/// @brief Derive a key using script. Equivalent on cmd is `openssl kdf -keylen LENGTH_HERE -kdfopt pass:PASSWORD -kdfopt n:1024 -kdfopt r:8 -kdfopt:16 scrypt`, of which the first X bytes should go to the key, and the remaining should go to the IV.
/// @param password Password to derive a key from.
/// @param key Output of the key.
/// @param key_len How long the key is.
/// @param iv Output for iv.
/// @param iv_len Length of the IV.
/// @return Success. < 0 for failure, 1 for success.
int derive_key_scrypt(char password[], unsigned char key[], size_t key_len, unsigned char iv[], size_t iv_len) {
	EVP_KDF* kdf = EVP_KDF_fetch(NULL, "SCRYPT", NULL);
	if (kdf == NULL) {
		ERROR("Could not find scrypt KDF.\n");
		return -1;
	}

	EVP_KDF_CTX* ctx = EVP_KDF_CTX_new(kdf);
	EVP_KDF_free(kdf);
	if (ctx == NULL) {
		ERROR("Could not generate EVP PKEY ctx.\n");
		return -1;
	}

	OSSL_PARAM params[6];

	uint64_t n = 1024;
	uint32_t r = 8;
	uint32_t p = 16;

	params[0] = OSSL_PARAM_construct_octet_string("pass", password, strlen(password)); 
	params[1] = OSSL_PARAM_construct_octet_string("salt", "", 0);
	params[2] = OSSL_PARAM_construct_uint64("n", &n);
	params[3] = OSSL_PARAM_construct_uint32("r", &r);
	params[4] = OSSL_PARAM_construct_uint32("p", &p);
	params[5] = OSSL_PARAM_construct_end();

	unsigned char out[key_len + iv_len];
	int derive_result = EVP_KDF_derive(ctx, out, key_len + iv_len, params);

	EVP_KDF_CTX_free(ctx);
	
	if (derive_result <= 0) {
		ERROR("Scrypt could not derive.\n");
		return -1;
	}

	for (int i = 0; i < sizeof(out); i++) {
		if (i >= key_len) {
			iv[i] = out[i];
		} else {
			key[i] = out[i];
		}
	}
	
	return 1;
}

/// @brief Derive a key from a password using MD4 (would use MD2, but it's not built in with OpenSSL by default, BOOOO). Will only output 8 bit keys.
/// Is this secure? No. Don't use it. BuSab was just sort of doing their own thing in the 80s.
/// @param password The password.
/// @param key The key output.
/// @return 1 on success, any number < 0 on fail.
int derive_key_md4(char password[], unsigned char key[], size_t key_len, unsigned char iv[], size_t iv_len) {
	EVP_MD_CTX* ctx = EVP_MD_CTX_new();

	if (ctx == NULL) {
		ERROR("Could not find MD ctx.\n");
		return -1;
	}

	EVP_MD* md = EVP_MD_fetch(NULL, "MD4", "provider=legacy");

	if (md == NULL) {
		ERROR("Could not get MD4.\n");
		EVP_MD_CTX_free(ctx);
		return -1;
	}

	OSSL_PARAM params[2];

	unsigned int len = key_len + iv_len;

	params[0] = OSSL_PARAM_construct_uint("size", &len);
	params[1] = OSSL_PARAM_construct_end();

	int init_result = EVP_DigestInit_ex2(ctx, md, params);
	EVP_MD_free(md);
	if (init_result <= 0) {
		ERROR("Could not initialize MD4.");
		EVP_MD_CTX_free(ctx);
		return -1;
	}

	int update = EVP_DigestUpdate(ctx, password, strlen(password));
	if (update <= 0) {
		ERROR("Could not update digest.");
		EVP_MD_CTX_free(ctx);
		return -1;
	}

	
	unsigned char out[len];

	unsigned int outlen;
	int final = EVP_DigestFinal(ctx, out, &outlen);
	EVP_MD_CTX_free(ctx);
	if (final <= 0) {
		ERROR("Could not process final digest.");
		return -1;
	}
	OPENSSL_assert(outlen == len);

	for (int i = 0; i < outlen; i++) {
		if (i >= key_len) {
			iv[i] = out[i];
		} else {
			key[i] = out[i];
		}
	}
	
	return 1;
}

int start_aes_cipher(EVP_CIPHER_CTX** ctx) {
	*ctx = NULL;
	*ctx = EVP_CIPHER_CTX_new();
	if (*ctx == NULL) {
		ERROR("Could not create OpenSSL EVP Cipher Context.\n");
		return -1;
	}

	// TODO: Might be fun to load RC2 with the legacy provider.
	EVP_CIPHER* cipher = NULL;
	cipher = EVP_CIPHER_fetch(NULL, "AES-256-CBC", NULL);
	if (cipher == NULL) {
		ERROR("Could not fetch AES-256-CBC Cipher.\n");
		EVP_CIPHER_CTX_free(*ctx);
		return -1;
	}

	int result = EVP_CipherInit_ex2(*ctx, cipher, NULL, NULL, 0, NULL);
	EVP_CIPHER_free(cipher);
	if (result <= 0) {
		ERROR("Could not add cipher to Cipher context.\n");
		EVP_CIPHER_CTX_free(*ctx);
		return -1;
	}
	OPENSSL_assert(EVP_CIPHER_CTX_get_key_length(*ctx) == 32);
	OPENSSL_assert(EVP_CIPHER_CTX_get_iv_length(*ctx) == 16);

	return 1;
}

int start_rc2_cipher(EVP_CIPHER_CTX** ctx) {
	*ctx = NULL;
	*ctx = EVP_CIPHER_CTX_new();

	if (ctx == NULL) {
		ERROR("Could not create Cipher Context.\n");
		return -1;
	}

	EVP_CIPHER* cipher = NULL;
	cipher = EVP_CIPHER_fetch(NULL, "RC2", "provider=legacy");
	if (cipher == NULL) {
		ERROR("Could not fetch RC2 cipher.\n");
		return -1;
	}

	int result = EVP_CipherInit_ex2(*ctx, cipher, NULL, NULL, 0, NULL);
	EVP_CIPHER_free(cipher);
	if (result <= 0) {
		ERROR("Could not add cipher to Cipher context.\n");
		EVP_CIPHER_CTX_free(*ctx);
	}
	OPENSSL_assert(EVP_CIPHER_CTX_get_key_length(*ctx) == 16);
	OPENSSL_assert(EVP_CIPHER_CTX_get_iv_length(*ctx) == 16);
	
	return 1;
}

int start_des_cipher(EVP_CIPHER_CTX** ctx) {
	*ctx = NULL;
	*ctx = EVP_CIPHER_CTX_new();

	if (ctx == NULL) {
		ERROR("Could not create Cipher Context.\n");
		return -1;
	}

	EVP_CIPHER* cipher = NULL;
	cipher = EVP_CIPHER_fetch(NULL, "DES-CBC", "provider=legacy");
	if (cipher == NULL) {
		ERROR("Could not fetch DES-CBC cipher.\n");
		return -1;
	}

	int result = EVP_CipherInit_ex2(*ctx, cipher, NULL, NULL, 0, NULL);
	EVP_CIPHER_free(cipher);
	if (result <= 0) {
		ERROR("Could not add cipher to Cipher context.\n");
		EVP_CIPHER_CTX_free(*ctx);
	}
	OPENSSL_assert(EVP_CIPHER_CTX_get_key_length(*ctx) == 8);
	OPENSSL_assert(EVP_CIPHER_CTX_get_iv_length(*ctx) == 8);
	
	return 1;
}

// Adapted from https://docs.openssl.org/master/man3/EVP_EncryptInit/#examples
int crypt_file(int do_crypt, unsigned char key[], unsigned char iv[], FILE* in, FILE* out, EVP_CIPHER_CTX* ctx) {
	int result = EVP_CipherInit_ex2(ctx, NULL, key, iv, do_crypt, NULL);
	if (result <= 0) {
		ERROR("Could not set encryption/decryption mode to Cipher context.\n");
		EVP_CIPHER_CTX_free(ctx);
		return -1;
	}
	
	unsigned char inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
	int inlen, outlen;
	for (;;) {
		inlen = fread(inbuf, 1, 1024, in);
		if (inlen <= 0) {
			break;
		}

		int update_result = EVP_CipherUpdate(ctx, outbuf, &outlen, inbuf, inlen);
		if (update_result <= 0) {
			ERROR("Could not crypt infile.\n");
			EVP_CIPHER_CTX_free(ctx);
			return -1;
		}
		fwrite(outbuf, 1, outlen, out);
	}
	int final_result = EVP_CipherFinal_ex(ctx, outbuf, &outlen);
	if (final_result <= 0) {
		ERROR("Could not crypt last bytes of infile.\n");
		EVP_CIPHER_CTX_free(ctx);
		return -1;
	}
	fwrite(outbuf, 1, outlen, out);

	return 1;
}