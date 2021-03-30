/*
 * About: A5/1 Implementation
 * Author: Bradley Reeves
 * Date: 03/29/2021
 * 
 * This implementation solves a question from the textbook Information Security 
 * Principles and Practice by Mark Stamp. The author mentions that there is a 
 * runup process that typically occurs after the registers are initially filled.
 * This implementation does not include the runup process.
 * 
 * Binary values are used throughout this implementation for clarity, but any
 * numbering system can be used instead (e.g., hexadecimal or decimal).
 * 
 */

#include <stdio.h>
#include <stdlib.h>

// Masks for the three shift registers
#define LFSR1_MASK 0b1111111111111111111        // 19 bits, numbered 0, 1, ..., 18
#define LFSR2_MASK 0b1111111111111111111111     // 22 bits, numbered 0, 1, ..., 21
#define LFSR3_MASK 0b11111111111111111111111    // 23 bits, numbered 0, 1, ..., 22

// Clocking bit of each of the three shift registers
#define LFSR1_CLOCK 0b100000000                 // bit 8
#define LFSR2_CLOCK 0b10000000000               // bit 10
#define LFSR3_CLOCK 0b10000000000               // bit 10

// Feedback taps, for clocking the shift registers
#define LFSR1_TAPS 0b1110010000000000000        // bits 18, 17, 16, 13
#define LFSR2_TAPS 0b1100000000000000000000     // bits 21, 20
#define LFSR3_TAPS 0b11100000000000010000000    // bits 22, 21, 20, 7

// Output taps, for keystream bit generation 
#define LFSR1_MSB 0b1000000000000000000         // bit 18
#define LFSR2_MSB 0b1000000000000000000000      // bit 21
#define LFSR3_MSB 0b10000000000000000000000     // bit 22

// Register lengths in bits
#define LFSR1_LEN 19
#define LFSR2_LEN 22
#define LFSR3_LEN 23

// Number of keystream bits to generate
#define ITERATIONS 32

// Lookup table macro
#define R2(n) n, n + 2*64, n + 1*64, n + 3*64
#define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#define R6(n) R4(n), R4(n + 2*4), R4(n + 1*4), R4(n + 3*4)
#define REVERSE_BITS R6(0), R6(2), R6(1), R6(3)

// Stores the reverse of each table
unsigned int lookupTable[256] = {REVERSE_BITS};

struct Registers {
    int LFSR1;
    int LFSR2; 
    int LFSR3; 
    int keystream;
};

// Print each bit of a number
void printBits(size_t const size, void const * const ptr) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

/*
 * Note: The author of the textbook from which this problem is from
 * indexes by most significant bit first. In order to get the 
 * correct answer, I need to to reverse the order of the initial
 * bits. This isn't necessary in an actual implementation.
 */
int reverseBits(int reg, int len) {
    // Split, reverse, and rearrange each byte chunk
    unsigned int reverse = lookupTable[reg & 0b11111111] << 24 |
    lookupTable[(reg >> 8) & 0b11111111] << 16 |
    lookupTable[(reg >> 16) & 0b11111111] << 8 |
    lookupTable[(reg >> 24) & 0b11111111];
    
    // Shift bits to account for register size
    return reverse >> (32 - len);
}

// Convert a binary string to long
long stringToBinary(char *str) {
    long value = 0;

    while (*str) {
        value <<= 1;
        value += ((*str++) & 1);
    }
    return value;
}

int parity(int x) {
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 1;
}

// Get majority bit of LFSR clocking bits
int majority(int LFSR1, int LFSR2, int LFSR3) {
    int sum = LFSR1 + LFSR2 + LFSR3;

    if (sum >= 2)
        return 1;
    else
        return 0;
}

// Shift LFSR and return result
int shift(int reg, int mask, int taps) {
    int t = reg & taps;
    reg = (reg << 1) & mask;
    reg |= parity(t);
    return reg;
}

// Output register values and keystream after generating keystream
void genOutput(struct Registers *reg) {
    // Reverse bits again to generate expected output
    reg->LFSR1 = reverseBits(reg->LFSR1, LFSR1_LEN);
    reg->LFSR2 = reverseBits(reg->LFSR2, LFSR2_LEN);
    reg->LFSR3 = reverseBits(reg->LFSR3, LFSR3_LEN);

    // Output requested for assignment
    printf("Keystream:\n");
    printBits(sizeof(reg->keystream), &reg->keystream);
    printf("\n");

    printf("Registers:\n");
    printf("LFSR1: ");
    printBits(sizeof(reg->LFSR1), &reg->LFSR1);

    printf("LFSR2: ");
    printBits(sizeof(reg->LFSR2), &reg->LFSR2);

    printf("LFSR3: ");
    printBits(sizeof(reg->LFSR3), &reg->LFSR3);
}

// Generate keystream using LFSRs
void genKeystream(struct Registers *reg) {
    for (int i = 0; i < ITERATIONS; i++) {
        // Get clock bits
        int LFSR1_MID = parity(reg->LFSR1 & LFSR1_CLOCK);
        int LFSR2_MID = parity(reg->LFSR2 & LFSR2_CLOCK);
        int LFSR3_MID = parity(reg->LFSR3 & LFSR3_CLOCK);

        // Do majority vote
        int maj = majority(LFSR1_MID, LFSR2_MID, LFSR3_MID);

        // If register clock bit equal to maj, do shift
        if (((reg->LFSR1 & LFSR1_CLOCK) != 0) == maj)
            reg->LFSR1 = shift(reg->LFSR1, LFSR1_MASK, LFSR1_TAPS);
        if (((reg->LFSR2 & LFSR2_CLOCK) != 0) == maj)
            reg->LFSR2 = shift(reg->LFSR2, LFSR2_MASK, LFSR2_TAPS);
        if (((reg->LFSR3 & LFSR3_CLOCK) != 0) == maj)
            reg->LFSR3 = shift(reg->LFSR3, LFSR3_MASK, LFSR3_TAPS);

        // Finally, generate stream bit
        reg->keystream <<= 1;
        reg->keystream |= parity(reg->LFSR1 & LFSR1_MSB) ^ parity(reg->LFSR2 & LFSR2_MSB) ^ parity(reg->LFSR3 & LFSR3_MSB);
    }
}

// Fill registers using given key
struct Registers * initRegisters(long key) {
    struct Registers *reg;
    reg = malloc(sizeof(struct Registers));

    reg->LFSR1 = (key >> LFSR2_LEN + LFSR3_LEN) & LFSR1_MASK;
    reg->LFSR2 = (key >> LFSR3_LEN) & LFSR2_MASK;
    reg->LFSR3 = key & LFSR3_MASK;

    // For the purpose of this assignment
    reg->LFSR1 = reverseBits(reg->LFSR1, LFSR1_LEN);
    reg->LFSR2 = reverseBits(reg->LFSR2, LFSR2_LEN);
    reg->LFSR3 = reverseBits(reg->LFSR3, LFSR3_LEN);

    return reg;
}

// Execute tests
void testHarness(char *binary) {
    long key = stringToBinary(binary);
    struct Registers *reg = initRegisters(key);

    genKeystream(reg);
    genOutput(reg);
    free(reg);
}

// Program Driver
int main(int argc, char *argv[]) {
    char *testKey = "1010101010101010101110011001100110011001111100001111000011110000";

    if (argc == 1)
        testHarness(testKey);
    else
        testHarness(argv[1]);

    return 0;
}