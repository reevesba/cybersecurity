/*
 * Steganography Make
 * 
 * About: Insert info into BMP image file.
 * Author: Bradley Reeves
 * Date: 04/11/2021
 * 
 * Code adapted from Chapter 5 of Information Security: Principles and
 * Practice (2nd Edition) by Mark Stamp (http://www.cs.sjsu.edu/~stamp/infosec/)
 */

#include "stego.h"

// Create new BMP and prepare for embedding
void preprocessBMP(FILE *in, FILE *out, char *fnameIn, uint32_t dataBytes, uint32_t *imageBytesWritten) {
    uint32_t form = 0xa5;
    char temp;

    // Skip first START_FROM bytes of image file
    for (uint32_t i = 0; i < START_FROM; i++) {
        if (fscanf(in, "%c", &temp) != 1) {
            fprintf(stderr, "Error in file %s\n", fnameIn);
            exit(0);
        }
        fprintf(out, "%c", temp);
        (*imageBytesWritten)++;
    }

    /*
     * Insert 64 bits of the form
     * 0xa5 to indicate that the file
     * contain stego data.
     */
    for (uint32_t i = 0; i < 8; i++) {
        for (uint32_t j = 0; j < 8; j++) {
            if (fscanf(in, "%c", &temp) != 1) {
                fprintf(stderr, "Error in file %s\n", fnameIn);
                exit(0);
            }
            temp = (temp & 0xfe) ^ ((form >> j) & 0x1);
            fprintf(out, "%c", temp);
            (*imageBytesWritten)++;
        }
    }

    // Insert bits of the number dataBytes (27 bits)
    for (uint32_t i = 0; i < 27; i++) {
        if (fscanf(in, "%c", &temp) != 1) {
            fprintf(stderr, "Error in file %s\n", fnameIn);
            exit(0);
        }
        temp = (temp & 0xfe) ^ ((dataBytes >> i) & 0x1);
        fprintf(out, "%c", temp);
        (*imageBytesWritten)++;
    }
}

// Embed input data in BMP image
void embedBMP(FILE *inData, FILE *in, FILE *out, char *fnameData, uint32_t dataBytes, uint32_t *imageBytesWritten, uint32_t *dataBytesWritten) {
    uint32_t moreData, moreImage, shift;
    char temp, data;

    // Read first byte of data
    if (fscanf(inData, "%c", &data) != 1) {
        fprintf(stderr, "File %s is empty\n", fnameData);
        exit(0);
    }
    
    moreImage = 1;
    shift = 0;
    
    while (moreImage) {
        if (fscanf(in, "%c", &temp) != 1) {
            moreImage = 0;
        } else {
            if ((*dataBytesWritten) < dataBytes) {
                temp = (temp & 0xfe) ^ ((data >> shift) & 0x1);
                shift = (shift + 1) & 0x7;
            
                if (shift == 0) {
                    (*dataBytesWritten)++;

                    if (fscanf(inData, "%c", &data) != 1)
                        moreData = 0;
                }
            }
            fprintf(out, "%c", temp);
            (*imageBytesWritten)++;
        }
    }
    if (moreData)
        printf("    Warning: entire data not inserted into image.  \n");
}

// Program driver
uint32_t main(int argc, const char *argv[]) {
    FILE *in, *inData, *out;
    char fnameIn[80], fnameData[80], fnameOut[80];
    uint32_t imageBytes, dataBytes, dataBytesWritten, imageBytesWritten;

    about();

    // Ensure all parameters are provided
    if (argc != 4) {
        fprintf(stderr, "===================================================================\n");
        fprintf(stderr, "        Usage:  %s inputImage outputImage inputFile                \n", argv[0]);
        fprintf(stderr, "   inputImage:  filename containing initial image                  \n");
        fprintf(stderr, "  outputImage:  filename for image containing stego data           \n");
        fprintf(stderr, "    inputFile:  filename for data to insert into outputImage file  \n");
        fprintf(stderr, "===================================================================\n");
        exit(0);
    }
    
    // Read in the filenames
    sprintf(fnameIn, "%s", argv[1]);
    sprintf(fnameOut, "%s", argv[2]);
    sprintf(fnameData, "%s", argv[3]);

    // Count input image bytes for capacity calculation
    in = openFile(fnameIn, "r");
    imageBytes = countBytes(in);
    fclose(in);
    
    printf("=================== Stego Stats ===================\n");
    printf("    Original Image Size: %d B                      \n", imageBytes);
    printf("     Embedding Capacity: %d B                      \n", imageBytes >> 3);
    
    // Reopen original image file
    in = openFile(fnameIn, "r");

    // Count data file bytes
    inData = openFile(fnameData, "r");
    dataBytes = countBytes(inData);
    fclose(inData);
    printf("         Data File Size: %d B                      \n", dataBytes);
    
    // Reopen data file
    inData = openFile(fnameData, "r");

    // Ensure original image is large enough for embedding
    if ((imageBytes - START_FROM - 27 - 64) <= 0) {
        fprintf(stderr, "Error: image file %s too small\n", fnameIn);
        exit(0);
    }
    
    // Ensure data fits in image
    if ((dataBytes << 3) >= (imageBytes - START_FROM - 27 - 64)) {
        fprintf(stderr, "Error: %s too large for %s\n", fnameData, fnameIn);
        exit(0);
    }

    // Ensure data is not too large
    if (dataBytes > (1 << 27)) {
        fprintf(stderr, "Error: %s too large (max size is %d)\n", fnameData, (1 << 27));
        exit(0);
    }

    // Ensure stego image file can be opened and written to
    out = openFile(fnameOut, "w");

    // Execute embedding procedures
    imageBytesWritten = 0;
    dataBytesWritten = 0;
    preprocessBMP(in, out, fnameIn, dataBytes, &imageBytesWritten);
    embedBMP(inData, in, out, fnameData, dataBytes, &imageBytesWritten, &dataBytesWritten);
    
    // Display final output
    printf("          Image Written: %d B                       \n", imageBytesWritten);
    printf("           Data Written: %d B                        \n", dataBytesWritten);
    printf("===================================================\n");

    // Close all files
    fclose(in);
    fclose(out);
    fclose(inData);

    return 0;
}
