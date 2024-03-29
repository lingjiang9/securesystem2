#include <stdio.h>
#include "rijndael.h"  // Ensure this is correctly included for the sub_bytes function

// Function to print the original block in decimal format without any prefix
void print_original_block(unsigned char *block, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d, ", block[i]);
    }
    printf("\n");
}

// Function to print the block in hexadecimal format with a 0x prefix after sub_bytes
void print_block_after_sub_bytes(unsigned char *block, int size) {
    for (int i = 0; i < size; i++) {
        printf("0x%02x, ", block[i]);
    }
    printf("\n");
}

int main() {
    // Initialize the block with values from 1 to 16
    unsigned char test_block[16] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    };

    // Print the original block in decimal format
    printf("Original block:\n");
    print_original_block(test_block, 16);

    // Apply the sub_bytes function
    sub_bytes(test_block);

    // Print the block after applying sub_bytes in the specified format
    printf("Block after applying sub_bytes:\n");
    print_block_after_sub_bytes(test_block, 16);

    return 0;
}
