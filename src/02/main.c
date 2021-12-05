#include <io.h>
#include <string_utils.h>

void first_star(char* input_file_path) {
    FILE* f = fopen(input_file_path, "r");
    if (f == NULL) {
        perror("Couldn't open file.\n");
        exit(1);
    }

    char* line = NULL;
    size_t size;
    char cmd[16] = { '\0' };
    int magnitude = -1;
    int coordinates[2]; // [x, y]
    coordinates[0] = coordinates[1] = 0;
    while (getline(&line, &size, f) != -1) {
        trim(line);
        if (sscanf(line, "%s %d", cmd, &magnitude) != 0) {
            if (strcmp(cmd, "forward") == 0) {
                coordinates[0] += magnitude;
            }
            else if (strcmp(cmd, "down") == 0) {
                coordinates[1] += magnitude;
            }
            else if (strcmp(cmd, "up") == 0) {
                coordinates[1] -= magnitude;
            }
            else {
                printf("error: Wrong command. cmd: '%s', line: '%s'\n", cmd, line);
                exit(1);
            }
        } else {
            printf("error: Wrong line format. line: '%s', cmd: '%s', %d\n", line, cmd, magnitude);
            exit(1);
        }
    }
    printf("First star:\t%d\n", coordinates[0] * coordinates[1]);

    if (fclose(f) != 0) {
        perror("Couldn't close file.\n");
    }
}

void second_star(char* input_file_path) {
    FILE* f = fopen(input_file_path, "r");
    if (f == NULL) {
        perror("Couldn't open file.\n");
        exit(1);
    }

    char* line = NULL;
    size_t size;
    char cmd[16] = { '\0' };
    int magnitude = -1;
    int coordinates[2]; // [x, y]
    int aim = 0;
    coordinates[0] = coordinates[1] = 0;
    while (getline(&line, &size, f) != -1) {
        trim(line);
        if (sscanf(line, "%s %d", cmd, &magnitude) != 0) {
            if (strcmp(cmd, "forward") == 0) {
                coordinates[0] += magnitude;
                coordinates[1] += aim * magnitude;
            }
            else if (strcmp(cmd, "down") == 0) {
                aim += magnitude;
            }
            else if (strcmp(cmd, "up") == 0) {
                aim -= magnitude;
            }
            else {
                printf("error: Wrong command. cmd: '%s', line: '%s'\n", cmd, line);
                exit(1);
            }
        }
        else {
            printf("error: Wrong line format. line: '%s', cmd: '%s', %d\n", line, cmd, magnitude);
            exit(1);
        }
    }
    printf("Second star:\t%d\n", coordinates[0] * coordinates[1]);

    if (fclose(f) != 0) {
        perror("Couldn't close file.\n");
    }
}

int main(int argc, char** argv) {
    char* input_file = "input.txt";
    if (argc > 1) {
        input_file = argv[1];
    }

    first_star(input_file);
    second_star(input_file);

    return 0;
}