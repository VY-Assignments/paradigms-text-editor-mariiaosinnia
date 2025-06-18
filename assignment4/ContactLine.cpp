#include "ContactLine.h"
#include <cstring>

uint8_t *ContactLine::serialize(uint32_t &length) {
    uint16_t offset = 0;
    uint8_t prefix_len = strlen(prefix);
    uint8_t contact_len = contact.length();
    uint8_t email_prefix_len = strlen(email_prefix);
    uint8_t email_len = email.length();

    uint8_t* buffer = new uint8_t[prefix_len + contact_len + email_prefix_len + email_len];

    memcpy(buffer, prefix, prefix_len);
    offset += prefix_len;

    memcpy(buffer + offset, &contact_len, sizeof(contact_len));
    offset += sizeof(contact_len);

    memcpy(buffer + offset, contact.c_str(), contact_len);
    offset += contact_len;

    memcpy(buffer + offset, email_prefix, email_prefix_len);
    offset += email_prefix_len;

    memcpy(buffer + offset, &email_len, sizeof(email_len));
    offset += sizeof(email_len);

    memcpy(buffer + offset, email.c_str(), email_len);
    offset += email_len;

    length = offset;
    return buffer;
}

void ContactLine::deserialize(uint8_t *buffer, uint32_t length) {
    uint16_t offset = 0;
    uint8_t prefix_len = strlen(prefix);
    uint8_t email_prefix_len = strlen(email_prefix);

    if (length < prefix_len + sizeof(uint8_t)) {
        return;
    }

    offset += prefix_len;

    uint8_t contact_len = 0;
    memcpy(&contact_len, buffer + offset, sizeof(contact_len));
    offset += sizeof(contact_len);

    char* contact_buf = new char[contact_len + 1];
    memcpy(contact_buf, buffer + offset, contact_len);
    contact_buf[contact_len] = '\0';
    contact = std::string(contact_buf);
    delete[] contact_buf;

    offset += contact_len + email_prefix_len;

    uint8_t email_len = 0;
    memcpy(&email_len, buffer + offset, sizeof(email_len));
    offset += sizeof(email_len);

    char* email_buf = new char[email_len + 1];
    memcpy(email_buf, buffer + offset, email_len);
    email_buf[email_len] = '\0';
    email = std::string(email_buf);
    delete[] email_buf;

}

Line *ContactLine::copy() {
    return new ContactLine(this->contact, this->email);
}




