/*
 * About: TEA Utilites
 * Author: Bradley Reeves
 * Date: 03/31/2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "tealib.h"

// Convert hex integer to hex string
char * htohs(uint32_t *hex, int block) {
    char *output = malloc(sizeof(uint32_t)*block);
    char *temp = output;

    for (int i = 0; i < block; i++) {
        char * temp = malloc(sizeof(uint32_t));
        sprintf(temp, "%X", hex[i]);
        strcat(output, temp);
    }
    return output;
}

// Convert ASCII string to hex string
char * atoh(char *str) {
    int length = strlen(str);
    char *hex = malloc(length*2);

    for (int i = 0, j = 0; i < length; i++, j += 2)
      sprintf(hex + j, "%02x", str[i] & 0xff);

    return hex;
}

// Convert hex string to ASCII string
char * htoa(char *str) {
    int length = strlen(str);
    char *text = malloc(length);

    for (int i = 0, j = 0; j < length; i++, j += 2) {
      int val[1];
      sscanf(str + j, "%2x", val);
      text[i] = val[0];
      text[i + 1] = '\0';
    }
    return text;
}

// Substring from position to postition + length
char * substring(char *str, int position, int length) {
    char *p = malloc(length + 1);

    for (int i = 0; i < length; i++)
      *(p + i) = *(str++ + position);

    *(p + (length)) = '\0';
    return p;
}

// Generate random 32 bit integer
uint32_t rand32() {
    uint32_t iv;
    iv = rand() & 0xff;
    iv |= (rand() & 0xff) << 8;
    iv |= (rand() & 0xff) << 16;
    iv |= (rand() & 0xff) << 24;
    return iv;
}

// Initial output to terminal
void about() {
    printf("   _____________________________       \n");
    printf(" / \\                            \\    \n");
    printf("|   |           / | Tiny        |      \n");
    printf(" \\_ |          /  | Encryption  |     \n");
    printf("    |      .  /   | Algorithm   |      \n");
    printf("    |     / \\/    |             |     \n");
    printf("    |    /   \\    | v1.0        |     \n");
    printf("    |   /    /   _|_            |      \n");
    printf("    |   \\   /   /\\ /\\           |   \n");
    printf("    |    \\ /   /__v__\\          |    \n");
    printf("    |     '   |       |         |      \n");
    printf("    |         |     .#|         |      \n");
    printf("    |         |#.  .##|         |      \n");
    printf("    |         |#######|         |      \n");
    printf("    |         |#######|         |      \n");
    printf("    |   ________________________|___   \n");
    printf("    |  /                           /   \n");
    printf("    \\_/___________________________/   \n");
    printf("                                       \n");
}