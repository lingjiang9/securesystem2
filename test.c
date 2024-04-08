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

// Function to compare two arrays of char
int areCharArraysEqual(const unsigned char *result4,
                       const unsigned char *expected_output4, int size) {
  for (int i = 0; i < size; i++) {
    if (result4[i] != expected_output4[i]) {
      return 0;  // The arrays are not equal
    }
  }
  return 1;  // The arrays are equal
}

int main() {
  // +++++++++++++++Test Case 1: sub bytes+++++++++++++++++++
  //   unsigned char test_block1[16] = {25,  160, 154, 233, 61,  244, 198,
  //   248,
  //                                    227, 226, 141, 72,  190, 43,  42,  8};
  //   unsigned char expected_output1[16] = {212, 224, 184, 30, 39,  191, 180,
  //   65,
  //                                         17,  152, 93,  82, 174, 241, 229,
  //                                         48};

  //   printf("Before sub_bytes:\n");
  //   print_block(test_block1, 16);

  //   sub_bytes(test_block1);

  //   printf("After sub_bytes:\n");
  //   print_block(test_block1, 16);

  //   printf("Expected output:\n");
  //   print_block(expected_output1, 16);

  //   // Using memcmp for comparison
  //   if (memcmp(test_block1, expected_output1, 16) == 0) {
  //     printf("Test Case 1 Passed: The output matches the expected
  //     output.\n");
  //   } else {
  //     printf(
  //         "Test Case 1 Failed:testThe output does not match the expected "
  //         "output.\n");
  //   }

  // +++++++++++++Test Case 2: shift rows++++++++++++
  //   unsigned char test_block2[16] = {212, 39,  17, 174, 224, 191, 152, 241,
  //                                    184, 180, 93, 229, 30,  65,  82,  48};

  //   unsigned char expected_output2[16] = {212, 191, 93, 48,  224, 180, 82,
  //   174,
  //                                         184, 65,  17, 241, 30,  39,  152,
  //                                         229};

  //   printf("Before shift_rows:\n");
  //   print_block(test_block2, 16);

  //   shift_rows(test_block2);

  //   printf("After shift_rows:\n");
  //   print_block(test_block2, 16);

  //   printf("Expected output:\n");
  //   print_block(expected_output2, 16);

  //   // Using memcmp for comparison
  //   if (memcmp(test_block2, expected_output2, 16) == 0) {
  //     printf("Test Case 2 Passed: The output matches the expected
  //     output.\n");
  //   } else {
  //     printf(
  //         "Test Case 2 Failed:testThe output does not match the expected "
  //         "output.\n");
  //   }

  // +++++++++++++Test Case 3: mix columns++++++++++++
  //   unsigned char test_block3[16] = {212, 191, 93, 48,  224, 180, 82,  174,
  //                                    184, 65,  17, 241, 30,  39,  152, 229};
  //   unsigned char expected_output3[16] = {4,  102, 129, 229, 224, 203, 25,
  //   154,
  //                                         72, 248, 211, 122, 40,  6,   38,
  //                                         76};

  //   printf("Before mix_columns:\n");
  //   print_block(test_block3, 16);

  //   mix_columns(test_block3);

  //   printf("After mix_columns:\n");
  //   print_block(test_block3, 16);

  //   printf("Expected output:\n");
  //   print_block(expected_output3, 16);

  //   // Using memcmp for comparison
  //   if (memcmp(test_block3, expected_output3, 16) == 0) {
  //     printf("Test Case 3 Passed: The output matches the expected
  //     output.\n");
  //   } else {
  //     printf(
  //         "Test Case 3 Failed:testThe output does not match the expected "
  //         "output.\n");
  //   }

  //   ++ ++ ++ ++ ++ ++ +Test Case 4 expand key++ ++ ++ ++ ++ ++

  //   unsigned char test_block4[16] = {43,  126, 21, 22,  40, 174, 210,
  //   166,
  //                                    171, 247, 21, 136, 9,  207, 79, 60};
  //   unsigned char expected_output4[176] =
  //       {43,  126, 21,  22,  40,  174, 210, 166, 171, 247, 21,  136, 9,
  //       207,
  //        79,  60,  160, 250, 254, 23,  136, 84,  44,  177, 35,  163, 57,
  //        57, 42,  108, 118, 5,   242, 194, 149, 242, 122, 150, 185, 67,
  //        89,  53, 128, 122, 115, 89,  246, 127, 61,  128, 71,  125, 71,
  //        22,  254, 62, 30,  35,  126, 68,  109, 122, 136, 59,  239, 68,
  //        165, 65,  168, 82, 91,  127, 182, 113, 37,  59,  219, 11,  173,
  //        0,   212, 209, 198, 248, 124, 131, 157, 135, 202, 242, 184, 188,
  //        17,  249, 21,  188, 109, 136, 163, 122, 17,  11,  62,  253, 219,
  //        249, 134, 65,  202, 0, 147, 253, 78,  84,  247, 14,  95,  95,
  //        201, 243, 132, 166, 79, 178, 78,  166, 220, 79,  234, 210, 115,
  //        33,  181, 141, 186, 210, 49,  43, 245, 96, 127, 141, 41,  47,
  //        172, 119, 102, 243, 25,  250, 220, 33, 40,  209, 41,  65,  87,
  //        92,  0,   110, 208, 20,  249, 168, 201, 238, 37,  137, 225, 63,
  //        12,  200, 182, 99,  12,  166}

  //   ;
  //   int size = 176;

  //   printf("Before expand the key:\n");
  //   print_block(test_block4, 16);

  //   unsigned char *result4 = expand_key(test_block4);

  //   printf("After expand key:\n");
  //   print_block(result4, 176);

  //   printf("Expected output:\n");
  //   print_block(expected_output4, 176);

  //   if (areCharArraysEqual(result4, expected_output4, size)) {
  //     printf("result4 and expected_output4 are equal.\n");
  //   } else {
  //     printf("result4 and expected_output4 are not equal.\n");
  //   }

  // +++++++++++++Test Case 5: add round key++++++++++++
  // Declare the function prototype
  //   void add_round_key(unsigned char *block, const unsigned char
  //   *round_key); unsigned char test_block5[16] = {50, 67, 246, 168, 136,
  //   90, 48, 141,
  //                                    49, 49, 152, 162, 224, 55, 7,  52};
  //   unsigned char round_key[16] = {43,  126, 21, 22,  40, 174, 210, 166,
  //                                  171, 247, 21, 136, 9,  207, 79,  60};
  //   unsigned char expected_output5[16] = {25,  61,  227, 190, 160, 244,
  //   226, 43,
  //                                         154, 198, 141, 42,  233, 248,
  //                                         72, 8};
  //   printf("Before add round key:\n");
  //   print_block(test_block5, 16);

  //   add_round_key(test_block5, round_key);
  //   print_block(round_key, 16);

  //   printf("After add round key:\n");
  //   print_block(test_block5, 16);

  //   printf("Expected output:\n");
  //   print_block(expected_output5, 16);

  //   if (memcmp(test_block5, expected_output5, 16) == 0) {
  //     printf("Test Case 5 Passed: The output matches the expected
  //     output.\n");
  //   } else {
  //     printf(
  //         "Test Case 5 add round key Failed:The output does not match the
  //         " "expected " "output.\n");
  //   }

  // +++++++++++++Test Case 6: encrypt block ++++++++++++
  //   unsigned char plaintext[BLOCK_SIZE] = {50, 67, 246, 168, 136, 90, 48,
  //   141,
  //                                          49, 49, 152, 162, 224, 55, 7,
  //                                          52};
  //   unsigned char key[BLOCK_SIZE] = {43,  126, 21, 22,  40, 174, 210,
  //   166,
  //                                    171, 247, 21, 136, 9,  207, 79, 60};
  //   unsigned char expected_output6[BLOCK_SIZE] = {
  //       57, 37, 132, 29, 2, 220, 9, 251, 220, 17, 133, 151, 25, 106, 11,
  //       50};
  //   // Encrypt the plaintext
  //   unsigned char *output = aes_encrypt_block(plaintext, key);
  //   if (!output) {
  //     printf("Failed to encrypt plaintext.\n");
  //     // free(expected_output6);  // Free memory allocated for expected
  //     output return 1;
  //   }

  //   printf("Before encryption:\n");
  //   print_block(plaintext, 16);

  //   aes_encrypt_block(plaintext, key);

  //   printf("After encryption:\n");
  //   print_block(output, 16);

  //   printf("Expected output:\n");
  //   print_block(expected_output6, 16);

  //   // Compare the output with the expected output
  //   if (memcmp(output, expected_output6, BLOCK_SIZE) == 0) {
  //     printf("Encryption Test Passed: Output matches the expected
  //     output.\n");
  //   } else {
  //     printf(
  //         "Encryption Test Failed: Output does not match the expected
  //         output.\n");
  //   }

  //   // Free dynamically allocated memory
  //   free(output);

  //++++++++++++++++test case 7: main round test+++++++++++++
  //   unsigned char plaintext[16] = {25,  61,  227, 190, 160, 244, 226, 43,
  //                                  154, 198, 141, 42,  233, 248, 72,  8};
  //   unsigned char expandedKey[176] = {
  //       43,  126, 21,  22,  40,  174, 210, 166, 171, 247, 21,  136, 9,   207,
  //       79, 60,  160, 250, 254, 23,  136, 84,  44,  177, 35,  163, 57,  57,
  //       42,  108, 118, 5,   242, 194, 149, 242, 122, 150, 185, 67,  89,  53,
  //       128, 122, 115, 89,  246, 127, 61,  128, 71,  125, 71,  22,  254, 62,
  //       30,  35,  126, 68, 109, 122, 136, 59,  239, 68,  165, 65,  168, 82,
  //       91,  127, 182, 113, 37, 59,  219, 11,  173, 0,   212, 209, 198, 248,
  //       124, 131, 157, 135, 202, 242, 184, 188, 17,  249, 21,  188, 109, 136,
  //       163, 122, 17,  11,  62,  253, 219, 249, 134, 65,  202, 0,   147, 253,
  //       78,  84,  247, 14,  95,  95,  201, 243, 132, 166, 79,  178, 78,  166,
  //       220, 79,  234, 210, 115, 33,  181, 141, 186, 210, 49,  43,  245, 96,
  //       127, 141, 41,  47,  172, 119, 102, 243, 25,  250, 220, 33,  40,  209,
  //       41,  65,  87,  92,  0,   110, 208, 20,  249, 168, 201, 238, 37,  137,
  //       225, 63,  12,  200, 182, 99,  12,  166};
  //   unsigned char expected_ciphertext[16] = {
  //       235, 64, 242, 30, 89, 46, 56, 132, 139, 161, 19, 231, 27, 195, 66,
  //       210};
  //   for (int round = 1; round <= 9; ++round) {
  //     sub_bytes(plaintext);
  //     printf("sub_bytes:\n");
  //     print_block(plaintext, 16);
  //     shift_rows(plaintext);
  //     printf("shift rows:\n");
  //     print_block(plaintext, 16);
  //     mix_columns(plaintext);
  //     printf("mix columns:\n");
  //     print_block(plaintext, 16);

  //     add_round_key(
  //         plaintext,
  //         expandedKey + (round * BLOCK_SIZE));  // Use the correct segment of
  //   }
  //   printf("After 9 main rounds:\n");
  //   print_block(plaintext, 16);
  //   printf("After 9 main rounds expected output:\n");
  //   print_block(expected_ciphertext, 16);

  //   // Compare the generated ciphertext with the expected ciphertext
  //   if (memcmp(plaintext, expected_ciphertext, BLOCK_SIZE) == 0) {
  //     printf(
  //         "Test case 7: main rounds Passed: Ciphertext matches the expected "
  //         "ciphertext.\n");
  //   } else {
  //     printf(
  //         "Test case 7 main rounds Failed: Ciphertext does not match the "
  //         "expected "
  //         "ciphertext.\n");
  //   }

  //+++++++++++++++test case8: final round+++++++++++++(without MixColumns)
  //   unsigned char plaintext8[16] = {235, 64,  242, 30,  89, 46,  56, 132,
  //                                   139, 161, 19,  231, 27, 195, 66, 210};
  //   unsigned char expandedKey8[176] = {
  //       43,  126, 21,  22,  40,  174, 210, 166, 171, 247, 21,  136, 9,   207,
  //       79, 60,  160, 250, 254, 23,  136, 84,  44,  177, 35,  163, 57,  57,
  //       42,  108, 118, 5,   242, 194, 149, 242, 122, 150, 185, 67,  89,  53,
  //       128, 122, 115, 89,  246, 127, 61,  128, 71,  125, 71,  22,  254, 62,
  //       30,  35,  126, 68, 109, 122, 136, 59,  239, 68,  165, 65,  168, 82,
  //       91,  127, 182, 113, 37, 59,  219, 11,  173, 0,   212, 209, 198, 248,
  //       124, 131, 157, 135, 202, 242, 184, 188, 17,  249, 21,  188, 109, 136,
  //       163, 122, 17,  11,  62,  253, 219, 249, 134, 65,  202, 0,   147, 253,
  //       78,  84,  247, 14,  95,  95,  201, 243, 132, 166, 79,  178, 78,  166,
  //       220, 79,  234, 210, 115, 33,  181, 141, 186, 210, 49,  43,  245, 96,
  //       127, 141, 41,  47,  172, 119, 102, 243, 25,  250, 220, 33,  40,  209,
  //       41,  65,  87,  92,  0,   110, 208, 20,  249, 168, 201, 238, 37,  137,
  //       225, 63,  12,  200, 182, 99,  12,  166};
  //   unsigned char expected_ciphertext8[16] = {57,  37, 132, 29,  2,  220, 9,
  //   251,
  //                                             220, 17, 133, 151, 25, 106, 11,
  //                                             50};

  //   sub_bytes(plaintext8);
  //   shift_rows(plaintext8);
  //   add_round_key(plaintext8, expandedKey8 + 10 * BLOCK_SIZE);

  //   printf("After final round:\n");
  //   print_block(plaintext8, 16);
  //   printf("After final round expected output:\n");
  //   print_block(expected_ciphertext8, 16);
  //   // Compare the generated ciphertext with the expected ciphertext
  //   if (memcmp(plaintext8, expected_ciphertext8, BLOCK_SIZE) == 0) {
  //     printf(
  //         "Test case 8: final rounds Passed: Ciphertext matches the expected
  //         " "ciphertext.\n");
  //   } else {
  //     printf(
  //         "Test case 8 final rounds Failed: Ciphertext does not match the "
  //         "expected "
  //         "ciphertext.\n");
  //   }

  //+++++++++++++++++test case 9: aes_encrypt_block++++++++++++
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

  // Compare the generated ciphertext with the expected ciphertext
  if (memcmp(ciphertext, expected_ciphertext9, 16) == 0) {
    printf(
        "Test case 9: AES Encryption SUCCESS: Ciphertext matches the expected "
        "ciphertext.\n");
  } else {
    printf(
        "Test case 9 AES Encryption FAILED: Ciphertext does not match the "
        "expected "
        "ciphertext.\n");
  }

  return 0;
};
