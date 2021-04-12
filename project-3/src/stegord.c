/*
 * Steganography Read
 * 
 * About: Read embedded data from a BMP image file.
 * Author: Bradley Reeves
 * Date: 04/11/2021
 * 
 * Code adapted from Chapter 5 of Information Security: Principles and
 * Practice (2nd Edition) by Mark Stamp (http://www.cs.sjsu.edu/~stamp/infosec/)
 */

#include "stego.h"

// Read the input image
uint32_t readBMP(FILE *in, char *fnameIn) {
    uint32_t form, bytesIn;
    char temp;

    // Skip first START_FROM bytes of image file
    for (uint32_t i = 0; i < START_FROM; i++) {
        if (fscanf(in, "%c", &temp) != 1) {
            fprintf(stderr, "Error in file %s.\n", fnameIn);
            exit(0);
        }
    }

    /*
     * Read 64 bits of the file.
     * If not of the form 0xa5, then
     * file does not contain stego data.
     */
    for (uint32_t i = 0; i < 8; i++) {
        form = 0x0;
        for (uint32_t j = 0; j < 8; j++) {
            if (fscanf(in, "%c", &temp) != 1) {
                fprintf(stderr, "Error in file %s.\n", fnameIn);
                exit(0);
            }
            form ^= ((temp & 0x1) << j);
        }

        if (form != 0xa5) {
            fprintf(stderr, "Error: file does not contain stego data that I can read.\n");
            exit(0);
        }
    }

    bytesIn = 0;
    for (uint32_t i = 0; i < 27; i++) {
        if (fscanf(in, "%c", &temp) != 1) {
            fprintf(stderr, "Error in file %s.\n", fnameIn);
            exit(0);
        }
        bytesIn ^= ((temp & 0x1) << i);
    }
    printf("Bytes Read: %d\n", bytesIn);
    return bytesIn;
}

// Write embedded message to file
void writeMessage(FILE *out, FILE *in, char *fnameIn, uint32_t bytesIn) {
    uint32_t shift, bytesOut;
    char temp, data;

    shift = 0, bytesOut = 0, data = 0;

    for (uint32_t i = 0; i < (bytesIn << 3); i++) {
        if (fscanf(in, "%c", &temp) != 1) {
            fprintf(stderr, "Error in file %s.\n", fnameIn);
            exit(0);
        }
            
        data = data ^ ((temp & 0x1) << shift);            
        shift++;

        if (shift == 8) {    
            fprintf(out, "%c", data);
            bytesOut++;
            data = 0;
            shift = 0;         
        }
    }
    printf("Bytes Written: %d\n", bytesOut);
}

// Program driver
uint32_t main(uint32_t argc, const char *argv[]) {
    FILE *in, *out;
    char fnameIn[80], fnameOut[80];
    uint32_t bytesIn;

    about();

    // Ensure all parameters are provided
    if (argc != 3) {
        fprintf(stderr, "============================================================\n");
        fprintf(stderr, "        Usage:  %s inputFile outputFile                     \n", argv[0]);
        fprintf(stderr, "    inputFile:  filename for image containing stego data    \n");
        fprintf(stderr, "   outputFile:  filename for storing plaintext stego data   \n");
        fprintf(stderr, "============================================================\n");
        exit(0);
    }
    
    // Read in the filenames
    sprintf(fnameIn, "%s", argv[1]);
    sprintf(fnameOut, "%s", argv[2]);

    // Ensure image can be opened and read
    in = openFile(fnameIn, "r"); 
    
    // Ensure pdf can be opened and written to
    out = openFile(fnameOut, "w");

    // Create the pdf extracted from the image
    bytesIn = readBMP(in, fnameIn);
    writeMessage(out, in, fnameIn, bytesIn);

    // Close all files
    fclose(in);
    fclose(out);

    return 0;
}
