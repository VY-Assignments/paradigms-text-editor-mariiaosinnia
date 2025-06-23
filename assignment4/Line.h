#ifndef LINE_H
#define LINE_H
#include <cstdint>

class Line {
public:
    virtual uint8_t* serialize(uint32_t& length) = 0;
    virtual void deserialize(uint8_t* buffer, uint32_t length) = 0;
    virtual Line* copy() = 0;
    virtual void append_text(char* input) = 0;
    virtual char* get_type() = 0;
    virtual const char* to_string() = 0;
    virtual ~Line();
};

#endif
