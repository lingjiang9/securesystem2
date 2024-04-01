#include <stdio.h>

#define BLOCK_ACCESS(block, row, col) (block[(row * 4) + col])
#define BLOCK_SIZE 16


void shift_rows(unsigned char *block);

// Utility function to print the state in a formatted 4x4 block
void print_block(unsigned char *block) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            printf("%02x ", BLOCK_ACCESS(block, row, col));
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    unsigned char block[BLOCK_SIZE] = {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B,
        0x0C, 0x0D, 0x0E, 0x0F
    };

    printf("Original block:\n");
    print_block(block);

    shift_rows(block);

    printf("Block after shift_rows:\n");
    print_block(block);

    return 0;
}
