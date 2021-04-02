/*
 * About: TEA Driver
 * Author: Bradley Reeves
 * Date: 03/31/2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "tealib.h"

// Encrypt plaintext
void encrypt(const uint32_t *key, uint32_t *data) {
    uint32_t L = data[0], R = data[1];
    uint32_t k0 = key[0], k1 = key[1], k2 = key[2], k3 = key[3];
    uint32_t sum = 0;

    for (int i = 0; i < ROUNDS; i++) {
        sum += DELTA;
        L += ((R << 4) + k0) ^ (R + sum) ^ ((R >> 5) + k1);
        R += ((L << 4) + k2) ^ (L + sum) ^ ((L >> 5) + k3);
    }
    data[0] = L;
    data[1] = R;
}

// Decrypt ciphertext
void decrypt(const uint32_t *key, uint32_t *data) {
    uint32_t L = data[0], R = data[1];
    uint32_t k0 = key[0], k1 = key[1], k2 = key[2], k3 = key[3];
    uint32_t sum = DELTA << 5;

    for (int i = 0; i < ROUNDS; i++) {
        R -= ((L << 4) + k2) ^ (L + sum) ^ ((L >> 5) + k3);
        L -= ((R << 4) + k0) ^ (R + sum) ^ ((R >> 5) + k1);
        sum -= DELTA;
    }
    data[0] = L;
    data[1] = R;
}

// Electronic Codebook Mode: Encrypt
void ecbEncrypt(const uint32_t *key, uint32_t *data, int blocks) {
    for (int i = 0; i < blocks; i += 2)
        encrypt(key, &data[i]);
}

// Electronic Codebook Mode: Decrypt
void ecbDecrypt(const uint32_t *key, uint32_t *data, int blocks) {
    for (int i = 0; i < blocks; i += 2)
        decrypt(key, &data[i]);
}

// Cipher Block Chaining Mode: Encrypt
void cbcEncrypt(const uint32_t *key, uint32_t *data, int blocks, uint32_t *iv) {
    uint32_t mask[2];
    mask[0] = iv[0], mask[1] = iv[1];

    for (int i = 0; i < blocks; i += 2) {
        // XOR plaintext with mask
        data[i] ^= mask[0];
        data[i + 1] ^= mask[1];

        // Encrypt current block
        encrypt(key, &data[i]);

        // Update mask for next cycle
        mask[0] = data[i];
        mask[1] = data[i + 1];
    }
}

// Cipher Block Chaining Mode: Decrypt
void cbcDecrypt(const uint32_t *key, uint32_t *data, int blocks, uint32_t *iv) {
    uint32_t mask[2];
    mask[0] = iv[0], mask[1] = iv[1];

    // Mask requires unaltered ciphertext
    uint32_t *ciphertext = malloc(sizeof(uint32_t)*blocks);
    memcpy(ciphertext, data, sizeof(uint32_t)*blocks);

    for (int i = 0; i < blocks; i += 2) {
        // Decrypt current block
        decrypt(key, &data[i]);

        // XOR decrypted data with mask
        data[i] ^= mask[0];
        data[i + 1] ^= mask[1];

        // Update mask for next cycle
        mask[0] = ciphertext[i];
        mask[1] = ciphertext[i + 1];
    }
    free(ciphertext);
}

// Counter Mode: Encrypt and Decrypt
void ctrCipher(const uint32_t *key, uint32_t *data, int blocks, uint32_t *iv) {
    uint32_t mask[2];
    mask[0] = iv[0], mask[1] = iv[1];

    uint64_t ivTemp = (uint64_t) mask[0] << 32 | mask[1]; 

    for (int i = 0; i < blocks; i++) {
        /*
         * Works like stream cipher, so you can use the
         * same function for encrypt/decrypt. Either
         * fuction works here.
         */
        encrypt(key, mask);

        // XOR data with mask
        data[i] ^= mask[0];
        data[i + 1] ^= mask[1];

        // update initialization vector and mask
        ivTemp++;
        mask[0] = (uint32_t) (ivTemp >> 32);
        mask[1] = (uint32_t) ivTemp;
    }
}

// Convert hex string to 32 bit integer blocks
uint32_t * chunk(char *str, int blocks) {
    uint32_t *hex = malloc(sizeof(uint32_t)*blocks);
    char *substr;

    for (int i = 0; i < blocks; i++) {
        // 8 nibbles = 32 bits
        substr = substring(str, i*NIBBLES, NIBBLES);
        hex[i] = (uint32_t) strtoul(substr, NULL, HEX_BASE);
        free(substr);
    }
    return hex;
}

void executeMode(uint32_t *key, uint32_t *msg, int blocks, uint32_t *iv, int mode, bool isHex) {
    // Leave original message unaltered
    uint32_t *msgcpy = malloc(sizeof(uint32_t)*blocks);
    memcpy(msgcpy, msg, sizeof(uint32_t)*blocks);

    // Encrypting message
    switch (mode) {
        case ECB:
            printf("Electronic Codebook Mode:\n");
            ecbEncrypt(key, msgcpy, blocks);
            break;
        case CBC:
            printf("Cipher Block Chaining Mode:\n");
            cbcEncrypt(key, msgcpy, blocks, iv);
            break;
        case CTR:
            printf("Counter Mode:\n");
            ctrCipher(key, msgcpy, blocks, iv);
    }

    printf("Encrypted Message: %s\n", htohs(msgcpy, blocks));

    // Decrypting message
    switch (mode) {
        case ECB:
            ecbDecrypt(key, msgcpy, blocks);
            break;
        case CBC:
            cbcDecrypt(key, msgcpy, blocks, iv);
            break;
        case CTR:
            ctrCipher(key, msgcpy, blocks, iv);
    }

    if (isHex)
        printf("Decrypted Message: 0x%s\n\n", htohs(msgcpy, blocks));
    else
        printf("Decrypted Message: %s\n\n", htoa(htohs(msgcpy, blocks)));

    free(msgcpy);
}

// Execute Tests
void testHarness(char *keystr, char *msgstr) {
    bool isHex = false;

    printf("Input: %s\n\n", msgstr);

    // Preprocessing
    if (keystr[0] == '0' && keystr[1] == 'x')
        keystr = substring(keystr, 2, strlen(keystr));

    if (msgstr[0] == '0' && msgstr[1] == 'x') {
        msgstr = substring(msgstr, 2, strlen(msgstr));
        isHex = true;
    }

    if (!isHex)
        msgstr = atoh(msgstr);

    // Setup key and message data
    int blocks = strlen(msgstr)/NIBBLES;
    uint32_t *key = chunk(keystr, KEY_BLOCKS);
    uint32_t *msg = chunk(msgstr, blocks);

    // For cbc/ctr mode, need initialization vector
    uint32_t *iv = malloc(sizeof(uint32_t)*2);
    iv[0] = rand32();
    iv[1] = rand32();

    executeMode(key, msg, blocks, NULL, ECB, isHex);
    executeMode(key, msg, blocks, iv, CBC, isHex);
    executeMode(key, msg, blocks, iv, CTR, isHex);

    free(key);
    free(msg);
    free(iv);
}

// Program Driver
int main(int argc, char *argv[]) {
    char *testKey = "0xA56BABCD00000000FFFFFFFFABCDEF01";
    char *test1 = "0x0123456789ABCDEF";
    char *test2 = "Privacy – like eating and breathing – is one of life’s basic requirements.";

    about();
    srand(time(NULL));

    if (argc == 1) {
        testHarness(testKey, test1);
        testHarness(testKey, test2);
    } else {
        testHarness(testKey, argv[1]);
    }

    return 0;
}