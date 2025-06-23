#include "CheckListLine.h"
#include <cstring>


uint8_t* CheckListLine::serialize(uint32_t &length) {
    uint32_t offset = 0;
    uint8_t task_len = strlen(task);
    uint8_t prefix_len = strlen(prefix_task_completed);

    length = prefix_len + sizeof(task_len) + task_len;
    uint8_t* buffer = new uint8_t[length];
    if (is_completed) {
        memcpy(buffer, prefix_task_completed, prefix_len);
        offset += prefix_len;
    }
    else {
        memcpy(buffer, prefix_task_uncompleted, prefix_len);
        offset += prefix_len;
    }

    memcpy(buffer + offset, &task_len, sizeof(task_len));
    offset += sizeof(task_len);

    memcpy(buffer + offset, task, task_len);
    offset += task_len;

    return buffer;
}

void CheckListLine::deserialize(uint8_t *buffer, uint32_t length) {
    uint32_t offset = 0;
    uint8_t prefix_len = strlen(prefix_task_completed);

    if (memcmp(buffer, prefix_task_completed, prefix_len) == 0) {
        is_completed = true;
    } else if (memcmp(buffer, prefix_task_uncompleted, prefix_len) == 0) {
        is_completed = false;
    } else {
        return;
    }

    offset += prefix_len;

    uint8_t task_len = 0;
    memcpy(&task_len, buffer + offset, sizeof(task_len));
    offset += sizeof(task_len);

    if (offset + task_len > length) return;

    char* result = new char[task_len + 1];
    memcpy(result, buffer + offset, task_len);
    result[task_len] = '\0';

    if (task) delete[] task;
    task = result;
}


Line* CheckListLine::copy() {
    return new CheckListLine(this->task, this->is_completed);
}

char *CheckListLine::get_type() {
    return "Check list";
}

const char *CheckListLine::to_string() {
    static char buffer[1024];
    buffer[0] = '\0';

    if (is_completed) {
        strcat(buffer, prefix_task_completed);
    } else {
        strcat(buffer, prefix_task_uncompleted);
    }

    if (task != nullptr) {
        strcat(buffer, task);
    }

    return buffer;
}



void CheckListLine::append_text(char *input) {
    int input_len = strlen(input);
    int old_len = 0;
    if (task != nullptr) {
        old_len = strlen(task);
    }

    char* new_task = (char*) realloc(task, old_len + input_len + 1);
    if (!new_task) return;

    memcpy(new_task + old_len, input, input_len + 1);

    task = new_task;
    length = old_len + input_len;
}



