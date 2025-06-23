#include "TextLine.h"
#include <cstring>
#include <iostream>
#include <stdint.h>


uint8_t* TextLine::serialize(uint32_t& length) {
    uint32_t offset = 0;
    uint32_t text_len = strlen(text);
    uint8_t prefix_len = strlen(prefix);

    length = prefix_len + sizeof(text_len) + text_len;
    uint8_t* buffer = new uint8_t[length];

    memcpy(buffer, prefix, prefix_len);
    offset += prefix_len;

    memcpy(buffer + offset, &text_len, sizeof(text_len));
    offset += sizeof(text_len);

    memcpy(buffer + offset, text, text_len);
    offset += text_len;

    return buffer;
}

void TextLine::deserialize(uint8_t* buffer, uint32_t length) {
    uint8_t prefix_len = strlen(prefix);

    if (length < prefix_len + sizeof(uint32_t)) {
        return;
    }

    if (memcmp(buffer, prefix, prefix_len) != 0) {
        return;
    }

    uint32_t text_len = 0;
    memcpy(&text_len, buffer + prefix_len, sizeof(text_len));

    if (prefix_len + sizeof(text_len) + text_len > length) {
        return;
    }

    delete[] text;

    text = new char[text_len + 1];

    memcpy(text, buffer + prefix_len + sizeof(text_len), text_len);
    text[text_len] = '\0';
}


Line *TextLine::copy() {
    return new TextLine(this->text);
}

char *TextLine::get_type() {
    return "Text";
}

char *TextLine::get_text() {
    return text;
}

const char *TextLine::to_string() {
    if (text) {
        full_line = std::string(prefix) + text;
    } else {
        full_line = std::string(prefix);
    }
    return full_line.c_str();
}


void TextLine::append_text(char* input) {
    int input_len = strlen(input);
    int old_len = 0;
    if (text != nullptr) {
        old_len = strlen(text);
    }

    char* new_text = (char*)realloc(text, old_len + input_len + 1);
    if (new_text == nullptr) return;

    memcpy(new_text + old_len, input, input_len + 1);

    text = new_text;
    length = old_len + input_len;
    cursor.set_char(length);
}

void TextLine::insert_text(int char_index, const char *insert_str) {
    int insert_len = strlen(insert_str);
    int old_len = 0;
    if (text != nullptr) {
        old_len = strlen(text);
    }

    if (char_index < 0) char_index = 0;
    if (char_index > old_len) char_index = old_len;

    memmove(text + char_index + insert_len, text + char_index, old_len - char_index + 1);
    memcpy(text + char_index, insert_str, insert_len);

    length = old_len + insert_len;
    cursor.set_char(char_index + insert_len);
}

void TextLine::search_text(const char *query) {
    int query_len = strlen(query);
    for (int i = 0; i <= length - query_len; i++) {
        if (strncmp(text + i, query, query_len) == 0) {
            printf("Text is present in this position: %d", i);
        }
    }
}

void TextLine::delete_text(int num_symbols) {
    int char_index = cursor.get_char();
    int to_delete = num_symbols;
    if (char_index < to_delete) to_delete = char_index;
    if (to_delete <= 0) return;

    int old_len = length;

    int new_len = old_len - to_delete;
    memmove(text + char_index - to_delete, text + char_index, old_len - char_index + 1); // +1 щоб захопити '\0'
    if (new_len == 0) {
        free(text);
        text = (char*)malloc(1);
        text[0] = '\0';
    } else {
        char* new_text = (char*)realloc(text, new_len + 1);
        if (new_text != nullptr) {
            text = new_text;
        }
    }

    length = new_len;
    cursor.set_char(char_index - to_delete);
}

void TextLine::insert_replacement(char *input) {
    int position = cursor.get_char();
    if (position <= 0 || position > length) return;
    int input_length = strlen(input);

    int insert_position = position - input_length;
    if (insert_position < 0) insert_position = 0;

    char* new_text = new char[length+ 1];
    strncpy(new_text, text, insert_position);
    strcpy(new_text + insert_position, input);
    strcpy(new_text + position, text + position);

    delete[] text;
    text = new_text;

    cursor.set_char(position);
}













