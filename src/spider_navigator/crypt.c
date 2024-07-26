#include <openssl/evp.h>
#include <openssl/err.h>
#include <stdio.h>

#define ERROR(e) fprintf(stderr, e); ERR_print_errors_fp(stderr);

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
	if (result <= 0) {
		ERROR("Could not set cipher to Cipher context.\n");
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
		return -1;
	}
	
	unsigned char inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH] = "";
	int inlen, outlen;
	for (;;) {
		inlen = fread(inbuf, 1, 1024, in);
		if (feof(in) != 0) {
			break;
		} else if (ferror(in) != 0) {
			return -1;
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
	EVP_CIPHER_CTX* ctx = NULL;
	if (start_aes_cipher(&ctx) <= 0) {
		return -1;
	}

	FILE* in = fopen("tags.h", "r");
	FILE* out = fopen("tags.crypt.txt", "w");

	crypt_file(1, "0123456789abcdeF0123456789abcdeF", "1234567887654321", in, out, ctx);
	
	fclose(in);
	fclose(out);

	FILE* i = fopen("tags.crypt.txt", "r");
	FILE* o = fopen("tags.decrypt.txt", "w");

	if (crypt_file(0, "0123456789abcdeF0123456789abcdeF", "1234567887654321", in, out, ctx) > 0) {
		free_ctx(ctx);
	}

	fclose(i);
	fclose(o);

	return 0;
}