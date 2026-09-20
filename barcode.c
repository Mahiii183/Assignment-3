#include "barcode.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static const char* LEFT_CODES[10] = {
    "1110010",
    "1100110",
    "1101100",
    "1010000",
    "1011100",
    "1001110",
    "1000010",
    "1000100",
    "1001000",
    "1110100"
};


static void draw_bar(struct image* img, int x, int white) {
    int color = white ? 255 : 0;
    for (int y = 0; y < img->height; y++) {
        int index = y * img->width + x;
        img->pixels[index].r = color;
        img->pixels[index].g = color;
        img->pixels[index].b = color;
    }
}

static void draw_pattern(struct image* img,int* x, const char* pattern,int invert) {
    for (int i = 0; pattern[i] != '\0'; i++) {
        int white = pattern[i] == '1';
        if (invert) {
            white = !white;
        }
        draw_bar(img, *x, white);
        (*x)++;
    }
}

struct image* barcode(char* data, int width, int height) {
    if (width != 113 || height <= 0) {
        return NULL;
    }
    if (data == NULL || strlen(data) != 12) {
        return NULL;
    }
    for (int i = 0; i < 12; i++) {
        if (data[i] < '0' || data[i] > '9') {
            return NULL;
        }
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
    int x = 9;
    draw_pattern(img, &x, "010", 0);
    for (int i = 0; i < 6; i++) {
        int digit = data[i] - '0';
        draw_pattern(img, &x, LEFT_CODES[digit], 0);
    }

    draw_pattern(img, &x, "10101", 0);

    for (int i = 6; i < 12; i++) {

        int digit = data[i] - '0';

        draw_pattern(img, &x, LEFT_CODES[digit], 1);
    }

    draw_pattern(img, &x, "010", 0);

    return img;
}

