#include "TextEditor.h"
#include <iostream>
#include <cstring>
#include <cstdio>

#include "CheckListLine.h"
#include "ContactLine.h"
#include "TextLine.h"

const int INITIAL_LINE_CAPACITY = 10;

TextEditor::TextEditor(): lines(nullptr), encrypted_buffers(nullptr), encrypted_lengths(nullptr), num_lines(0), allocated_lines(0),
caesar_cipher("caesar.dll"), clipboard(nullptr){
    init_text();
}

TextEditor::~TextEditor() {
    if (lines) {
        for (int i = 0; i < num_lines; ++i) {
            if (lines[i]) delete lines[i];
        }
        delete[] lines;
    }

    delete[] clipboard;

    if (encrypted_buffers) {
        for (int i = 0; i < num_lines; ++i) {
            if (encrypted_buffers[i]) delete[] encrypted_buffers[i];
        }
        delete[] encrypted_buffers;
    }
    delete[] encrypted_lengths;
}

void TextEditor::free_text() {
    if (lines) {
        for (int i = 0; i < num_lines; ++i) {
            delete lines[i];
        }
        delete[] lines;
        lines = nullptr;
    }

    if (encrypted_buffers) {
        for (int i = 0; i < num_lines; ++i) {
            delete[] encrypted_buffers[i];
        }
        delete[] encrypted_buffers;
        encrypted_buffers = nullptr;
    }

    if (encrypted_lengths) {
        delete[] encrypted_lengths;
        encrypted_lengths = nullptr;
    }

    num_lines = 0;
    allocated_lines = 0;
}

void TextEditor::init_text() {
    allocated_lines = INITIAL_LINE_CAPACITY;
    num_lines = 0;

    lines = new Line*[allocated_lines];
}

void TextEditor::add_line(int type, bool is_completed) {
    Line* new_line = nullptr;

    if (type == 1) {
        new_line = new TextLine((char*) "");
    } else if (type == 2) {
        new_line = new ContactLine(std::string(""), std::string(""));;
    } else if (type == 3) {
        new_line = new CheckListLine((char*) "", is_completed);
    } else {
        printf("Unknown line type.\n");
        return;
    }

    if (num_lines == allocated_lines) {
        int new_allocated = allocated_lines * 2;
        Line** new_lines = new Line*[new_allocated];
        for (int i = 0; i < num_lines; ++i) {
            new_lines[i] = lines[i];
        }
        delete[] lines;
        lines = new_lines;
        allocated_lines = new_allocated;
    }


    lines[num_lines++] = new_line;
    cursor.set_line(num_lines - 1);
    cursor.set_char(0);
}

void TextEditor::append_text(char* input) {
    if (num_lines == 0) {
        add_line(1, false);
    }
    int line_idx = num_lines - 1;

    Line* current = lines[line_idx];
    if (strcmp(current->get_type(), "Text") == 0) {
        TextLine* text_line = (TextLine*)current;
        text_line->append_text(input);
        cursor.set_char(strlen(text_line->get_text()));
    }
    else {
        current->append_text(input);
    }
    cursor.set_line(line_idx);
}

void TextEditor::print_text() {
    for (int i = 0; i < num_lines; i++) {
        if (lines[i] != nullptr) {
            printf("%s\n", lines[i]->to_string());
        } else {
            printf("(nullptr line at index %d)\n", i);
        }
    }
}


void TextEditor::save_to_file(const char* file_name) {
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < num_lines; i++) {
        fputs(lines[i]->to_string(), file);
        fputc('\n', file);
    }

    fclose(file);
    printf("Text has been saved successfully\n");
}

void TextEditor::insert_text(int line_index, int char_index, const char* insert_str) {
    Line* line = lines[line_index];
    if (strcmp(line->get_type(), "Text") == 0) {
        ((TextLine*)line)->insert_text(char_index, insert_str);
        cursor.set_line(line_index);
        cursor.set_char(char_index + strlen(insert_str));
    } else {
        printf("Insert is only supported for text lines.\n");
    }
}

void TextEditor::search_text(const char* query) {
    int query_len = strlen(query);

    for (int i = 0; i < num_lines; ++i) {
        Line* line = lines[i];

        if (strcmp(line->get_type(), "Text") != 0) {
            continue;
        }

        char* text = ((TextLine*)line)->get_text();
        int line_len = strlen(text);

        for (int j = 0; j <= line_len - query_len; ++j) {
            if (strncmp(text + j, query, query_len) == 0) {
                printf("Text is present in this position: %d %d\n", i, j);
            }
        }
    }
}

void TextEditor::clear_console() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void TextEditor::print_menu() {
    printf("Choose the command:\n"
           "0  - Exit\n"
           "1  - Append text\n"
           "2  - Start new line\n"
           "3  - Save to file\n"
           "5  - Print text\n"
           "6 - Encrypt text (requires key)\n"
           "7 - Save encrypted text to binary file\n"
           "8 - Load encrypted text from binary file\n"
           "9 - Decrypt text (requires key)\n"
           "14 - Encrypt/Decrypt external file\n");
}

//Assignment 2

void TextEditor::delete_text(int num_symbols) {
    int line_index = cursor.get_line();
    if (line_index < 0 || line_index >= num_lines) return;

    Line* line = lines[line_index];
    if (strcmp(line->get_type(), "Text") == 0) {
        TextLine* text_line = (TextLine*)line;
        text_line->delete_text(num_symbols);
        cursor.set_char(cursor.get_char() - num_symbols);
    } else {
        printf("Delete text supported only for text lines.\n");
    }
}

void TextEditor::insert_replacement(char* input) {
    int line_index = cursor.get_line();
    if (line_index < 0 || line_index >= num_lines) return;

    Line* line = lines[line_index];
    if (strcmp(line->get_type(), "Text") == 0) {
        TextLine* text_line = (TextLine*)line;
        text_line->insert_replacement(input);
        cursor.set_char(cursor.get_char());
    } else {
        printf("Insert replacement is supported only for text lines.\n");
    }
}

void TextEditor::encrypt_text(int key) {
    if (!lines || num_lines == 0) return;

    encrypted_buffers = new uint8_t*[num_lines]();
    encrypted_lengths = new uint32_t[num_lines]();

    for (int i = 0; i < num_lines; ++i) {
        if (!lines[i]) {
            encrypted_buffers[i] = nullptr;
            encrypted_lengths[i] = 0;
            continue;
        }

        uint32_t length;
        uint8_t* serialized = lines[i]->serialize(length);

        char* encrypted = caesar_cipher.encrypt((char*)serialized, key, length);

        if (encrypted) {
            uint32_t len = length;
            encrypted_buffers[i] = new uint8_t[len + 1];
            memcpy(encrypted_buffers[i], encrypted, len + 1);
            encrypted_lengths[i] = len;
        } else {
            encrypted_buffers[i] = nullptr;
            encrypted_lengths[i] = 0;
        }

        delete[] serialized;
    }
}


void TextEditor::save_encrypted_text(char* path) {
    FILE* f = fopen(path, "wb");
    if (!f || !encrypted_buffers || !encrypted_lengths) return;

    for (int i = 0; i < num_lines; ++i) {
        fwrite(&encrypted_lengths[i], sizeof(uint32_t), 1, f);
        fwrite(encrypted_buffers[i], encrypted_lengths[i], 1, f);
    }

    fclose(f);
}

void TextEditor::load_encrypted_text(char* file_path) {
    FILE* f = fopen(file_path, "rb");
    if (!f) {
        printf("Error opening file.\n");
        return;
    }

    free_text();

    encrypted_buffers = new uint8_t*[INITIAL_LINE_CAPACITY];
    encrypted_lengths = new uint32_t[INITIAL_LINE_CAPACITY];
    allocated_lines = INITIAL_LINE_CAPACITY;
    num_lines = 0;

    while (true) {
        uint32_t len;
        if (fread(&len, sizeof(uint32_t), 1, f) != 1) break;

        uint8_t* buffer = new uint8_t[len];
        if (fread(buffer, len, 1, f) != 1) {
            delete[] buffer;
            break;
        }

        if (num_lines == allocated_lines) {
            int new_allocated = allocated_lines * 2;

            uint8_t** new_buffers = new uint8_t*[new_allocated];
            uint32_t* new_lengths = new uint32_t[new_allocated];

            for (int i = 0; i < num_lines; ++i) {
                new_buffers[i] = encrypted_buffers[i];
                new_lengths[i] = encrypted_lengths[i];
            }

            delete[] encrypted_buffers;
            delete[] encrypted_lengths;

            encrypted_buffers = new_buffers;
            encrypted_lengths = new_lengths;
            allocated_lines = new_allocated;
        }


        encrypted_buffers[num_lines] = buffer;
        encrypted_lengths[num_lines] = len;
        num_lines++;
    }

    fclose(f);
    printf("Encrypted text loaded successfully.\n");
}

Line* create_line_from_buffer(uint8_t* data) {
    if (!data) return nullptr;

    if (data[0] == 'T') return new TextLine(nullptr);
    if (data[0] == 'C') return new ContactLine("", "");
    if (data[0] == '[') return new CheckListLine(nullptr, false);

    return nullptr;
}


void TextEditor::decrypt_text(int key) {
    Line** new_lines = new Line*[allocated_lines]();
    int valid_lines = 0;

    for (int i = 0; i < num_lines; ++i) {
    char* decrypted = caesar_cipher.decrypt((char*)encrypted_buffers[i], key, encrypted_lengths[i]);
        if (!decrypted) {
            new_lines[valid_lines++] = nullptr;
            continue;
        }

        Line* line = create_line_from_buffer((uint8_t*)decrypted);
        if (line) {
            line->deserialize((uint8_t*)decrypted, encrypted_lengths[i]);
            new_lines[valid_lines++] = line;
        } else {
            new_lines[valid_lines++] = nullptr;
        }
    }
    delete[] lines;
    lines = new_lines;
    num_lines = valid_lines;
}
