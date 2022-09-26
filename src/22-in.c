#include <stdio.h>
#include <stdlib.h>

#define SIZE 2000

typedef struct image {
    char pgmType[1000];
    int width;
    int height;
    int maxValue;
    int pixels[SIZE][SIZE];
} Image;

void read(char* filename, Image* image) {
    FILE *file = fopen(filename, "r");
    fscanf(file, "%s", image->pgmType);
    fscanf(file, "%d %d", &image->width, &image->height);
    fscanf(file, "%d", &image->maxValue);
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            fscanf(file, "%d", &image->pixels[x][y]);
        }
    }
    fclose(file);
}

void write(char* filename, struct image* writeImage) {
    FILE *file = fopen(filename, "w");
    if(file == NULL){
        perror(filename);
        exit(1);
    }
    fprintf(file, "%s\n", writeImage->pgmType);
    fprintf(file, "%d %d\n", writeImage->width, writeImage->height);
    fprintf(file, "%d\n", writeImage->maxValue);
    for (int y = 0; y < writeImage->height; y++) {
        for (int x = 0; x < writeImage->width; x++) {
            fprintf(file, "%d ", writeImage->pixels[x][y]);
        }
    }
    fclose(file);
}

Image bigger;
Image smaller;
Image target;

int main(int argc, char **argv) {
    read(argv[1], &bigger);
    read(argv[2], &smaller);

    if (bigger.width < smaller.width) {
        Image *copy = &bigger;
        bigger = smaller;
        smaller = *copy;
    }

    target.width = bigger.width;
    target.height = bigger.height;
    target.maxValue = bigger.maxValue;
    for (int i = 0; i < 1000; i++) {
        target.pgmType[i] = bigger.pgmType[i];
    }

    int smallFromWidth = (bigger.width - smaller.width) / 2;
    int smallToWidth = smallFromWidth + smaller.width;
    int smallFromHeight = (bigger.height - smaller.height) / 2;
    int smallToHeight = smallFromHeight + smaller.height;

    for (int y = 0; y < target.height; y++) {
        for (int x = 0; x < target.width; x++) {
            if (smallFromWidth <= x && x < smallToWidth && smallFromHeight <= y && y < smallToHeight) {
                target.pixels[x][y] = smaller.pixels[x - smallFromWidth][y - smallFromHeight];
            } else {
                target.pixels[x][y] = bigger.pixels[x][y];
            }
        }
    }

    write(argv[3], &target);

    return 0;
}