#include "ContactLine.h"
#include <cstring>

uint8_t *ContactLine::serialize(uint8_t *buffer, uint32_t &length) {
    uint16_t offset = 0;

    uint8_t prefix_len = strlen(prefix);
    memcpy(buffer, prefix, prefix_len);
    offset += prefix_len;

    uint8_t contact_len = contact.length();
    memcpy(buffer + offset, &contact_len, sizeof(contact_len));
    offset += sizeof(contact_len);

    memcpy(buffer + offset, contact.c_str(), contact_len);
    offset += contact_len;

    uint8_t email_prefix_len = strlen(email_prefix);
    memcpy(buffer + offset, email_prefix, email_prefix_len);
    offset += email_prefix_len;

    uint8_t email_len = email.length();
    memcpy(buffer + offset, &email_len, sizeof(email_len));
    offset += sizeof(email_len);

    memcpy(buffer + offset, email.c_str(), email_len);
    offset += email_len;

    length = offset;
    return buffer;
}

char *ContactLine::deserialize(uint8_t *buffer, uint32_t length) {
    uint16_t offset = 0;
    uint8_t prefix_len = strlen(prefix);
    uint8_t email_prefix_len = strlen(email_prefix);

    if (length < prefix_len + sizeof(uint32_t)) {
        return nullptr;
    }

    offset += prefix_len;

    uint8_t contact_len = 0;
    memcpy(&contact_len, buffer + offset, sizeof(contact_len));
    offset += sizeof(contact_len);

    offset += contact_len + email_prefix_len;

    uint8_t email_len = email.length();
    memcpy(&email_len, buffer + offset, sizeof(email_len));
    offset += sizeof(email_len);

    char* result = new char[prefix_len + contact_len + email_prefix_len + email_len + 1];

    memcpy(result, prefix, prefix_len);
    memcpy(result + prefix_len, buffer + prefix_len, contact_len);
    memcpy(result + prefix_len + contact_len, email_prefix, email_prefix_len);
    memcpy(result + prefix_len + contact_len + email_prefix_len, buffer + offset, email_len);

    result[prefix_len + contact_len + email_prefix_len + email_len] = '\0';

    return result;
}



