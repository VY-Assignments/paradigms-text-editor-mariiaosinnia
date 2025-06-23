#ifndef CHECKLISTLINE_H
#define CHECKLISTLINE_H
#include <string.h>
#include <string>

#include "Line.h"


class CheckListLine : public Line{
private:
    bool is_completed;
    char* task;
    int length;
    const char* prefix_task_uncompleted = "[ ] ";
    const char* prefix_task_completed = "[x] ";
public:
    CheckListLine(const char* task_input, bool is_completed)
    : is_completed(is_completed)
    {
        if (task_input) {
            size_t len = strlen(task_input);
            task = (char*)malloc(len + 1);
            if (task) {
                strcpy(task, task_input);
            }
        } else {
            task = nullptr;
        }
    }
    uint8_t* serialize(uint32_t &length) override;
    void deserialize(uint8_t *buffer, uint32_t length) override;
    Line* copy() override;
    char* get_type() override;
    const char* to_string() override;
    void append_text(char* input) override;
};



#endif
