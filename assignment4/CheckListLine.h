#ifndef CHECKLISTLINE_H
#define CHECKLISTLINE_H
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
    CheckListLine(char* task, bool is_completed)
    : task(task), is_completed(is_completed) {}
    uint8_t* serialize(uint32_t &length) override;
    void deserialize(uint8_t *buffer, uint32_t length) override;
    Line* copy() override;
    char* get_type();
    void append_text(char* input);
};



#endif
