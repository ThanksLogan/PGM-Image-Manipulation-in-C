# C Project: Image Processing with PGM Files

## Overview
This project involves manipulating PGM (Portable GrayMap) images using C. The program reads a PGM file, processes the image to perform thresholding and rotation operations, and then writes the modified images back to PGM files.

## How it looks: 

![image](https://github.com/ThanksLogan/PGM-Image-Manipulation-in-C/assets/89110766/1cc794e1-63b5-48bf-869c-827dacab5d20)

![image](https://github.com/ThanksLogan/PGM-Image-Manipulation-in-C/assets/89110766/d4c70fad-da32-41fa-8136-7621d5bf30e0)

![image](https://github.com/ThanksLogan/PGM-Image-Manipulation-in-C/assets/89110766/0ad13a58-6fed-439b-865a-ff943e70e725)


## Getting Started

### Prerequisites
- A C compiler (like GCC)
- A PGM image file for processing

### Installation
1. Clone or download this repository to your local machine.
2. Place your PGM image file in the same directory as the C code.

### Running the Program
1. Compile the C code using a C compiler. Example using GCC: `gcc -o image_processor image_processor.c`
2. Run the compiled program: `./image_processor`
3. The program will generate processed images in the same directory.

## Code Description

### `image_processor.c`
- **Main Functions**:
  - `readPGM()`: Reads a PGM image file and stores it in a 2D array.
  - `writePGM()`: Writes a 2D array of pixel data to a PGM file.
  - `threshold()`: Applies thresholding to the image.
  - `rotate()`: Rotates the image by performing a matrix transpose.
- **Challenges Faced**: 
  - Getting accustomed to C syntax.
  - Understanding pointers and memory allocation.
  - Deciding on appropriate file reading and writing methods.
  - Debugging issues related to memory management.

### Processed Images
- The program generates the following images:
  - `rotate.pgm`: Image after one rotation.
  - `threshold.pgm`: Image after applying thresholding.
  - `rotate_again.pgm`: Image after a second rotation.

## Project Development
- Initial challenges included adapting to the C language syntax and understanding structs.
- The project involved choices regarding file I/O operations and pointer notation.
- Memory allocation and error handling were crucial parts of the development.
- A significant bug related to memory deallocation was identified and resolved.

## Rotating the Image
- The rotation is not a conventional 90-degree turn but rather a matrix transpose.
- This results in the image being mirrored and rotated, as evident from the output images.

## Acknowledgments
- Utilized C language documentation, particularly for file I/O operations, from sources like [Tutorialspoint](https://www.tutorialspoint.com/c_standard_library/c_function_fopen.htm).
