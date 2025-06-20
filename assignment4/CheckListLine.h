#ifndef CHECKLISTLINE_H
#define CHECKLISTLINE_H
#include <string>

#include "Line.h"


class CheckListLine : public Line{
private:
    bool is_completed;
    std::string task;
    const char* prefix_task_completed = "[ ]";
    const char* prefix_task_uncompleted = "[x]";
public:
    CheckListLine(std::string& task) : task(task) {};
    CheckListLine(const std::string& task, bool is_completed)
    : task(task), is_completed(is_completed) {}
    uint8_t* serialize(uint32_t &length) override;
    void deserialize(uint8_t *buffer, uint32_t length) override;
    Line* copy() override;
};



#endif
