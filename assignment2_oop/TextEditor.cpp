#include "TextEditor.h"
#include <iostream>
#include <cstring>
#include <cstdio>

const int INITIAL_LINE_CAPACITY = 10;

TextEditor::TextEditor() {
    init_text();
}
TextEditor::~TextEditor() {
    free_text();
}


void TextEditor::init_text() {
    allocated_lines = INITIAL_LINE_CAPACITY;
    num_lines = 0;
    lines = (char**)malloc(allocated_lines * sizeof(char*));
    line_lengths = (int*)malloc(allocated_lines * sizeof(int));
}

void TextEditor::add_line() {
    if (num_lines == allocated_lines) {
        allocated_lines *= 2;
        lines = (char**)realloc(lines, allocated_lines * sizeof(char*));
        line_lengths = (int*)realloc(line_lengths, allocated_lines * sizeof(int));
    }
    lines[num_lines] = (char*)malloc(1);
    lines[num_lines][0] = '\0';
    line_lengths[num_lines] = 0;
    num_lines++;
}

void TextEditor::append_text(const char* input) {
    if (num_lines == 0) {
        add_line();
    }
    int line_idx = num_lines - 1;
    int old_len = line_lengths[line_idx];
    int input_len = strlen(input);

    lines[line_idx] = (char*)realloc(lines[line_idx], old_len + input_len + 1);
    strcpy(lines[line_idx] + old_len, input);
    line_lengths[line_idx] += input_len;
}

void TextEditor::print_text() {
    for (int i = 0; i < num_lines; i++) {
        printf("%s\n", lines[i]);
    }
}

void TextEditor::save_to_file(const char* file_name) {
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < num_lines; i++) {
        fputs(lines[i], file);
        fputc('\n', file);
    }

    fclose(file);
    printf("Text has been saved successfully\n");
}

void TextEditor::free_text() {
    for (int i = 0; i < num_lines; i++) {
        free(lines[i]);
    }
    free(lines);
    free(line_lengths);
}

void TextEditor::load_from_file(const char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }

    free_text();
    init_text();

    char buffer[512];

    while (fgets(buffer, sizeof(buffer), file)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        add_line();
        append_text(buffer);
    }

    fclose(file);
    printf("Text has been loaded successfully\n");
}

void TextEditor::insert_text(int line_index, int char_index, const char* insert_str) {
    if (line_index < 0 || line_index >= num_lines) {
        printf("There isn`t line with this index");
        return;
    }
    int old_len = line_lengths[line_index];
    int insert_len = strlen(insert_str);

    if (char_index < 0) {
        char_index = 0;
    }
    if (char_index > old_len) {
        char_index = old_len;
    }

    lines[line_index] = (char*)realloc(lines[line_index], old_len + insert_len + 1);

    memmove(lines[line_index] + char_index + insert_len,
            lines[line_index] + char_index,
            old_len - char_index + 1);

    memcpy(lines[line_index] + char_index, insert_str, insert_len);

    line_lengths[line_index] = old_len + insert_len;
}

void TextEditor::search_text(const char* query) {
    int query_len = strlen(query);
    for (int i = 0; i < num_lines; i++) {
        char* line = lines[i];
        int line_len = line_lengths[i];
        for (int j = 0; j <= line_len - query_len; j++) {
            if (strncmp(line + j, query, query_len) == 0) {
                printf("Text is present in this position: %d %d\n", i, j);
            }
        }
    }
}

void TextEditor::clear_console() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void TextEditor::print_menu() {
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