#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }

    FILE *outputFile = fopen(argv[2], "wb");
    if (outputFile == NULL) {
        printf("Error: Unable to open output file.\n");
        fclose(inputFile);
        return 1;
    }

    int user_id;
    short item_id;
    char rating;
    long timestamp;

    while (fscanf(inputFile, "%d%hd%c%ld", &user_id, &item_id, &rating, &timestamp) == 4) {
        fwrite(&user_id, sizeof(int), 1, outputFile);
        fwrite(&item_id, sizeof(short), 1, outputFile);
        fwrite(&rating, sizeof(char), 1, outputFile);
        fwrite(&timestamp, sizeof(long), 1, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
