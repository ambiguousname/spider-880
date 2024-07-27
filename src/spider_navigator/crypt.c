#include <openssl/evp.h>
#include <openssl/kdf.h>
#include <openssl/err.h>
#include <openssl/provider.h>
#include <stdio.h>
#include <string.h>

#define ERROR(e) fprintf(stderr, e); ERR_print_errors_fp(stderr);



// Each password *should* be unique when we generate, so I'm not gonna bother with a salt or anything like that.
int derive_key_scrypt(unsigned char password[], unsigned char* key, size_t key_len, unsigned char* iv, size_t iv_len) {
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

int free_ctx(EVP_CIPHER_CTX* ctx) {
	EVP_CIPHER_CTX_free(ctx);
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
		free_ctx(*ctx);
		return -1;
	}

	int result = EVP_CipherInit_ex2(*ctx, cipher, NULL, NULL, 0, NULL);
	EVP_CIPHER_free(cipher);
	if (result <= 0) {
		ERROR("Could not set cipher to Cipher context.\n");
		free_ctx(*ctx);
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
		ERROR("Could not cipher to Cipher context.\n");
		free_ctx(*ctx);
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
		ERROR("Could not cipher to Cipher context.\n");
		free_ctx(*ctx);
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
		free_ctx(ctx);
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
			free_ctx(ctx);
			return -1;
		}
		fwrite(outbuf, 1, outlen, out);
	}
	int final_result = EVP_CipherFinal_ex(ctx, outbuf, &outlen);
	if (final_result <= 0) {
		ERROR("Could not crypt last bytes of infile.\n");
		free_ctx(ctx);
		return -1;
	}
	fwrite(outbuf, 1, outlen, out);

	return 1;
}

int main() {
	OSSL_PROVIDER*  deflt;
	deflt = OSSL_PROVIDER_load(NULL, "default");

	if (deflt == NULL) {
		ERROR("Could not load default provider.");
		return -1;
	}

	OSSL_PROVIDER* legacy;
	legacy = OSSL_PROVIDER_load(NULL, "legacy");

	if (legacy == NULL) {
		ERROR("Could not load legacy provider.");
		OSSL_PROVIDER_unload(deflt);
		return -1;
	}

	EVP_CIPHER_CTX* ctx = NULL;
	if (start_des_cipher(&ctx) <= 0) {
		OSSL_PROVIDER_unload(legacy);
		OSSL_PROVIDER_unload(deflt);
		return -1;
	}

	FILE* in = fopen("tags.h", "rb");
	FILE* out = fopen("tags.crypt.txt", "wb");

	unsigned char key[8], iv[8];
	
	derive_key_scrypt("TEST", key, 8, iv, 8);


	crypt_file(1, key, iv, in, out, ctx);
	
	fclose(in);
	fclose(out);

	FILE* i = fopen("tags.crypt.txt", "rb");
	FILE* o = fopen("tags.decrypt.txt", "wb");

	if (crypt_file(0, key, iv, in, out, ctx) > 0) {
		free_ctx(ctx);
	}

	fclose(i);
	fclose(o);

	OSSL_PROVIDER_unload(legacy);
	OSSL_PROVIDER_unload(deflt);

	return 0;
}