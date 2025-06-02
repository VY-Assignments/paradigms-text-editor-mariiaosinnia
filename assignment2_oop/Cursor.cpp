#include "Cursor.h"

Cursor::Cursor() {
    line_index = 0;
    char_index = 0;
}
void Cursor::set_position(int in_line_index, int in_char_index) {
    line_index = in_line_index;
    char_index = in_char_index;
}
int Cursor::get_char() {
    return char_index;
}
int Cursor::get_line() {
    return line_index;
}

void Cursor::set_line(int in_line_index) {
    line_index = in_line_index;
}

void Cursor::set_char(int in_char_index) {
    char_index = in_char_index;
}



