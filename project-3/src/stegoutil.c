/*
 * About: Steganography Utilites
 * Author: Bradley Reeves
 * Date: 04/12/2021
 */

#include "stego.h"

// Open a new file and check for errors
FILE * openFile(char *fname, char *perm) {
    FILE *file = fopen(fname, perm);
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s.\n", fname);
        exit(0);
    }
    return file;
}

// Count file size in bytes
uint32_t countBytes(FILE *file) {
    uint32_t count = 0;
    char temp;

    while (1) {
        if(fscanf(file, "%c", &temp) != 1)
            break;
        count++;
    }
    return count;
}

// Generate random bit
uint8_t randBit() {
    return rand() % 0x2;
}

// Initial output to terminal
void about() {
    printf("                                                      \n");
    printf("     _____ __                                         \n");                            
    printf("    / ___// /____  ____ _____ ________  _______       \n");
    printf("    \\__ \\/ __/ _ \\/ __ `/ __ `/ ___/ / / / ___/    \n");
    printf("   ___/ / /_/  __/ /_/ / /_/ (__  ) /_/ (__  )        \n");
    printf("  /____/\\__/\\___/\\__, /\\__,_/____/\\__,_/____/    \n");
    printf("                /____/                v1.0            \n");                  
    printf("                                                      \n");
}