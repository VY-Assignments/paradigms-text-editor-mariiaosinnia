#include "Snapshot.h"
#include <cstring>

Snapshot::Snapshot(char** in_text, int in_num_lines, int cursor_line_pos, int cursor_char_pos) {
    num_lines = in_num_lines;
    cursor_line = cursor_line_pos;
    cursor_char = cursor_char_pos;

    text = new char*[num_lines];
    for (int i = 0; i < num_lines; ++i) {
        int len = strlen(in_text[i]);
        text[i] = new char[len + 1];
        strcpy(text[i], in_text[i]);
    }
}

Snapshot::~Snapshot() {
    for (int i = 0; i < num_lines; ++i) {
        delete[] text[i];
    }
    delete[] text;
}

char** Snapshot::get_text() {
    return text;
}

int Snapshot::get_num_lines() {
    return num_lines;
}

int Snapshot::get_cursor_line() {
    return cursor_line;
}

int Snapshot::get_cursor_char() {
    return cursor_char;
}
