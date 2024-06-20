#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int itemId;
    long offset; 
} MovieInfo;

int main(int argc, char *argv[]) {
    FILE *data_file = fopen(argv[1], "r");
    if (data_file == NULL) {
        perror("Error opening data file");
        return 1;
    }

    FILE *item_file = fopen(argv[2], "r");
    if (item_file == NULL) {
        perror("Error opening item file");
        fclose(data_file);
        return 1;
    }

    FILE *output_file = fopen(argv[3], "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(data_file);
        fclose(item_file);
        return 1;
    }

    char *line = NULL; 
    size_t line_length = 0; 

    MovieInfo *movieIndex = NULL;
    int numItems = 0;
    long offset = 0;

    while (getline(&line, &line_length, item_file) != -1) { 
        movieIndex = realloc(movieIndex, (numItems + 1) * sizeof(MovieInfo));
        if (movieIndex == NULL) {
            perror("Memory allocation error");
            fclose(data_file);
            fclose(item_file);
            fclose(output_file);
            free(line); 
            return 1;
        }
        sscanf(line, "%d", &movieIndex[numItems].itemId);
        movieIndex[numItems].offset = offset; 
        offset = ftell(item_file); 
        numItems++;
    }
    rewind(item_file);

    int userId, rating;
    long timestamp;
    long itemOffset;

    while (fscanf(data_file, "%d%*d%d%ld", &userId, &rating, &timestamp) == 3) {
        itemOffset = -1;
        for (int i = 0; i < numItems; i++) {
            if (userId == movieIndex[i].itemId) {
                itemOffset = movieIndex[i].offset;
                break;
            }
        }

        if (itemOffset == -1) {
            fprintf(stderr, "Item ID not found: %d\n", userId);
            continue;
        }

        fprintf(output_file, "%d %ld %d %ld\n", userId, itemOffset, rating, timestamp);
    }

    free(movieIndex);
    free(line); 
    fclose(data_file);
    fclose(item_file);
    fclose(output_file);

    return 0;
}
