/*This file(test.c) is used to test expected value of
every single function and major encryption and decryption functions during my
development. The test object is the file(rijndael.c). Tests taken from the NIST
document, Appendix B–Cipher Example- page 33,
http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rijndael.h"

void print_block(const unsigned char *block, int length) {
  for (int i = 0; i < length; i++) {
    printf("%02X ", block[i]);
  }
  printf("\n");
}

int main() {
  // +++Test Case 1: sub bytes+++
  unsigned char test_block1[16] = {25,  160, 154, 233, 61,  244, 198, 248,
                                   227, 226, 141, 72,  190, 43,  42,  8};
  unsigned char expected_output1[16] = {212, 224, 184, 30, 39,  191, 180, 65,
                                        17,  152, 93,  82, 174, 241, 229, 48};

  printf("Before sub_bytes:\n");
  print_block(test_block1, 16);

  sub_bytes(test_block1);

  printf("After sub_bytes:\n");
  print_block(test_block1, 16);

  printf("Expected output:\n");
  print_block(expected_output1, 16);

  if (memcmp(test_block1, expected_output1, 16) == 0) {
    printf("Test Case 1 Passed: The output matches the expected output.\n");
  } else {
    printf(
        "Test Case 1 Failed: The output does not match the expected output.\n");
  }

  // +++Test Case 2: shift rows+++
  unsigned char test_block2[16] = {212, 39,  17, 174, 224, 191, 152, 241,
                                   184, 180, 93, 229, 30,  65,  82,  48};

  unsigned char expected_output2[16] = {212, 191, 93, 48,  224, 180, 82,  174,
                                        184, 65,  17, 241, 30,  39,  152, 229};

  printf("Before shift_rows:\n");
  print_block(test_block2, 16);

  shift_rows(test_block2);

  printf("After shift_rows:\n");
  print_block(test_block2, 16);

  printf("Expected output:\n");
  print_block(expected_output2, 16);

  if (memcmp(test_block2, expected_output2, 16) == 0) {
    printf("Test Case 2 Passed: The output matches the expected output.\n");
  } else {
    printf(
        "Test Case 2 Failed: The output does not match the expected output.\n");
  }

  // +++Test Case 3: mix columns+++
  unsigned char test_block3[16] = {212, 191, 93, 48,  224, 180, 82,  174,
                                   184, 65,  17, 241, 30,  39,  152, 229};
  unsigned char expected_output3[16] = {4,  102, 129, 229, 224, 203, 25, 154,
                                        72, 248, 211, 122, 40,  6,   38, 76};

  printf("Before mix_columns:\n");
  print_block(test_block3, 16);

  mix_columns(test_block3);

  printf("After mix_columns:\n");
  print_block(test_block3, 16);

  printf("Expected output:\n");
  print_block(expected_output3, 16);

  if (memcmp(test_block3, expected_output3, 16) == 0) {
    printf("Test Case 3 Passed.\n");
  } else {
    printf("Test Case 3 Failed.\n");
  }

  //+++Test Case 4 expand key+++
  unsigned char test_block4[16] = {43,  126, 21, 22,  40, 174, 210, 166,
                                   171, 247, 21, 136, 9,  207, 79,  60};
  unsigned char expected_output4[176] =
      {43,  126, 21,  22,  40,  174, 210, 166, 171, 247, 21,  136, 9,   207,
       79,  60,  160, 250, 254, 23,  136, 84,  44,  177, 35,  163, 57,  57,
       42,  108, 118, 5,   242, 194, 149, 242, 122, 150, 185, 67,  89,  53,
       128, 122, 115, 89,  246, 127, 61,  128, 71,  125, 71,  22,  254, 62,
       30,  35,  126, 68,  109, 122, 136, 59,  239, 68,  165, 65,  168, 82,
       91,  127, 182, 113, 37,  59,  219, 11,  173, 0,   212, 209, 198, 248,
       124, 131, 157, 135, 202, 242, 184, 188, 17,  249, 21,  188, 109, 136,
       163, 122, 17,  11,  62,  253, 219, 249, 134, 65,  202, 0,   147, 253,
       78,  84,  247, 14,  95,  95,  201, 243, 132, 166, 79,  178, 78,  166,
       220, 79,  234, 210, 115, 33,  181, 141, 186, 210, 49,  43,  245, 96,
       127, 141, 41,  47,  172, 119, 102, 243, 25,  250, 220, 33,  40,  209,
       41,  65,  87,  92,  0,   110, 208, 20,  249, 168, 201, 238, 37,  137,
       225, 63,  12,  200, 182, 99,  12,  166}

  ;
  int size = 176;

  printf("Before expand the key:\n");
  print_block(test_block4, 16);

  unsigned char *result4 = expand_key(test_block4);

  printf("After expand key:\n");
  print_block(result4, 176);

  printf("Expected output:\n");
  print_block(expected_output4, 176);

  if (memcmp(result4, expected_output4, size) == 0) {
    printf("test case 4 passed.\n");
  } else {
    printf("test case 4 failed.\n");
  }

  // +++Test Case 5: add round key+++

  unsigned char test_block5[16] = {50, 67, 246, 168, 136, 90, 48, 141,
                                   49, 49, 152, 162, 224, 55, 7,  52};
  unsigned char round_key[16] = {43,  126, 21, 22,  40, 174, 210, 166,
                                 171, 247, 21, 136, 9,  207, 79,  60};
  unsigned char expected_output5[16] = {25,  61,  227, 190, 160, 244, 226, 43,
                                        154, 198, 141, 42,  233, 248, 72,  8};
  printf("Before add round key:\n");
  print_block(test_block5, 16);

  add_round_key(test_block5, round_key);
  print_block(round_key, 16);

  printf("After add round key:\n");
  print_block(test_block5, 16);

  printf("Expected output:\n");
  print_block(expected_output5, 16);

  if (memcmp(test_block5, expected_output5, 16) == 0) {
    printf("Test Case 5 Passed.\n");
  } else {
    printf("Test Case 5 add round key Failed.\n");
  }

  //+++test case 7: 9 main round test+++
  unsigned char plaintext[16] = {25,  61,  227, 190, 160, 244, 226, 43,
                                 154, 198, 141, 42,  233, 248, 72,  8};
  unsigned char expandedKey[176] = {
      43,  126, 21,  22,  40,  174, 210, 166, 171, 247, 21,  136, 9,   207, 79,
      60,  160, 250, 254, 23,  136, 84,  44,  177, 35,  163, 57,  57,  42,  108,
      118, 5,   242, 194, 149, 242, 122, 150, 185, 67,  89,  53,  128, 122, 115,
      89,  246, 127, 61,  128, 71,  125, 71,  22,  254, 62,  30,  35,  126, 68,
      109, 122, 136, 59,  239, 68,  165, 65,  168, 82,  91,  127, 182, 113, 37,
      59,  219, 11,  173, 0,   212, 209, 198, 248, 124, 131, 157, 135, 202, 242,
      184, 188, 17,  249, 21,  188, 109, 136, 163, 122, 17,  11,  62,  253, 219,
      249, 134, 65,  202, 0,   147, 253, 78,  84,  247, 14,  95,  95,  201, 243,
      132, 166, 79,  178, 78,  166, 220, 79,  234, 210, 115, 33,  181, 141, 186,
      210, 49,  43,  245, 96,  127, 141, 41,  47,  172, 119, 102, 243, 25,  250,
      220, 33,  40,  209, 41,  65,  87,  92,  0,   110, 208, 20,  249, 168, 201,
      238, 37,  137, 225, 63,  12,  200, 182, 99,  12,  166};
  unsigned char expected_ciphertext[16] = {
      235, 64, 242, 30, 89, 46, 56, 132, 139, 161, 19, 231, 27, 195, 66, 210};
  for (int round = 1; round <= 9; ++round) {
    sub_bytes(plaintext);
    printf("sub_bytes:\n");
    print_block(plaintext, 16);
    shift_rows(plaintext);
    printf("shift rows:\n");
    print_block(plaintext, 16);
    mix_columns(plaintext);
    printf("mix columns:\n");
    print_block(plaintext, 16);

    add_round_key(
        plaintext,
        expandedKey + (round * BLOCK_SIZE));  // Use the correct segment of
  }
  printf("After 9 main rounds:\n");
  print_block(plaintext, 16);
  printf("After 9 main rounds expected output:\n");
  print_block(expected_ciphertext, 16);

  if (memcmp(plaintext, expected_ciphertext, BLOCK_SIZE) == 0) {
    printf("Test case 7: main rounds Passed.\n");
  } else {
    printf("Test case 7 main rounds Failed.\n");
  }

  //+++test case8: final round(without MixColumns)+++
  unsigned char plaintext8[16] = {235, 64,  242, 30,  89, 46,  56, 132,
                                  139, 161, 19,  231, 27, 195, 66, 210};
  unsigned char expandedKey8[176] = {
      43,  126, 21,  22,  40,  174, 210, 166, 171, 247, 21,  136, 9,   207, 79,
      60,  160, 250, 254, 23,  136, 84,  44,  177, 35,  163, 57,  57,  42,  108,
      118, 5,   242, 194, 149, 242, 122, 150, 185, 67,  89,  53,  128, 122, 115,
      89,  246, 127, 61,  128, 71,  125, 71,  22,  254, 62,  30,  35,  126, 68,
      109, 122, 136, 59,  239, 68,  165, 65,  168, 82,  91,  127, 182, 113, 37,
      59,  219, 11,  173, 0,   212, 209, 198, 248, 124, 131, 157, 135, 202, 242,
      184, 188, 17,  249, 21,  188, 109, 136, 163, 122, 17,  11,  62,  253, 219,
      249, 134, 65,  202, 0,   147, 253, 78,  84,  247, 14,  95,  95,  201, 243,
      132, 166, 79,  178, 78,  166, 220, 79,  234, 210, 115, 33,  181, 141, 186,
      210, 49,  43,  245, 96,  127, 141, 41,  47,  172, 119, 102, 243, 25,  250,
      220, 33,  40,  209, 41,  65,  87,  92,  0,   110, 208, 20,  249, 168, 201,
      238, 37,  137, 225, 63,  12,  200, 182, 99,  12,  166};
  unsigned char expected_ciphertext8[16] = {57,  37, 132, 29,  2,  220, 9,  251,
                                            220, 17, 133, 151, 25, 106, 11, 50};

  sub_bytes(plaintext8);
  shift_rows(plaintext8);
  add_round_key(plaintext8, expandedKey8 + 10 * BLOCK_SIZE);

  printf("After final round:\n");
  print_block(plaintext8, 16);
  printf("After final round expected output:\n");
  print_block(expected_ciphertext8, 16);
  if (memcmp(plaintext8, expected_ciphertext8, BLOCK_SIZE) == 0) {
    printf("Test case 8: final rounds Passed.\n");
  } else {
    printf("Test case 8 final rounds Failed.\n");
  }

  //+++test case 9: aes_encrypt_block+++
  unsigned char plaintext9[16] = {50, 67, 246, 168, 136, 90, 48, 141,
                                  49, 49, 152, 162, 224, 55, 7,  52};
  unsigned char initial_key[16] = {43,  126, 21, 22,  40, 174, 210, 166,
                                   171, 247, 21, 136, 9,  207, 79,  60};
  unsigned char expected_ciphertext9[16] = {57,  37, 132, 29,  2,  220, 9,  251,
                                            220, 17, 133, 151, 25, 106, 11, 50};

  printf("Before encryption:\n");
  print_block(plaintext9, 16);

  unsigned char *ciphertext = aes_encrypt_block(plaintext9, initial_key);

  printf("After encryption:\n");
  print_block(ciphertext, 16);
  printf("expected output:\n");
  print_block(expected_ciphertext9, 16);

  if (memcmp(ciphertext, expected_ciphertext9, 16) == 0) {
    printf("Test case 9: AES Encryption SUCCESS.\n");
  } else {
    printf("Test case 9 AES Encryption FAILED.\n");
  }

  //+++test case 10: invert_sub_bytes test +++
  unsigned char test_block10[16] = {212, 224, 184, 30, 39,  191, 180, 65,
                                    17,  152, 93,  82, 174, 241, 229, 48};
  unsigned char expected_output10[16] = {25,  160, 154, 233, 61,  244, 198, 248,
                                         227, 226, 141, 72,  190, 43,  42,  8};

  printf("Before invert sub_bytes:\n");
  print_block(test_block10, 16);

  inverse_sub_bytes(test_block10);

  printf("After invert sub_bytes:\n");
  print_block(test_block10, 16);

  printf("Expected output:\n");
  print_block(expected_output10, 16);
  if (memcmp(test_block10, expected_output10, 16) == 0) {
    printf("Test Case 10 invert sub byte Passed.\n");
  } else {
    printf("Test Case 10 invert sub byte Failed.\n");
  }

  // +++Test Case 11: inverse shift rows+++
  unsigned char test_block11[16] = {212, 191, 93, 48,  224, 180, 82,  174,
                                    184, 65,  17, 241, 30,  39,  152, 229};

  unsigned char expected_output11[16] = {212, 39,  17, 174, 224, 191, 152, 241,
                                         184, 180, 93, 229, 30,  65,  82,  48};

  printf("Before inverse shift_rows:\n");
  print_block(test_block11, 16);

  inverse_shift_rows(test_block11);

  printf("After inverse shift_rows:\n");
  print_block(test_block11, 16);

  printf("Expected output:\n");
  print_block(expected_output11, 16);

  // Using memcmp for comparison
  if (memcmp(test_block11, expected_output11, 16) == 0) {
    printf("Test Case 11 inverse shift rows Passed.\n");
  } else {
    printf("Test Case 11 inverse shift rows Failed.\n");
  }

  // +++Test Case 12: inverse mix columns+++
  unsigned char test_block12[16] = {4,  102, 129, 229, 224, 203, 25, 154,
                                    72, 248, 211, 122, 40,  6,   38, 76};
  unsigned char expected_output12[16] = {212, 191, 93, 48,  224, 180, 82,  174,
                                         184, 65,  17, 241, 30,  39,  152, 229};

  printf("Before inverse mix_columns:\n");
  print_block(test_block12, 16);

  inverse_mix_columns(test_block12);

  printf("After inverse mix_columns:\n");
  print_block(test_block12, 16);

  printf("Expected output:\n");
  print_block(expected_output12, 16);

  if (memcmp(test_block12, expected_output12, 16) == 0) {
    printf("Test Case 12 inverse mix columns Passed.\n");
  } else {
    printf("Test Case 12 inverse mix columns Failed.\n");
  }

  //+++test case 14: first round decyption+++
  unsigned char test_block14[16] = {57,  37, 132, 29,  2,  220, 9,  251,
                                    220, 17, 133, 151, 25, 106, 11, 50};

  unsigned char expected_output14[16] = {235, 64,  242, 30,  89, 46,  56, 132,
                                         139, 161, 19,  231, 27, 195, 66, 210};
  printf("Before add last round key:\n");
  print_block(test_block14, 16);

  add_round_key(test_block14, expandedKey + 10 * BLOCK_SIZE);
  inverse_shift_rows(test_block14);
  inverse_sub_bytes(test_block14);

  printf("After 1 round :\n");
  print_block(test_block14, 16);

  printf("Expected output:\n");
  print_block(expected_output14, 16);

  if (memcmp(test_block14, expected_output14, 16) == 0) {
    printf("Test Case 14 first round of decryption Passed.\n");
  } else {
    printf("Test Case 14 first round of decryption Failed.\n");
  }

  //+++Test case 15: 10 main inverse round test+++
  unsigned char ciphertext15[16] = {235, 64,  242, 30,  89, 46,  56, 132,
                                    139, 161, 19,  231, 27, 195, 66, 210};

  unsigned char expected_plaintext15[16] = {50, 67, 246, 168, 136, 90, 48, 141,
                                            49, 49, 152, 162, 224, 55, 7,  52};
  for (int round = 9; round >= 1; --round) {
    add_round_key(ciphertext15, expandedKey + (round * BLOCK_SIZE));

    inverse_mix_columns(ciphertext15);
    printf("inverse mix columns:\n");
    print_block(ciphertext15, 16);

    inverse_shift_rows(ciphertext15);
    printf("inverse shift rows:\n");
    print_block(ciphertext15, 16);

    inverse_sub_bytes(ciphertext15);
    printf("inverse sub_bytes:\n");
    print_block(ciphertext15, 16);
  }

  add_round_key(ciphertext15, round_key);

  printf("After 10 main rounds:\n");
  print_block(ciphertext15, 16);
  printf("After 10 main rounds expected output:\n");
  print_block(expected_plaintext15, 16);

  // Compare the generated ciphertext with the expected ciphertext
  if (memcmp(ciphertext15, expected_plaintext15, BLOCK_SIZE) == 0) {
    printf("Test case 15: 10 main inverse rounds Passed. \n");
  } else {
    printf("Test case 15: 10 main inverse rounds Failed.\n");
  }

  //+++test case 16: aes_decrypt_block+++
  unsigned char ciphertext16[16] = {57,  37, 132, 29,  2,  220, 9,  251,
                                    220, 17, 133, 151, 25, 106, 11, 50};

  unsigned char expected_plaintext16[16] = {50, 67, 246, 168, 136, 90, 48, 141,
                                            49, 49, 152, 162, 224, 55, 7,  52};

  printf("Before decryption:\n");
  print_block(ciphertext16, 16);

  unsigned char *plaintext16 = aes_decrypt_block(ciphertext16, initial_key);

  printf("After decryption:\n");
  print_block(plaintext16, 16);
  printf("expected output:\n");
  print_block(expected_plaintext16, 16);

  if (memcmp(plaintext16, expected_plaintext16, 16) == 0) {
    printf("Test case 16: AES Decryption SUCCESS.\n");
  } else {
    printf("Test case 16: AES Decryption FAILED.\n");
  }

  return 0;
};
