#ifndef HEADER_H
#define HEADER_H

typedef struct Text {
    char** lines;
    int* line_lengths;
    int num_lines;
    int allocated_lines;
} Text;

void init_text(Text* text);
void free_text(Text* text);
void append_text(Text* text, char* input);
void add_line(Text* text);
void print_text(Text* text);
void save_to_file(Text* text, char* file_name);
void load_from_file(Text* text, char* file_name);
void insert_text(Text* text, int line_index, int char_index, char* insert_str);
void search_text(Text* text, char* query);
void clear_console();
void print_menu();

#endif //HEADER_H
