
#include "rijndael.h"

#include <stdio.h>
#define BLOCK_ACCESS(block, row, col) (block[(row * 4) + col])
#define BLOCK_SIZE 16
// Make sure to include the definitions for mix_columns and other necessary functions here

void print_block(unsigned char *block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", block[i]);
        if ((i + 1) % 4 == 0) printf("\n");
    }
    printf("\n");
}

int main() {
    // Example block taken from AES specification
    unsigned char block[BLOCK_SIZE] = {
        0x87, 0xf2, 0x4d, 0x97,
        0x6e, 0x4c, 0x90, 0xec,
        0x46, 0xe7, 0x4a, 0xc3,
        0xa6, 0x8c, 0xd8, 0x95
    };

    // Expected output after mix_columns on the example block
    unsigned char expected[BLOCK_SIZE] = {
        0x47, 0x40, 0xa3, 0x4c,
        0x37, 0xd4, 0x70, 0x9f,
        0x94, 0xe4, 0x3a, 0x42,
        0xed, 0xa5, 0xa6, 0xbc
    };

    printf("Original block:\n");
    print_block(block);

    mix_columns(block);

    printf("Block after mix_columns:\n");
    print_block(block);

    printf("Expected block:\n");
    print_block(expected);

    // Verify the result
    int is_correct = 1;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        if (block[i] != expected[i]) {
            is_correct = 0;
            break;
        }
    }

    if (is_correct) {
        printf("mix_columns test PASSED.\n");
    } else {
        printf("mix_columns test FAILED.\n");
    }

    return 0;
}
