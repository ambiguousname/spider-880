#include <openssl/evp.h>
#include <openssl/kdf.h>
#include <openssl/err.h>
#include <stdio.h>

#define ERROR(e) fprintf(stderr, e); ERR_print_errors_fp(stderr);

int free_ctx(EVP_CIPHER_CTX* ctx) {
	EVP_CIPHER_CTX_free(ctx);
}
// TODO: It'd be nice to get some legacy encryption. I think for some sense of story as to when these files were encrypted.
// RC2 for cipher would be cool. 
// There is no 80s key derivation function that OpenSSL supports. I'm thinking a custom, super wonky setup using MD2. The more security flaws, the better.
// Maybe the algorithm could just be hashing the name of the website.

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
	if (result <= 0) {
		ERROR("Could not set cipher to Cipher context.\n");
		EVP_CIPHER_free(cipher);
		free_ctx(*ctx);
		return -1;
	}
	OPENSSL_assert(EVP_CIPHER_CTX_get_key_length(*ctx) == 32);
	OPENSSL_assert(EVP_CIPHER_CTX_get_iv_length(*ctx) == 16);

	return 1;
}

// Adapted from https://docs.openssl.org/master/man3/EVP_EncryptInit/#examples
int crypt_file(int do_crypt, unsigned char key[32], unsigned char iv[16], FILE* in, FILE* out, EVP_CIPHER_CTX* ctx) {
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

// Each password *should* be unique when we generate, so I'm not gonna bother with a salt or anything like that.
int derive_key_pbkdf2(const char* password, unsigned char* key[32]) {
	EVP_KDF* kdf = EVP_KDF_fetch(NULL, "ARGON2", NULL);
	if (kdf == NULL) {
		ERROR("Could not find given algorithm.");
		return -1;
	}

	EVP_KDF_CTX* ctx = EVP_KDF_CTX_new(kdf);
	EVP_KDF_free(kdf);
	if (ctx == NULL) {
		ERROR("Could not generate EVP PKEY ctx.");
		return -1;
	}

	OSSL_PARAM params[5];

	params[0] = OSSL_PARAM_construct_octet_string("pass", )
}

int main() {
	EVP_CIPHER_CTX* ctx = NULL;
	if (start_aes_cipher(&ctx) <= 0) {
		return -1;
	}

	FILE* in = fopen("tags.h", "rb");
	FILE* out = fopen("tags.crypt.txt", "wb");

	unsigned char key[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
	0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x20, 0x21,
	0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x30, 0x31}; 

	unsigned char iv[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
	0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15};


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

	return 0;
}