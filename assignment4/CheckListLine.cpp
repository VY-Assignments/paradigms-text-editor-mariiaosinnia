#include "CheckListLine.h"
#include <cstring>


uint8_t *CheckListLine::serialize(uint8_t *buffer, uint32_t &length) {
    uint32_t offset = 0;
    uint32_t task_len = task.length();

    if (is_completed) {
        uint8_t prefix_len = strlen(prefix_task_completed);
        memcpy(buffer, prefix_task_completed, prefix_len);
        offset += prefix_len;
    }
    else {
        uint8_t prefix_len = strlen(prefix_task_uncompleted);
        memcpy(buffer, prefix_task_uncompleted, prefix_len);
        offset += prefix_len;
    }

    memcpy(buffer + offset, &task_len, sizeof(task_len));
    offset += sizeof(task_len);

    memcpy(buffer + offset, task.c_str(), task_len);
    offset += task_len;

    length = offset;

    return buffer;
}

char *CheckListLine::deserialize(uint8_t *buffer, uint32_t length) {
    uint32_t offset = 0;
    uint8_t prefix_len = strlen(prefix_task_completed);

    offset += prefix_len;

    uint32_t task_len = 0;
    memcpy(&task_len, buffer + offset, sizeof(task_len));
    offset += sizeof(task_len);

    char* result = new char[prefix_len + task_len + 1];

    if (is_completed) {
        memcpy(result, prefix_task_completed, prefix_len);
    }
    else {
        memcpy(result, prefix_task_uncompleted, prefix_len);
    }
    memcpy(result + prefix_len, buffer + offset, task_len);
    result[prefix_len + task_len + 1] = '\0';

    return result;
}

