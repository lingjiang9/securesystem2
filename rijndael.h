/*
 * TODO: Ling Jiang, D22128264
 *       a brief description of this code.
 */

#ifndef RIJNDAEL_H
#define RIJNDAEL_H

#define BLOCK_ACCESS(block, row, col) (block[(row * 4) + col])
#define BLOCK_SIZE 16
#define KEY_SIZE 16
#define EXPANDED_KEY_SIZE 176
#define AES_ROUNDS 10
void sub_bytes(unsigned char *block);
void invert_sub_bytes(unsigned char *block);
void shift_rows(unsigned char *block);
void mix_columns(unsigned char *block);
void invert_mix_columns(unsigned char *block);
void add_round_key(unsigned char *block, unsigned char *round_key);
void inverse_shift_rows(unsigned char *block);

/*
 * These should be the main encrypt/decrypt functions (i.e. the main
 * entry point to the library for programmes hoping to use it to
 * encrypt or decrypt data)
 */
unsigned char *aes_encrypt_block(unsigned char *plaintext, unsigned char *key);
unsigned char *aes_decrypt_block(unsigned char *ciphertext, unsigned char *key);
unsigned char *expand_key(unsigned char *cipher_key);

#endif
