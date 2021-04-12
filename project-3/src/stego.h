/*
 * About: Steganography Header File
 * Author: Bradley Reeves
 * Date: 04/12/2021
 * 
 * openFile: Open a new file and check for errors.
 * countBytes: Count file size in bytes.
 * randBit: Generate random bit.
 * about: Initial output to terminal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define START_FROM 100

FILE * openFile(char *fname, char *perm);
uint32_t countBytes(FILE *file);
uint8_t randBit();
void about();
