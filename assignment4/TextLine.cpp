#include "TextLine.h"
#include <cstring>
#include <iostream>
#include <stdint.h>


uint8_t* TextLine::serialize(uint8_t* buffer, uint32_t& length) {
    uint32_t offset = 0;
    uint32_t text_len = text.length();

    uint8_t prefix_len = strlen(prefix);
    memcpy(buffer, prefix, prefix_len);
    offset += prefix_len;

    memcpy(buffer + offset, &text_len, sizeof(text_len));
    offset += sizeof(text_len);

    memcpy(buffer + offset, text.c_str(), text_len);
    offset += text_len;

    length = offset;

    return buffer;
}

char* TextLine::deserialize(uint8_t* buffer, uint32_t length) {
    uint32_t offset = 0;
    uint8_t prefix_len = strlen(prefix);

    if (length < prefix_len + sizeof(uint32_t)) {
        return nullptr;
    }

    offset += prefix_len;

    uint32_t text_len = 0;
    memcpy(&text_len, buffer + offset, sizeof(text_len));
    offset += sizeof(text_len);

    if (offset + text_len > length) {
        return nullptr;
    }

    char* result = new char[prefix_len + text_len + 1];

    memcpy(result, prefix, prefix_len);
    memcpy(result + prefix_len, buffer + offset, text_len);
    result[prefix_len + text_len] = '\0';

    return result;
}

Line *TextLine::copy() {
    return new TextLine(this->text);
}





