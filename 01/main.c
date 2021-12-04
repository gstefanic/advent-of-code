#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string_utils.h>

void first_part(FILE* f) {
    char* line = NULL;
    size_t size;
    int depth_increased_count = 0;
    long long previous_depth = -1;
    long long current_depth = 0;
    while (getline(&line, &size, f) != -1) {
        trim(line);
        current_depth = strtol(line, NULL, 10);
        if (previous_depth >= 0 && current_depth > previous_depth) {
            ++depth_increased_count;
        }
        previous_depth = current_depth;
    }
    printf("%d\n", depth_increased_count);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        perror("No input file.\n");
        exit(1);
    }
    char* input_file_path = argv[1];
    FILE* f = fopen(input_file_path, "r");
    if (f == NULL) {
        perror("Couldn't open file.\n");
        exit(1);
    }

    first_part(f);

    if (fclose(f) != 0) {
        perror("Couldn't close file.\n");
    }
    return 0;
}