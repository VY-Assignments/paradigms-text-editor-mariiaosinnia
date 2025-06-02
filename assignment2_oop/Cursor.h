#ifndef CURSOR_H
#define CURSOR_H

class Cursor {
public:
    Cursor();
    int get_line();
    int get_char();
    void set_position(int in_line_index, int in_char_index);
    void set_line(int in_line_index);
    void set_char(int in_char_index);

private:
    int line_index;
    int char_index;
};


#endif //CURSOR_H
