#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H
#include "CaesarCipher.h"
#include "Cursor.h"
#include "Stack.h"
#include "Line.h"


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

    void delete_text(int num_symbols);
    void undo();
    void redo();
    void cut(int num_symbols);
    void copy(int num_symbols);
    void paste();
    void insert_replacement(char* input);
    void encrypt_text();
    void decrypt_text();
    void save_encrypted_text(char* file_path);
    void load_encrypted_text(char* file_path);

private:
    Line** lines;
    int num_lines;
    int allocated_lines;
    char* clipboard;

    Cursor cursor;
    Stack undo_stack;
    Stack redo_stack;
    CaesarCipher caesar_cipher;
};

#endif
