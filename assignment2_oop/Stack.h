#include "Snapshot.h"

class Stack {
public:
    Stack(int inCapacity);
    ~Stack();

    void Push(char** text, int num_lines, int cursor_line, int cursor_char);
    Snapshot* Pop();
    Snapshot* Peek();
    bool isEmpty();
    int Size();
    void Clear();

private:
    void Resize();

    Snapshot** snapshots;
    int capacity;
    int size;
};
