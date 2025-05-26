//
// Created by Legion on 26.05.2025.
//

#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H



class TextEditor {
public:
    TextEditor();
    ~TextEditor();

    void init_text();
    void free_text();
    void append_text(const char* input);
    void add_line();
    void print_text();
    void save_to_file(const char* file_name);
    void load_from_file(const char* file_name);
    void insert_text(int line_index, int char_index, const char* insert_str);
    void search_text(const char* query);
    void clear_console();
    void print_menu();
private:
    char** lines;
    int* line_lengths;
    int num_lines;
    int allocated_lines;
};



#endif //TEXTEDITOR_H
