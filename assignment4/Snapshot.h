class Snapshot {
public:
    Snapshot(char** in_text, int in_num_lines, int cursor_line_pos, int cursor_char_pos);
    ~Snapshot();

    char** get_text();
    int get_num_lines();
    int get_cursor_line();
    int get_cursor_char();

private:
    char** text;
    int num_lines;
    int cursor_line;
    int cursor_char;
};
