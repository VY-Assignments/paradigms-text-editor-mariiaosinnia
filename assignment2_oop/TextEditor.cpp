#include "TextEditor.h"
#include <iostream>
#include <cstring>
#include <cstdio>

const int INITIAL_LINE_CAPACITY = 10;

TextEditor::TextEditor(): undo_stack(3), redo_stack(3){
    init_text();
    clipboard = nullptr;

    undo_stack.Push(text, num_lines, cursor.get_line(), cursor.get_char());
}

TextEditor::~TextEditor() {
    free_text();
    if (clipboard) {
        delete[] clipboard;
        clipboard = nullptr;
    }
}


void TextEditor::init_text() {
    allocated_lines = INITIAL_LINE_CAPACITY;
    num_lines = 0;
    text = (char**)malloc(allocated_lines * sizeof(char*));
    line_lengths = (int*)malloc(allocated_lines * sizeof(int));
}

void TextEditor::add_line() {
    undo_stack.Push(text, num_lines, cursor.get_line(), cursor.get_char());

    if (num_lines == allocated_lines) {
        allocated_lines *= 2;
        text = (char**)realloc(text, allocated_lines * sizeof(char*));
        line_lengths = (int*)realloc(line_lengths, allocated_lines * sizeof(int));
    }
    text[num_lines] = (char*)malloc(1);
    text[num_lines][0] = '\0';
    line_lengths[num_lines] = 0;
    num_lines++;

    cursor.set_line(num_lines - 1);
    cursor.set_char(0);

    redo_stack.Clear();

}

void TextEditor::append_text(const char* input) {
    undo_stack.Push(text, num_lines, cursor.get_line(), cursor.get_char());

    if (num_lines == 0) {
        add_line();
    }
    int line_idx = num_lines - 1;
    int old_len = line_lengths[line_idx];
    int input_len = strlen(input);

    text[line_idx] = (char*)realloc(text[line_idx], old_len + input_len + 1);
    strcpy(text[line_idx] + old_len, input);
    line_lengths[line_idx] += input_len;

    cursor.set_line(line_idx);
    cursor.set_char(line_lengths[line_idx]);

    redo_stack.Clear();
}

void TextEditor::print_text() {
    for (int i = 0; i < num_lines; i++) {
        printf("%s\n", text[i]);
    }
}

void TextEditor::save_to_file(const char* file_name) {
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < num_lines; i++) {
        fputs(text[i], file);
        fputc('\n', file);
    }

    fclose(file);
    printf("Text has been saved successfully\n");
}

void TextEditor::free_text() {
    for (int i = 0; i < num_lines; i++) {
        free(text[i]);
    }
    free(text);
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
    undo_stack.Push(text, num_lines, cursor.get_line(), cursor.get_char());

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

    text[line_index] = (char*)realloc(text[line_index], old_len + insert_len + 1);

    memmove(text[line_index] + char_index + insert_len,
            text[line_index] + char_index,
            old_len - char_index + 1);

    memcpy(text[line_index] + char_index, insert_str, insert_len);

    line_lengths[line_index] = old_len + insert_len;

    cursor.set_line(line_index);
    cursor.set_char(char_index + insert_len);

    redo_stack.Clear();
}

void TextEditor::search_text(const char* query) {
    int query_len = strlen(query);
    for (int i = 0; i < num_lines; i++) {
        char* line = text[i];
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
           "0  - Exit\n"
           "1  - Append text\n"
           "2  - Start new line\n"
           "3  - Save to file\n"
           "4  - Load from file\n"
           "5  - Print text\n"
           "6  - Insert text at line/index\n"
           "7  - Search text\n"
           "8  - Delete text\n"
           "9  - Undo\n"
           "10 - Redo\n"
           "11 - Cut text\n"
           "12 - Paste text\n"
           "13 - Copy text\n"
           "14 - Insert text with replacement\n");
}

//Assignment 2

void TextEditor::delete_text(int num_symbols) {
    undo_stack.Push(text, num_lines, cursor.get_line(), cursor.get_char());

    int line_index = cursor.get_line();
    int char_index = cursor.get_char();
    if (line_index < 0 || line_index >= num_lines) return;

    int to_delete = num_symbols;
    if (char_index < to_delete) {
        to_delete = char_index;
    }
    if (to_delete <= 0) return;

    int old_len = line_lengths[line_index];
    char* old_line = text[line_index];

    int new_len = old_len - to_delete;

    char* new_line = new char[new_len + 1];

    for (int i = 0; i < char_index - to_delete; i++) {
        new_line[i] = old_line[i];
    }

    for (int i = char_index; i < old_len; i++) {
        new_line[i - to_delete] = old_line[i];
    }

    new_line[new_len] = '\0';

    delete[] old_line;

    text[line_index] = new_line;
    line_lengths[line_index] = new_len;

    cursor.set_char(char_index - to_delete);

    redo_stack.Clear();
}

void TextEditor::undo() {
    if (undo_stack.Size() == 0) {
        printf("[Undo] No more undo steps available.\n");
        return;
    }

    redo_stack.Push(text, num_lines, cursor.get_line(), cursor.get_char());

    Snapshot* snapshot = undo_stack.Pop();
    if (!snapshot) {
        printf("[Undo] No snapshot to restore.\n");
        return;
    }

    for (int i = 0; i < num_lines; ++i) {
        delete[] text[i];
    }
    delete[] text;
    delete[] line_lengths;

    num_lines = snapshot->get_num_lines();
    cursor.set_line(snapshot->get_cursor_line());
    cursor.set_char(snapshot->get_cursor_char());

    text = new char*[num_lines];
    line_lengths = new int[num_lines];
    char** snap_text = snapshot->get_text();

    for (int i = 0; i < num_lines; ++i) {
        int len = strlen(snap_text[i]);
        text[i] = new char[len + 1];
        strcpy(text[i], snap_text[i]);
        line_lengths[i] = len;
    }

    delete snapshot;
}

void TextEditor::redo() {
    if (redo_stack.Size() == 0) {
        printf("[Redo] No more redo steps available.\n");
        return;
    }

    undo_stack.Push(text, num_lines, cursor.get_line(), cursor.get_char());

    Snapshot* snapshot = redo_stack.Pop();
    if (!snapshot) {
        printf("[Redo] No snapshot to restore.\n");
        return;
    }

    for (int i = 0; i < num_lines; ++i) {
        delete[] text[i];
    }
    delete[] text;
    delete[] line_lengths;

    num_lines = snapshot->get_num_lines();
    cursor.set_line(snapshot->get_cursor_line());
    cursor.set_char(snapshot->get_cursor_char());

    text = new char*[num_lines];
    line_lengths = new int[num_lines];
    char** snap_text = snapshot->get_text();

    for (int i = 0; i < num_lines; ++i) {
        int len = strlen(snap_text[i]);
        text[i] = new char[len + 1];
        strcpy(text[i], snap_text[i]);
        line_lengths[i] = len;
    }

    delete snapshot;
}

void TextEditor::copy(int num_symbols) {
    if (clipboard) {
        delete[] clipboard;
        clipboard = nullptr;
    }

    int line = cursor.get_line();
    int pos = cursor.get_char();

    if (line < 0 || line >= num_lines) return;
    if (pos <= 0) return;

    int copy_len = num_symbols;
    if (copy_len > pos) copy_len = pos;

    clipboard = new char[copy_len + 1];
    strncpy(clipboard, text[line] + pos - copy_len, copy_len);
    clipboard[copy_len] = '\0';
}


void TextEditor::cut(int num_symbols) {
    undo_stack.Push(text, num_lines, cursor.get_line(), cursor.get_char());

    int line = cursor.get_line();
    int pos = cursor.get_char();

    if (line < 0 || line >= num_lines) return;
    if (pos <= 0) return;

    if (num_symbols > pos) num_symbols = pos;

    delete[] clipboard;
    clipboard = new char[num_symbols + 1];
    strncpy(clipboard, text[line] + pos - num_symbols, num_symbols);
    clipboard[num_symbols] = '\0';

    int old_len = line_lengths[line];
    int new_len = old_len - num_symbols;

    char* new_line = new char[new_len + 1];

    strncpy(new_line, text[line], pos - num_symbols);
    strcpy(new_line + pos - num_symbols, text[line] + pos);
    new_line[new_len] = '\0';

    delete[] text[line];
    text[line] = new_line;
    line_lengths[line] = new_len;

    cursor.set_char(pos - num_symbols);

    redo_stack.Clear();
}


void TextEditor::paste() {
    undo_stack.Push(text, num_lines, cursor.get_line(), cursor.get_char());

    if (!clipboard) return;

    int line = cursor.get_line();
    int pos = cursor.get_char();

    if (line < 0 || line >= num_lines) return;
    if (pos < 0 || pos > line_lengths[line]) return;

    int clip_len = strlen(clipboard);
    int new_len = line_lengths[line] + clip_len;

    char* new_line = new char[new_len + 1];

    strncpy(new_line, text[line], pos);
    strcpy(new_line + pos, clipboard);
    strcpy(new_line + pos + clip_len, text[line] + pos);

    new_line[new_len] = '\0';

    delete[] text[line];
    text[line] = new_line;
    line_lengths[line] = new_len;

    cursor.set_char(pos + clip_len);

    redo_stack.Clear();
}

void TextEditor::insert_replacement(char* input) {
    undo_stack.Push(text, num_lines, cursor.get_line(), cursor.get_char());

    int line = cursor.get_line();
    int pos = cursor.get_char();

    if (line < 0 || line >= num_lines) return;
    if (pos <= 0 || pos > line_lengths[line]) return;

    int input_len = strlen(input);

    int insert_pos = pos - input_len;
    if (insert_pos < 0) insert_pos = 0;

    int new_len = line_lengths[line] + input_len;

    char* new_line = new char[new_len + 1];

    strncpy(new_line, text[line], insert_pos);

    strcpy(new_line + insert_pos, input);

    strcpy(new_line + insert_pos + input_len, text[line] + pos);

    delete[] text[line];
    text[line] = new_line;
    line_lengths[line] = new_len;

    cursor.set_char(insert_pos + input_len);

    redo_stack.Clear();
}



