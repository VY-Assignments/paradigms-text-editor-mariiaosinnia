#ifndef LINE_H
#define LINE_H
#include <cstdint>

class Line {
public:
    virtual uint8_t* serialize(uint8_t* buffer, uint32_t& length) = 0;
    virtual char* deserialize(uint8_t* buffer, uint32_t length) = 0;
    virtual Line* copy() = 0;
};

#endif
