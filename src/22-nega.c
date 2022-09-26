#include <stdio.h>

#define WIDTH 1024
#define HEIGHT 768

int main(int argc, char **argv) {
    char pgmType[1000];
    int originImage[WIDTH][HEIGHT];
    int targetImage[WIDTH][HEIGHT];
    int imageWidth, imageHeight;
    int maxValue;

    FILE *originFile = fopen(argv[1], "r");
    fscanf(originFile, "%s", pgmType);
    fscanf(originFile, "%d %d", &imageWidth, &imageHeight);
    fscanf(originFile, "%d", &maxValue);

    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            fscanf(originFile, "%d", &originImage[x][y]);
        }
    }
    fclose(originFile);

    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            targetImage[x][y] = 255 - originImage[x][y];
        }
    }

    FILE *targetFile = fopen(argv[2], "w");
    fprintf(targetFile, "%s\n", pgmType);
    fprintf(targetFile, "%d %d\n", imageWidth, imageHeight);
    fprintf(targetFile, "%d\n", maxValue);

    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            fprintf(targetFile, "%d ", targetImage[x][y]);
        }
    }
    fclose(targetFile);

    return 0;
}