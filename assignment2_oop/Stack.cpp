#include "Stack.h"

Stack::Stack(int in_capacity) {
    capacity = in_capacity;
    size = 0;
    snapshots = new Snapshot*[capacity];
}

Stack::~Stack() {
    for (int i = 0; i < size; i++) {
        delete snapshots[i];
    }
    delete[] snapshots;
}

void Stack::Push(char** text, int num_lines, int cursor_line, int cursor_char) {
    if (size == capacity) {
        delete snapshots[0];
        for (int i = 1; i < size; ++i) {
            snapshots[i - 1] = snapshots[i];
        }
        size--;
    }
    snapshots[size] = new Snapshot(text, num_lines, cursor_line, cursor_char);
    size++;
}

void Stack::Pop() {
    if (size == 0) return;
    delete snapshots[size - 1];
    size--;
}

Snapshot* Stack::Peek() {
    if (size == 0) return nullptr;
    return snapshots[size - 1];
}

bool Stack::isEmpty() {
    return size == 0;
}

int Stack::Size() {
    return size;
}

void Stack::Resize() {
    int new_capacity = capacity * 2;
    Snapshot** new_snapshots = new Snapshot*[new_capacity];

    for (int i = 0; i < size; i++) {
        new_snapshots[i] = snapshots[i];
    }

    delete[] snapshots;
    snapshots = new_snapshots;
    capacity = new_capacity;
}

void Stack::Clear() {
    for (int i = 0; i < size; i++) {
        delete snapshots[i];
    }
    size = 0;
}

