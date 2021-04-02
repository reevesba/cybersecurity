/*
 * About: TEA Utilities Header File
 * Author: Bradley Reeves
 * Date: 03/31/2021
 * 
 * htohs: Convert hex integer to hex string.
 * atoh: Convert ASCII string to hex string.
 * htoa: Convert hex string to ASCII string.
 * substring: Substring from position to postition + length.
 * rand32: Generate random 32 bit integer.
 * about: Initial output to terminal.
 */

#define DELTA 0x9e3779b9u
#define ROUNDS 32u
#define NIBBLES 8u
#define HEX_BASE 16u
#define KEY_BLOCKS 4u
#define ECB 0u
#define CBC 1u
#define CTR 2u

char * htohs(uint32_t *hex, int length);
char * atoh(char *str);
char * htoa(char *str);
char * substring(char *str, int position, int length);
uint32_t rand32();
void about();