#ifndef TEXTLINE_H
#define TEXTLINE_H
#include <cstring>
#include <stdint.h>
#include <string>

#include "Cursor.h"
#include "Line.h"
#include "../assignment2_oop/TextEditor.h"

class TextLine : public Line{
private:
    char* text;
    const char* prefix = "Text: ";
    uint32_t length;
    std::string full_line;

    Cursor cursor;
public:
    TextLine(char* t) : text(nullptr), length(0) {
        if (t != nullptr) {
            size_t len = std::strlen(t);
            text = static_cast<char*>(std::malloc(len + 1));
            if (text != nullptr) {
                std::memcpy(text, t, len);
                text[len] = '\0';
                length = len;
            }
        }
    }
    uint8_t* serialize(uint32_t& length) override;

    void deserialize(uint8_t* buffer, uint32_t length) override;
    Line* copy() override;
    char* get_type() override;
    char* get_text();
    const char* to_string() override;

    void append_text(char* input) override;
    void insert_text(int char_index, const char* insert_str);
    void search_text(const char* query);

    void delete_text(int num_symbols);
    void insert_replacement(char* input);
};



#endif
