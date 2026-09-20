#include "barcode.h"
#include "loader.h"
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv){
    // TODO: parse the arguments in argv. 
    // You can expect argv[1] to be the digits to encode
    // You can expect argv[2] to be the integer width
    // You can expect argv[3] to be the integer height
    // You can expect argv[4] to be the output filepath.

    if(argc != 5) {
        printf("Incorrect number of arguments. Expected: ./build/image_calc <barcode_value> <width> <height> <output_image_path>\n");
        return -1;
    }

    char* barcode_value = argv[1];
    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    char* output_filepath = argv[4];
    if (width <= 0 || height <= 0) {
        printf("Error: Width and height must be positive.\n");
        return -1;
    }
    struct image* output_image = barcode(barcode_value, width, height);
    if (output_image == NULL) {
        printf("Error: Could not create image.\n");
        return -1;
    }
    int result = saveimage(output_filepath, output_image);
    free(output_image->pixels);
    free(output_image);
    
    return result;
}
