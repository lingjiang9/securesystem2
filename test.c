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

  // Using memcmp for comparison
  if (memcmp(test_block1, expected_output1, 16) == 0) {
    printf("Test Case 1 Passed: The output matches the expected output.\n");
  } else {
    printf(
        "Test Case 1 Failed:testThe output does not match the expected "
        "output.\n");
  }

  // +++++++++++++Test Case 2: shift rows++++++++++++
  unsigned char test_block2[16] = {212, 224, 184, 30, 39,  191, 180, 65,
                                   17,  152, 93,  82, 174, 241, 229, 48};
  unsigned char expected_output2[16] = {212, 224, 184, 30,  191, 180, 65,  39,
                                        93,  82,  17,  152, 48,  174, 241, 229};

  printf("Before shift_rows:\n");
  print_block(test_block2, 16);

  shift_rows(test_block2);

  printf("After shift_rows:\n");
  print_block(test_block2, 16);

  printf("Expected output:\n");
  print_block(expected_output2, 16);

  // Using memcmp for comparison
  if (memcmp(test_block2, expected_output2, 16) == 0) {
    printf("Test Case 2 Passed: The output matches the expected output.\n");
  } else {
    printf(
        "Test Case 2 Failed:testThe output does not match the expected "
        "output.\n");
  }

  // +++++++++++++Test Case 3: mix columns++++++++++++
  unsigned char test_block3[16] = {212, 224, 184, 30,  191, 180, 65,  39,
                                   93,  82,  17,  152, 48,  174, 241, 229};
  unsigned char expected_output3[16] = {4,   224, 72,  40, 102, 203, 248, 6,
                                        129, 25,  211, 38, 229, 154, 122, 76};

  printf("Before mix_columns:\n");
  print_block(test_block3, 16);

  mix_columns(test_block3);

  printf("After mix_columns:\n");
  print_block(test_block3, 16);

  printf("Expected output:\n");
  print_block(expected_output3, 16);

  // Using memcmp for comparison
  if (memcmp(test_block3, expected_output3, 16) == 0) {
    printf("Test Case 3 Passed: The output matches the expected output.\n");
  } else {
    printf(
        "Test Case 3 Failed:testThe output does not match the expected "
        "output.\n");
  }

  //   ++ ++ ++ ++ ++ ++ +Test Case 4 expand key++ ++ ++ ++ ++ ++

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

  if (areCharArraysEqual(result4, expected_output4, size)) {
    printf("result4 and expected_output4 are equal.\n");
  } else {
    printf("result4 and expected_output4 are not equal.\n");
  }

  // +++++++++++++Test Case 5: add round key++++++++++++
  // Declare the function prototype
  void add_round_key(unsigned char *block, const unsigned char *round_key);
  unsigned char test_block5[16] = {50, 67, 246, 168, 136, 90, 48, 141,
                                   49, 49, 152, 162, 224, 55, 7,  52};
  unsigned char round_key[16] = {43,  126, 21, 22,  40, 174, 210, 166,
                                 171, 247, 21, 136, 9,  207, 79,  60};
  unsigned char expected_output5[16] = {25,  61,  227, 190, 160, 244, 226, 43,
                                        154, 198, 141, 42,  233, 248, 72,  8};
  printf("Before add round key:\n");
  print_block(test_block5, 16);

  add_round_key(test_block5, round_key);

  printf("After add round key:\n");
  print_block(test_block5, 16);

  printf("Expected output:\n");
  print_block(expected_output5, 16);

  if (memcmp(test_block5, expected_output5, 16) == 0) {
    printf("Test Case 5 Passed: The output matches the expected output.\n");
  } else {
    printf(
        "Test Case 5 Failed:The output does not match the expected "
        "output.\n");
  }
  return 0;
}
