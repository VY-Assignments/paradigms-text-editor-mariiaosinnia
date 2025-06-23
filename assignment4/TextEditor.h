#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H
#include "CaesarCipher.h"
#include "Cursor.h"
#include "Line.h"


class TextEditor {
public:
    TextEditor();
    ~TextEditor();

    void init_text();
    void free_text();
    void append_text(char* input);
    void add_line(int type, bool is_completed);
    void print_text();
    void save_to_file(const char* file_name);
    void load_from_file(const char* file_name);
    void insert_text(int line_index, int char_index, const char* insert_str);
    void search_text(const char* query);
    void clear_console();
    void print_menu();

    void delete_text(int num_symbols);
    void undo();
    void redo();
    void cut(int num_symbols);
    void copy(int num_symbols);
    void paste();
    void insert_replacement(char* input);
    void encrypt_text(int key);
    void decrypt_text(int key);
    void save_encrypted_text(char* file_path);
    void load_encrypted_text(char* file_path);
    void add_line_to_text(Line* new_line);

private:
    Line** lines;
    int num_lines;
    int allocated_lines;
    char* clipboard;

    int current_tab = 0;
    int tabs_count = 1;

    uint8_t** encrypted_buffers;
    uint32_t* encrypted_lengths;

    Cursor cursor;
    CaesarCipher caesar_cipher;
};

#endif
