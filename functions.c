#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int INITIAL_LINE_CAPACITY = 10;

typedef struct Text {
    char** lines;
    int* line_lengths;
    int num_lines;
    int allocated_lines;
} Text;

void init_text(Text* text) {
    text->allocated_lines = INITIAL_LINE_CAPACITY;
    text->num_lines = 0;
    text->lines = malloc(text->allocated_lines * sizeof(char*));
    text->line_lengths = malloc(text->allocated_lines * sizeof(int));
}

void add_line(Text* text) {
    if (text->num_lines == text->allocated_lines) {
        text->allocated_lines *= 2;
        text->lines = realloc(text->lines, text->allocated_lines * sizeof(char*));
        text->line_lengths = realloc(text->line_lengths, text->allocated_lines * sizeof(int));
    }
    text->lines[text->num_lines] = malloc(1);
    text->lines[text->num_lines][0] = '\0';
    text->line_lengths[text->num_lines] = 0;
    text->num_lines++;
}

void append_text(Text* text, char* input) {
    if (text->num_lines == 0) {
        add_line(text);
    }
    int line_idx = text->num_lines - 1;
    int old_len = text->line_lengths[line_idx];
    int input_len = strlen(input);

    text->lines[line_idx] = realloc(text->lines[line_idx], old_len + input_len + 1);
    strcpy(text->lines[line_idx] + old_len, input);
    text->line_lengths[line_idx] += input_len;
}

void print_text(Text* text) {
    for (int i = 0; i < text->num_lines; i++) {
        printf("%s\n", text->lines[i]);
    }
}

void save_to_file(Text* text, char* file_name) {
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < text->num_lines; i++) {
        fputs(text->lines[i], file);
        fputc('\n', file);
    }

    fclose(file);
    printf("Text has been saved successfully\n");
}

void free_text(Text* text) {
    for (int i = 0; i < text->num_lines; i++) {
        free(text->lines[i]);
    }
    free(text->lines);
    free(text->line_lengths);
}

void load_from_file(Text* text, char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }

    free_text(text);
    init_text(text);

    char buffer[512];

    while (fgets(buffer, sizeof(buffer), file)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        add_line(text);
        append_text(text, buffer);
    }

    fclose(file);
    printf("Text has been loaded successfully\n");
}

void insert_text(Text* text, int line_index, int char_index, char* insert_str) {
    if (line_index < 0 || line_index >= text->num_lines) {
        printf("There isn`t line with this index");
        return;
    }
    int old_len = text->line_lengths[line_index];
    int insert_len = strlen(insert_str);

    if (char_index < 0) {
        char_index = 0;
    }
    if (char_index > old_len) {
        char_index = old_len;
    }

    text->lines[line_index] = realloc(text->lines[line_index], old_len + insert_len + 1);

    memmove(text->lines[line_index] + char_index + insert_len,
            text->lines[line_index] + char_index,
            old_len - char_index + 1);

    memcpy(text->lines[line_index] + char_index, insert_str, insert_len);

    text->line_lengths[line_index] = old_len + insert_len;
}

void search_text(Text* text, char* query) {
    int query_len = strlen(query);
    for (int i = 0; i < text->num_lines; i++) {
        char* line = text->lines[i];
        int line_len = text->line_lengths[i];
        for (int j = 0; j <= line_len - query_len; j++) {
            if (strncmp(line + j, query, query_len) == 0) {
                printf("Text is present in this position: %d %d\n", i, j);
            }
        }
    }
}

void clear_console() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void print_menu() {
    printf("Choose the command:\n"
           "1 - Append text\n"
           "2 - Start new line\n"
           "3 - Save to file\n"
           "4 - Load from file\n"
           "5 - Print text\n"
           "6 - Insert text by line/index\n"
           "7 - Search\n"
           "0 - Exit\n");
}