#include "TextEditor.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include "Line.h"
#include "TextLine.h"

int main() {
    TextEditor text_editor;
    text_editor.init_text();

    text_editor.print_menu();

    while (1) {
        int command;
        char buffer[10];
        printf("Enter command number > ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &command);

        switch (command) {
            case 0:
                printf("Goodbye!\n");
                text_editor.free_text();
                return 0;

            case 1: {
                char input[256];
                printf("Enter text to append: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                text_editor.append_text(input);
                break;
            }

            case 2:
                text_editor.add_line();
                printf("New line is started");
                break;

            case 3: {
                char filename[100];
                printf("Enter the file name for saving: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                text_editor.save_to_file(filename);
                break;
            }

            case 4: {
                char filename[100];
                printf("Enter the file name for loading: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                text_editor.load_from_file(filename);
                break;
            }

            case 5:
                text_editor.print_text();
                break;

            case 6: {
                int line, index;
                char temp[20];
                char insert_str[256];
                printf("Choose line and index: ");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%d %d", &line, &index);
                printf("Enter text to insert: ");
                fgets(insert_str, sizeof(insert_str), stdin);
                insert_str[strcspn(insert_str, "\n")] = '\0';
                text_editor.insert_text(line, index, insert_str);
                break;
            }

            case 7: {
                char query[100];
                printf("Enter text to search: ");
                fgets(query, sizeof(query), stdin);
                query[strcspn(query, "\n")] = '\0';
                text_editor.search_text(query);
                break;
            }

            case 8: {
                int count;
                char temp[20];
                printf("Number of symbols to delete: ");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%d", &count);
                text_editor.delete_text(count);
                break;
            }

            case 9:
                text_editor.undo();
                break;

            case 10:
                text_editor.redo();
                break;

            case 11: {
                int count;
                char temp[20];
                printf("Number of symbols to cut: ");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%d", &count);
                text_editor.cut(count);
                break;
            }

            case 12:
                text_editor.paste();
                break;

            case 13: {
                int count;
                char temp[20];
                printf("Number of symbols to copy: ");
                fgets(temp, sizeof(temp), stdin);
                sscanf(temp, "%d", &count);
                text_editor.copy(count);
                break;
            }

            case 14: {
                char input[256];
                printf("Write text to insert (with replacement): ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                text_editor.insert_replacement(input);
                break;
            }

            default:
                printf("The command is not implemented\n");
        }
    }

    return 0;
}
