#ifndef TEXTLINE_H
#define TEXTLINE_H
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

    Cursor cursor;
public:
    TextLine(char* t) : text(t) {}
    uint8_t* serialize(uint32_t& length) override;

    void deserialize(uint8_t* buffer, uint32_t length) override;
    Line* copy() override;
    char* get_type();

    void append_text(const char* input);
    void insert_text(int char_index, const char* insert_str);
    void search_text(const char* query);

    void delete_text(int num_symbols);
    // void cut(int num_symbols);
    // void copy(int num_symbols);
    // void paste();
    void insert_replacement(char* input);
};



#endif
