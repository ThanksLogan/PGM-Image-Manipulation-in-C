/*
 * Author: Logan Foreman
 * REDID: 825056655
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
// Structure to hold grayscale pixel data
typedef struct {
    unsigned char value;
} PixelGray;

// Function to read a PGM image into a 2D array
PixelGray** readPGM(const char* filename, int* width, int* height);

// Function to write a 2D matrix as a PGM image
void writePGM(const char* filename, PixelGray** matrix, int* width, int* height);

// Function to threshold the image matrix
PixelGray** threshold(PixelGray** matrix, int* width, int* height);

// Function to rotate the image matrix
PixelGray** rotate(PixelGray** matrix, int* width, int* height);

//main function - DO NOT MODIFY
int main() {
    int width, height; // variable to hold width and height. Use reference in other functions
    PixelGray** image_original = readPGM("lenna_p5.pgm", &width, &height);
// Now you have the grayscale image data in the 'image_original' 2D array
// Access pixel data using image[row][col].value
// For example, to access the pixel at row=2, col=3:
// unsigned char pixel_value = image[2][3].value;
// Create a new 2D array 'image_thresh' to store the threshold image
    PixelGray** image_thresh = threshold(image_original, &width, &height);
//write the image data as "threshold.pgm"
    writePGM("threshold.pgm", image_thresh, &width, &height);
// Create a new 2D array 'image_rotate' to store the rotated image
    PixelGray** image_rotate = rotate(image_original, &width, &height);
//write the image data as "rotate.pgm"
    writePGM("rotate.pgm", image_rotate, &width, &height);
    image_rotate = rotate(image_rotate, &width, &height);
//write the image data as "rotate_again.pgm"
    writePGM("rotate_again.pgm", image_rotate, &width, &height);
// Free the allocated memory when you're done
    for (int i = 0; i < height; ++i) {
        free(image_original[i]);
        free(image_thresh[i]);
        free(image_rotate[i]);
    }
    free(image_original);
    free(image_thresh);
    free(image_rotate);
    return 0;
}

// Function to read a PGM image into a 2D array
/*
a. This function should open the file with provided file name.
b. Handle errors!
c. Get the dimensions of the image.
d. Dynamically allocate the storage (2D matrix) for the image dimension.
e. Read from the file and fill the 2D matrix.
f. Close the file.
g. Return the 2D matrix
 */
PixelGray** readPGM(const char* filename, int* width, int* height){

    // Opens the file for reading in binary
    FILE * file = NULL;
    file = fopen(filename, "rb");
    // Handles error when opening the file
    if (file == NULL) {
        perror("Failed to Open The PGM File");
        exit(1); //returns 1 rn but we can change to another code number
    }

    char magic[3];
    int max_val;
    //char comment[24];

    // Read and validate the first line (magic)
    if (fscanf(file, "%2s", magic) != 1 || magic[0] != 'P' || magic[1] != '5') {
        printf("Not a valid P5 PGM file\n");
        fclose(file);
        exit(1);
    }

    // Skip the rest of the first line
    while (fgetc(file) != '\n');

    // Read width, height, and max value from the third line
    if (fscanf(file, "%d %d\n%d", width, height, &max_val) != 3) {
        printf("Error reading width, height, and max value\n");
        fclose(file);
        exit(1);
    }
    while (fgetc(file) != '\n');

    // Now, magic, comment, width, height, and max_val contain the header information
    printf("Magic: %s\n", magic);
    //printf("Comment: %s\n", comment);
    printf("Width: %d\n", *width);
    printf("Height: %d\n", *height);
    printf("Max Value: %d\n", max_val);

    PixelGray **matrix = (PixelGray **)malloc((size_t) *height * sizeof(PixelGray *));
    if (matrix == NULL) {
        perror("Memory allocation failed(rows)");
        exit(1);
    }

    for (int i = 0; i < *height; i++) {
        matrix[i] = (PixelGray *)malloc((size_t) *width * sizeof(PixelGray));
        //printf("allocated memory for %d %d", i, height);
        if (matrix[i] == NULL) {
            //printf("%d", i);
            perror("Memory allocation failed(columns)");
            // Free previously allocated rows
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }

            // Free the top-level pointer
            free(matrix);
            exit(1);
        }
    }
    //printf("We made it: %d %d", *width, *height);
    // Read pixel data
    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            //int pixel;
            /*
            if (fscanf(file, "%d", &pixel) != 1) {
                printf("Error reading pixel data\n");
                fclose(file);
                exit(1);
            }
            */
            //            if (fread(&pixel, 1, 1, file) != 1) { //100000000
            //sizeof(unsigned char) for size parameter but dont need cus always reading 1 byte
            if (fread(&matrix[i][j].value, 1, 1, file) != 1) { //10001000
                if (feof(file)) {
                    printf("End of file reached while reading pixel data\n");
                } else if (ferror(file)) {
                    perror("Error reading pixel data");
                } else {
                    printf("Unknown error reading pixel data\n");
                }
                fclose(file);
                exit(1);
            }

            //matrix[i][j].value = (unsigned char) pixel;

        }
    }

    //closes the file
    fclose(file);

    //should return the 2d array
    return matrix;
}


// Function to write a 2D matrix as a PGM image
void writePGM(const char* filename, PixelGray** matrix, int* width, int* height){
// Write the pixel data to a new PGM file
    FILE *outputFile = fopen(filename, "w"); // Open a new PGM file for writing
    if (outputFile == NULL) {
        perror("File creation failed");
        exit(1);
    }

    // Write the PGM header to the new file

    fprintf(outputFile, "P5\n%d %d\n255\n", *width, *height);

    // Write the pixel data from the 2D array to the new file as ASCII values
    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            fprintf(outputFile, "%c", matrix[i][j].value); // Write pixel value as ASCII
        }
        //fprintf(outputFile, "\n"); // Newline after each row
    }

    // Close the new file
    fclose(outputFile);

    // Free allocated memory
    /*
    for (int i = 0; i < *height; i++) {
        free(matrix[i]);
    }
    free(matrix);
*/
}

// Function to threshold the image matrix
/*
a. This function should create a new 2D matrix. Dynamically allocate the storage (2D
matrix) for the new matrix.
b. Thresholding
i. If original value > 80 -- store 255
ii. Otherwise – store 0
c. Return the new 2D matrix */
PixelGray** threshold(PixelGray** matrix, int* width, int* height){
    //we create a new matrix and allocate storage for it first.
    //then, we copy the existing matrix data to it but threshold along the way

    /*Here we are allocating memory for a new matrix called threshold*/
    PixelGray **threshold = (PixelGray **)malloc((size_t) *height * sizeof(PixelGray *));
    if (threshold == NULL) {
        perror("Memory allocation failed(rows)");
        exit(1);
    }

    for (int i = 0; i < *height; i++) {
        threshold[i] = (PixelGray *)malloc((size_t) *width * sizeof(PixelGray));
        //printf("allocated memory for %d %d", i, height);
        if (threshold[i] == NULL) {
            //printf("%d", i);
            perror("Memory allocation failed(columns)");
            // Free previously allocated rows
            for (int j = 0; j < i; j++) {
                free(threshold[j]);
            }

            // Free the top-level pointer
            free(threshold);
            exit(1);
        }
    }

    //Now that weve allocated memory for a new matrix called threshold
    //we can populate it and change the values as we go.
    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            //we grab the matrix[i][j], and copy but threshold the value
            if(matrix[i][j].value > 80){
                //printf(" _%d_ ", matrix[i][j].value);
                threshold[i][j].value = 255;
            }else{
                threshold[i][j].value = 0;
            }
        }
    }
    // Before returning, free the memory allocated for the original 'matrix'
    /*for (int i = 0; i < *height; i++) {
        free(matrix[i]);
    }
    free(matrix);
    */
    return threshold;
    //exit(20);
}

// Function to rotate the image matrix
/*
a. This function should create a new 2D matrix. Dynamically allocate the storage (2D
matrix) for the new matrix.
b. Rotate the original 2D matrix and store the result as the new matrix.
i. Rotation can be achieved by matrix transpose (swapping rows & column).
c. Return the new 2D matrix.
 */
PixelGray** rotate(PixelGray** matrix, int* width, int* height){
    PixelGray **rotate = (PixelGray **)malloc((size_t) *height * sizeof(PixelGray *));
    if (rotate == NULL) {
        perror("Memory allocation failed(rows)");
        exit(1);
    }

    for (int i = 0; i < *height; i++) {
        rotate[i] = (PixelGray *)malloc((size_t) *width * sizeof(PixelGray));
        //printf("allocated memory for %d %d", i, height);
        if (rotate[i] == NULL) {
            //printf("%d", i);
            perror("Memory allocation failed(columns)");
            // Free previously allocated rows
            for (int j = 0; j < i; j++) {
                free(rotate[j]);
            }

            // Free the top-level pointer
            free(rotate);
            exit(1);
        }
    }
    //Time to rotate the original matrix using matrix transpose: swapping rows and column values?
    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            //we grab the matrix[i][j], and copy but threshold
            //rotated matrix[row][col] will equal original [col][row]
            rotate[i][j].value = matrix[j][i].value;
        }
    }
    // Before returning, free the memory allocated for the original 'matrix'
    /*
    for (int i = 0; i < *height; i++) {
        free(matrix[i]);
    }
    free(matrix);
    */return rotate;
}
