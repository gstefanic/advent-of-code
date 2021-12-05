#include <stdio.h>
#include <stdlib.h>
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
    printf("First star:\t%d\n", depth_increased_count);

    if (fclose(f) != 0) {
        perror("Couldn't close file.\n");
    }
}

typedef struct {
    size_t window_size;
    long long* values;
    size_t number_of_values;
    long long sum;
} sliding_window;

void free_sliding_window(sliding_window* sw) {
    if (sw != NULL) {
        if (sw->values != NULL) {
            free(sw->values);
        }
        free(sw);
    }
}

sliding_window* new_sliding_window(size_t window_size) {
    sliding_window* sw;
    if (window_size > 0 && (sw = malloc(sizeof *sw)) != NULL) {
        sw->window_size = window_size;
        sw->number_of_values = 0;
        sw->sum = 0;
        if ((sw->values = malloc((sizeof sw->values) * window_size)) != NULL) {
            for (int i = 0; i < window_size; ++i) {
                sw->values[i] = 0;
            }
        } else {
            free_sliding_window(sw);
        }
    }
    return sw;
}

int is_window_full(sliding_window* window) {
    if (window == NULL) {
        perror("error: window is null at is_window_full: \n");
        exit(1);
    }
    return (window->number_of_values == window->window_size) ? 1 : 0;
}

void add_measurement(sliding_window* window, long long measurement) {
    if (window == NULL) {
        perror("error: window is null at add_measurement: \n");
        exit(1);
    }
    if (is_window_full(window)) {
        window->sum -= window->values[0];
        for (size_t i = 1; i < window->window_size; ++i) {
            window->values[i - 1] = window->values[i];
        }
        window->values[window->window_size - 1] = measurement;
    } else {
        window->values[window->number_of_values] = measurement;
        ++window->number_of_values;
    }
    window->sum += measurement;
}

void second_star(char* input_file_path) {
    FILE* f = fopen(input_file_path, "r");
    if (f == NULL) {
        perror("Couldn't open file.\n");
        exit(1);
    }
    char* line = NULL;
    size_t size;
    int depth_increased_count = 0;
    long long previous_sliding_depth = -1;
    long long current_sliding_depth = -1;
    sliding_window* window = new_sliding_window(3);
    while (window != NULL && getline(&line, &size, f) != -1) {
        trim(line);
        long long current_depth = strtol(line, NULL, 10);
        add_measurement(window, current_depth);
        if (is_window_full(window) != 0) {
            current_sliding_depth = window->sum;
            if (previous_sliding_depth >= 0 && current_sliding_depth > previous_sliding_depth) {
                ++depth_increased_count;
            }
            previous_sliding_depth = current_sliding_depth;
        }
    }
    free_sliding_window(window);
    printf("Second star:\t%d\n", depth_increased_count);

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