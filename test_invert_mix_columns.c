#include "rijndael.h"
#include <stdio.h>

#define BLOCK_SIZE 16
#define BLOCK_ACCESS(block, row, col) (block[(row * 4) + col])

// Define xtime, mix_columns, and inv_mix_columns here as you've done previously.

void print_block(const char* description, unsigned char *block) {
    printf("%s:\n", description);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", block[i]);
        if ((i + 1) % 4 == 0) printf("\n");
    }
    printf("\n");
}

int main() {
    // Original block (after some rounds of AES encryption)
    unsigned char block[BLOCK_SIZE] = {
        0x47, 0x40, 0xa3, 0x4c,
        0x37, 0xd4, 0x70, 0x9f,
        0x94, 0xe4, 0x3a, 0x42,
        0xed, 0xa5, 0xa6, 0xbc
    };

    // Expected block after inverse mix columns
    unsigned char expected[BLOCK_SIZE] = {
        0x87, 0xf2, 0x4d, 0x97,
        0x6e, 0x4c, 0x90, 0xec,
        0x46, 0xe7, 0x4a, 0xc3,
        0xa6, 0x8c, 0xd8, 0x95
    };

    // Perform the inv_mix_columns operation on the block
    invert_mix_columns(block);

    // Check if the output matches the expected block
    int is_correct = 1;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        if (block[i] != expected[i]) {
            is_correct = 0;
            break;
        }
    }

    // Print the result
    print_block("Original", block);
    print_block("Expected", expected);
    
    if (is_correct) {
        printf("inv_mix_columns test PASSED.\n");
    } else {
        printf("inv_mix_columns test FAILED.\n");
    }

    return 0;
}
