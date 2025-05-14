#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Line {
    char* text;
    int size;
    int allocated_size;
} Line;

typedef struct Text {
    Line* lines;
    int size;
} Text;

void append_text(Text* text, char* input) {
    if (text->size == 0) {
        text->lines = malloc(10 * sizeof(Line));
    }

    Line* current_line = &text->lines[text->size - 1];
    int input_len = strlen(input);

    if (current_line->size + input_len + 1 > current_line->allocated_size) {
        if (current_line->allocated_size == 0) {
            current_line->allocated_size = 10;
        }
        else {
            current_line->allocated_size = current_line->allocated_size * 2;
        }
        current_line->text = realloc(current_line->text, current_line->allocated_size * sizeof(char));
    }

    strcat(current_line->text, input);
    current_line->size += input_len;
}
