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

Image left;
Image right;
Image target;

int main(int argc, char **argv) {
    read(argv[1], &left);
    read(argv[2], &right);

    for (int i = 0; i < 1000; i++) {
        target.pgmType[i] = left.pgmType[i];
    }

    target.width = left.width + right.width;
    target.height = left.height > right.height ? left.height : right.height;
    target.maxValue = left.maxValue;

    for (int y = 0; y < target.height; y++) {
        for (int x = 0; x < left.width; x++) {
            target.pixels[x][y] = left.height > y ? left.pixels[x][y] : 255;
        }
        for (int x = 0; x < right.width; x++) {
            target.pixels[x + left.width][y] = right.height > y ?right.pixels[x][y] : 255;
        }
    }

    write(argv[3], &target);

    return 0;
}