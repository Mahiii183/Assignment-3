#include "barcode.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct image* barcode(char* data, int width, int height) {
    (void)data;
    if (width <= 0 || height <= 0) {
        return NULL;
    }
    if ((size_t)width > SIZE_MAX / (size_t)height ||
        (size_t)width * (size_t)height >
            SIZE_MAX / sizeof(struct pixel)) {
        return NULL;
    }
    struct image* img = malloc(sizeof(struct image));

    if (img == NULL) {
        return NULL;
    }
    img->width = width;
    img->height = height;
    size_t total_pixels = (size_t)width * (size_t)height;
    img->pixels = malloc(total_pixels * sizeof(struct pixel));
    if (img->pixels == NULL) {
        free(img);
        return NULL;
    }
    for (size_t i = 0; i < total_pixels; i++) {
        img->pixels[i].r = 255;
        img->pixels[i].g = 255;
        img->pixels[i].b = 255;
    }

    return img;
}

