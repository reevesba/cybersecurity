/*
 * Steganography Destroy
 * 
 * About: Corrupts data embedded in image. Could be used for MiM.
 * Author: Bradley Reeves
 * Date: 04/11/2021
 * 
 * Code adapted from Chapter 5 of Information Security: Principles and
 * Practice (2nd Edition) by Mark Stamp (http://www.cs.sjsu.edu/~stamp/infosec/)
 */

#include "stego.h"

void stegoDestroy(FILE *in, FILE *out, char *fnameIn, uint32_t *imageBytesWritten) {
    uint32_t moreImage = 1, shift = 0;
    char temp;

    /*
     * Skip first START_FROM bytes of image file.
     * Add 64 iterations to retain form 0xa5. This
     * will make stego_read run with no errors, but
     * the output file will still be corrupted.
     */
    for (uint32_t i = 0; i < START_FROM + 64; i++) {
        if (fscanf(in, "%c", &temp) != 1) {
            fprintf(stderr, "Error in file %s\n", fnameIn);
            exit(0);
        }
        fprintf(out, "%c", temp);
        (*imageBytesWritten)++;
    }

    while (moreImage) {
        if (fscanf(in, "%c", &temp) != 1) {
            moreImage = 0;
        } else {
            // Randomly modify low order bits
            temp = (temp & 0xfe) ^ ((randBit() >> shift) & 0x1);
            shift = (shift + 1) & 0x7;
            fprintf(out, "%c", temp);
            (*imageBytesWritten)++;
        }
    }
}

// Program driver
uint32_t main(uint32_t argc, const char *argv[]) {
    FILE *in, *out;
    char fnameIn[80], fnameOut[80];
    uint32_t imageBytes, imageBytesWritten;

    about();

    // Ensure all parameters are provided
    if (argc != 3) {
        fprintf(stderr, "===================================================================\n");
        fprintf(stderr, "        Usage:  %s inputImage outputImage                          \n", argv[0]);
        fprintf(stderr, "   inputImage:  filename containing initial image with data        \n");
        fprintf(stderr, "  outputImage:  filename for image with destroyed data             \n");
        fprintf(stderr, "===================================================================\n");
        exit(0);
    }
    
    // Read in the filenames
    sprintf(fnameIn, "%s", argv[1]);
    sprintf(fnameOut, "%s", argv[2]);

    // Count input image bytes
    in = openFile(fnameIn, "r");
    imageBytes = countBytes(in);
    fclose(in);
    
    printf("=================== Stego Stats ===================\n");
    printf("    Original Image Size: %d B                      \n", imageBytes);
    
    // Reopen original image file
    in = openFile(fnameIn, "r");

    // Ensure data is not too large
    if (imageBytes > (1 << 27)) {
        fprintf(stderr, "Error: %s too large (max size is %d)\n", fnameIn, (1 << 27));
        exit(0);
    }

    // Ensure stego image file can be opened and written to
    out = openFile(fnameOut, "w");

    // Execute destruction procedure
    imageBytesWritten = 0;
    stegoDestroy(in, out, fnameIn, &imageBytesWritten);
    
    // Display final output
    printf("          Image Written: %d B                       \n", imageBytesWritten);
    printf("===================================================\n");

    // Close all files
    fclose(in);
    fclose(out);

    return 0;
}
