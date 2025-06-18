#include "TextLine.h"
#include <cstring>
#include <iostream>
#include <stdint.h>


uint8_t* TextLine::serialize(uint32_t& length) {
    uint32_t offset = 0;
    uint32_t text_len = text.length();
    uint8_t prefix_len = strlen(prefix);

    length = prefix_len + sizeof(text_len) + text_len;
    uint8_t* buffer = new uint8_t[length];

    memcpy(buffer, prefix, prefix_len);
    offset += prefix_len;

    memcpy(buffer + offset, &text_len, sizeof(text_len));
    offset += sizeof(text_len);

    memcpy(buffer + offset, text.c_str(), text_len);
    offset += text_len;

    return buffer;
}

void TextLine::deserialize(uint8_t* buffer, uint32_t length) {
    uint32_t offset = 0;
    uint8_t prefix_len = strlen(prefix);

    if (length < prefix_len + sizeof(uint8_t)) {
        return;
    }

    offset += prefix_len;

    uint32_t text_len = 0;
    memcpy(&text_len, buffer + offset, sizeof(text_len));
    offset += sizeof(text_len);

    if (offset + text_len > length) {
        return;
    }

    char* result = new char[prefix_len + text_len + 1];

    memcpy(result, prefix, prefix_len);
    memcpy(result + prefix_len, buffer + offset, text_len);
    result[prefix_len + text_len] = '\0';

    text = std::string(result);
    delete[] result;
}

Line *TextLine::copy() {
    return new TextLine(this->text);
}





