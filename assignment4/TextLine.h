#ifndef TEXTLINE_H
#define TEXTLINE_H
#include <stdint.h>
#include <string>
#include "Line.h"

class TextLine : public Line{
private:
    std::string text;
    const char* prefix = "Text: ";
public:
    TextLine(std::string& t) : text(t) {}
    uint8_t* serialize(uint8_t* buffer, uint32_t& length) override;
    char* deserialize(uint8_t* buffer, uint32_t length) override;
    Line* copy() override;
};



#endif
