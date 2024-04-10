/* Ling Jiang-D22128264
  * This file contains the implementation of the functions declared in the
  header file. They are used to encrypt and decrypt data using the AES
  encryption algorithm. sub functions include:sub bytes, shift rows, mix
  columns, expand key, add round key, inverse sub bytes, inverse shift rows,
  inverse mix columns.
 */

#include "rijndael.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//+++Encryption+++

//--- sub bytes---
static const unsigned char s_box[256] = {

    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B,
    0xFE, 0xD7, 0xAB, 0x76, 0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0,
    0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0, 0xB7, 0xFD, 0x93, 0x26,
    0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2,
    0xEB, 0x27, 0xB2, 0x75, 0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0,
    0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84, 0x53, 0xD1, 0x00, 0xED,
    0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F,
    0x50, 0x3C, 0x9F, 0xA8, 0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5,
    0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2, 0xCD, 0x0C, 0x13, 0xEC,
    0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14,
    0xDE, 0x5E, 0x0B, 0xDB, 0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C,
    0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79, 0xE7, 0xC8, 0x37, 0x6D,
    0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F,
    0x4B, 0xBD, 0x8B, 0x8A, 0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E,
    0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E, 0xE1, 0xF8, 0x98, 0x11,
    0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F,
    0xB0, 0x54, 0xBB, 0x16,
};

void sub_bytes(unsigned char *block) {
  for (int i = 0; i < 16; i++) {
    block[i] = s_box[block[i]];
  }
}

void shift_rows(unsigned char *block) {
  unsigned char temp;

  // Shift the second row left by 1
  temp = block[5];
  block[5] = block[9];
  block[9] = block[13];
  block[13] = block[1];
  block[1] = temp;

  // Shift the third row left by 2
  temp = block[2];
  block[2] = block[10];
  block[10] = temp;

  temp = block[6];
  block[6] = block[14];
  block[14] = temp;

  // Shift the fourth row left by 3 (or equivalently, right by 1)
  temp = block[15];
  block[15] = block[11];
  block[11] = block[7];
  block[7] = block[3];
  block[3] = temp;
}

// ---mix columns---

#define xtime(x) (((x) << 1) ^ ((((x) >> 7) & 1) * 0x1b))
#define multiply(x, y)                           \
  (((y) & 1) * (x) ^ ((y >> 1) & 1) * xtime(x) ^ \
   ((y >> 2) & 1) * xtime(xtime(x)) ^ ((y >> 3) & 1) * xtime(xtime(xtime(x))))

void mix_columns(unsigned char *block) {
  unsigned char temp[4];
  int i;

  for (i = 0; i < 4; ++i) {
    temp[0] = multiply(block[i * 4], 2) ^ multiply(block[i * 4 + 1], 3) ^
              block[i * 4 + 2] ^ block[i * 4 + 3];
    temp[1] = block[i * 4] ^ multiply(block[i * 4 + 1], 2) ^
              multiply(block[i * 4 + 2], 3) ^ block[i * 4 + 3];
    temp[2] = block[i * 4] ^ block[i * 4 + 1] ^ multiply(block[i * 4 + 2], 2) ^
              multiply(block[i * 4 + 3], 3);
    temp[3] = multiply(block[i * 4], 3) ^ block[i * 4 + 1] ^ block[i * 4 + 2] ^
              multiply(block[i * 4 + 3], 2);

    block[i * 4] = temp[0];
    block[i * 4 + 1] = temp[1];
    block[i * 4 + 2] = temp[2];
    block[i * 4 + 3] = temp[3];
  }
}

/*
 This function expand the round key. Given an input, which is a single 128-bit
key, it should return a 176-byte vector, containing the 11 round keys one after
the other
 */

//---expand key---
static const unsigned char r_con[] = {0x01, 0x02, 0x04, 0x08, 0x10,
                                      0x20, 0x40, 0x80, 0x1B, 0x36};

unsigned char *expand_key(unsigned char *cipher_key) {
  unsigned char *expanded_key = (unsigned char *)malloc(EXPANDED_KEY_SIZE);
  if (!expanded_key) {
    return NULL;
  }

  unsigned char temp[4];
  unsigned char temp2[4];
  int i = 0;
  int rconIndex = 0;

  // Copy the original key as the first 16 bytes of the expanded key
  for (i = 0; i < KEY_SIZE; i++) {
    expanded_key[i] = cipher_key[i];
  }

  // Generate the rest of the expanded key
  while (i < EXPANDED_KEY_SIZE) {
    // printf("This is the start %d\n", i); // debuggggg
    for (int j = 0; j < 4; j++) {
      temp[j] = expanded_key[(i - 4) + j];
      temp2[j] = expanded_key[(i - KEY_SIZE) + j];
    }

    if (i % KEY_SIZE == 0) {
      // Rotate the temp array
      //   printf("MOD 16");// debuggggg
      unsigned char t = temp[0];
      temp[0] = temp[1];
      temp[1] = temp[2];
      temp[2] = temp[3];
      temp[3] = t;

      // Substitute the bytes using the S-box
      for (int j = 0; j < 4; j++) {
        temp[j] = s_box[temp[j]];
      }

      // XOR the first byte with the Rcon value and move to the next Rcon value
      temp[0] ^= r_con[rconIndex];
      rconIndex++;

      for (int j = 0; j < 4; j++) {
        // XOR temp with the 16-byte block i bytes ago
        expanded_key[i] = temp[j] ^ temp2[j];
        i++;
      }
    } else {
      //   XOR temp with the 16-byte block i bytes ago
      for (int j = 0; j < 4; j++) {
        expanded_key[i] = temp[j] ^ temp2[j];
        i++;
      }
    }
  }

  return expanded_key;
}

//---add round key---
void add_round_key(unsigned char *block, unsigned char *round_key) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    block[i] ^= round_key[i];
  }
}

//+++decryption+++

//---inverse sub bytes---
static const unsigned char inv_s_box[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E,
    0x81, 0xF3, 0xD7, 0xFB, 0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87,
    0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB, 0x54, 0x7B, 0x94, 0x32,
    0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49,
    0x6D, 0x8B, 0xD1, 0x25, 0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16,
    0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92, 0x6C, 0x70, 0x48, 0x50,
    0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05,
    0xB8, 0xB3, 0x45, 0x06, 0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02,
    0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B, 0x3A, 0x91, 0x11, 0x41,
    0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8,
    0x1C, 0x75, 0xDF, 0x6E, 0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89,
    0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B, 0xFC, 0x56, 0x3E, 0x4B,
    0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59,
    0x27, 0x80, 0xEC, 0x5F, 0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D,
    0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF, 0xA0, 0xE0, 0x3B, 0x4D,
    0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63,
    0x55, 0x21, 0x0C, 0x7D,
};
void inverse_sub_bytes(unsigned char *block) {
  for (int i = 0; i < 16; i++) {
    block[i] = inv_s_box[block[i]];
  }
}

// ---inverse shift rows---
void inverse_shift_rows(unsigned char *block) {
  unsigned char temp;

  // Second row (shift right by 1)
  temp = block[1];
  block[1] = block[13];
  block[13] = block[9];
  block[9] = block[5];
  block[5] = temp;

  // Third row (shift right by 2)
  temp = block[2];
  block[2] = block[10];
  block[10] = temp;

  temp = block[6];
  block[6] = block[14];
  block[14] = temp;

  // Fourth row (shift right by 3)
  temp = block[3];
  block[3] = block[7];
  block[7] = block[11];
  block[11] = block[15];
  block[15] = temp;
}

// ---inverse mix columns---

#define xtime(x) (((x) << 1) ^ ((((x) >> 7) & 1) * 0x1b))
#define multiply(x, y)                           \
  (((y) & 1) * (x) ^ ((y >> 1) & 1) * xtime(x) ^ \
   ((y >> 2) & 1) * xtime(xtime(x)) ^ ((y >> 3) & 1) * xtime(xtime(xtime(x))))

// Function to perform Inverse MixColumns operation on a single column
void inverse_mix_column(unsigned char *column) {
  unsigned char temp[4];
  temp[0] = multiply(column[0], 0x0e) ^ multiply(column[1], 0x0b) ^
            multiply(column[2], 0x0d) ^ multiply(column[3], 0x09);
  temp[1] = multiply(column[0], 0x09) ^ multiply(column[1], 0x0e) ^
            multiply(column[2], 0x0b) ^ multiply(column[3], 0x0d);
  temp[2] = multiply(column[0], 0x0d) ^ multiply(column[1], 0x09) ^
            multiply(column[2], 0x0e) ^ multiply(column[3], 0x0b);
  temp[3] = multiply(column[0], 0x0b) ^ multiply(column[1], 0x0d) ^
            multiply(column[2], 0x09) ^ multiply(column[3], 0x0e);
  for (int i = 0; i < 4; i++) {
    column[i] = temp[i];
  }
}

// Function to perform Inverse MixColumns operation on the entire state matrix
void inverse_mix_columns(unsigned char *block) {
  for (int i = 0; i < 4; i++) {
    unsigned char column[4];
    for (int j = 0; j < 4; j++) {
      column[j] = block[i * 4 + j];  // Corrected indices here
    }
    inverse_mix_column(column);
    for (int j = 0; j < 4; j++) {
      block[i * 4 + j] = column[j];  // Corrected indices here
    }
  }
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++                  AES ENCRYPTION                      +++
// +++                                                      +++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
unsigned char *aes_encrypt_block(unsigned char *plaintext, unsigned char *key) {
  // step1: Expand the key
  unsigned char *expandedKey = expand_key(key);
  /* debuggggg
   for (int i = 0; i < EXPANDED_KEY_SIZE; ++i) {
     printf("%02x ", expandedKey[i]);
   } */
  printf("\n");
  if (!expandedKey) {
    printf("Failed to expand key.\n");
    return NULL;
  }

  // step2: Allocate memory for the output block (ciphertext)
  unsigned char *output =
      (unsigned char *)malloc(sizeof(unsigned char) * BLOCK_SIZE);
  if (!output) {
    free(expandedKey);  // Free the dynamically allocated expandedKey
    printf("Failed to allocate memory for output block.\n");
    return NULL;
  }

  // step3: Initial Round: AddRoundKey
  memcpy(output, plaintext, BLOCK_SIZE);
  add_round_key(output, expandedKey);
  // debugggg
  // printf("This is key: ");
  // for (int i = 0; i < BLOCK_SIZE; ++i) {
  //   printf("%02x ", expandedKey[i]);
  // }

  // step4: 9 Main Rounds
  for (int round = 1; round <= 9; ++round) {
    sub_bytes(output);
    shift_rows(output);
    mix_columns(output);
    add_round_key(
        output,
        expandedKey +
            (round *
             BLOCK_SIZE));  // Use the correct segment of the expanded key
  }

  // Final Round (without MixColumns)
  sub_bytes(output);
  shift_rows(output);
  add_round_key(output, expandedKey + 10 * BLOCK_SIZE);
  free(expandedKey);
  return output;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++                  AES DECRYPTION                      +++
// +++                                                      +++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

unsigned char *aes_decrypt_block(unsigned char *ciphertext,
                                 unsigned char *key) {
  // step1: Expand the key
  unsigned char *expandedKey = expand_key(key);
  // debuggggggggggggggg
  // for (int i = 0; i < EXPANDED_KEY_SIZE; ++i) {
  //   printf("%02x ", expandedKey[i]);
  // }
  printf("\n");
  if (!expandedKey) {
    printf("Failed to expand key.\n");
    return NULL;
  }
  // step2: Allocate memory for the output block (plaintext)
  unsigned char *output =
      (unsigned char *)malloc(sizeof(unsigned char) * BLOCK_SIZE);
  if (!output) {
    printf("Failed to allocate memory for output block.\n");
    return NULL;
  }
  // step3 add last round key
  memcpy(output, ciphertext, BLOCK_SIZE);
  add_round_key(output, expandedKey + 10 * BLOCK_SIZE);
  // debugggg
  // printf("This is last round key: ");
  // for (int i = 0; i < BLOCK_SIZE; ++i) {
  //   printf("%02x ", expandedKey[i]);
  // }

  // step4 inverse shift rows
  inverse_shift_rows(output);

  // step5 inverse sub bytes
  inverse_sub_bytes(output);

  //  step6 10 main rounds
  for (int round = 9; round >= 1; --round) {
    add_round_key(output, expandedKey + (round * BLOCK_SIZE));
    inverse_mix_columns(output);
    inverse_shift_rows(output);
    inverse_sub_bytes(output);
  }
  add_round_key(output,
                key);  // add the initial key

  // debuggggg
  // printf("This is the result after 10 main inverse rounds: ");
  // for (int i = 0; i < BLOCK_SIZE; ++i) {
  //   printf("%02x ", output[i]);
  // }

  return output;
}