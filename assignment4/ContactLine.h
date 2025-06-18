#ifndef CONTACTLINE_H
#define CONTACTLINE_H
#include <string>
#include "Line.h"


class ContactLine : public Line {
private:
    std::string contact;
    std::string email;
    const char* prefix = "Contact - ";
    const char* email_prefix = ", E-mail: ";
public:
    ContactLine(std::string& contact, std::string& email) : contact(contact), email(email) {}
    uint8_t* serialize(uint32_t &length) override;
    void deserialize(uint8_t *buffer, uint32_t length) override;
    Line* copy() override;
};



#endif
