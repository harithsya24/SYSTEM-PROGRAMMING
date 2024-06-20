#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
     FILE *input_file = fopen(argv[1], "rb");
    if (input_file == NULL) {
        perror("Error opening the input file");
        return 1;
    }
    FILE *output_file = fopen(argv[2], "a");
    if (output_file == NULL) {
        perror("Error opening the output file");
        fclose(input_file);
        return 1;
    }
    int user_id;
    short item_id;
    char rating;
    long timestamp;
    size_t elements_read;

    while (1) {
        elements_read = fread(&user_id, sizeof(int), 1, input_file);
        if (elements_read != 1) {
            if (feof(input_file)) {
                break;
            } else {
                perror("Error reading from input file");
                fclose(input_file);
                fclose(output_file);
                return 1;
            }
        }
        elements_read = fread(&item_id, sizeof(short), 1, input_file);
        if (elements_read != 1) {
            fprintf(stderr, "Error reading from input file\n");
            fclose(input_file);
            fclose(output_file);
            return 1;
        }
        elements_read = fread(&rating, sizeof(char), 1, input_file);
        if (elements_read != 1) {
            fprintf(stderr, "Error reading from input file\n");
            fclose(input_file);
            fclose(output_file);
            return 1;
        }
        elements_read = fread(&timestamp, sizeof(long), 1, input_file);
        if (elements_read != 1) {
            fprintf(stderr, "Error reading from input file\n");
            fclose(input_file);
            fclose(output_file);
            return 1;
        }
        fprintf(output_file, "%d%hd%c%ld\n", user_id, item_id, rating, timestamp);
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}
