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

Image top;
Image bottom;
Image target;

int main(int argc, char **argv) {
    read(argv[1], &top);
    read(argv[2], &bottom);

    // String代入
    for (int i = 0; i < 1000; i++) {
        target.pgmType[i] = top.pgmType[i];
    }

    target.width = top.width > bottom.width ? top.width : bottom.width;
    target.height = top.height + bottom.height;
    target.maxValue = top.maxValue;

    for (int y = 0; y < top.height; y++) {
        for (int x = 0; x < target.width; x++) {
            target.pixels[x][y] = top.width > x ? top.pixels[x][y] : 0;
        }
    }
    for (int y = 0; y < bottom.height; y++) {
        for (int x = 0; x < target.width; x++) {
            target.pixels[x][y + top.height] = bottom.width > x ? bottom.pixels[x][y] : 0;
        }
    }

    write(argv[3], &target);

    return 0;
}