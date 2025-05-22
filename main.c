#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    Text* text = malloc(sizeof(Text));
    init_text(text);

    while (1) {
        clear_console();
        print_menu();

        int command;
        char buffer[10];
        printf("> ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &command);

        switch (command) {
            case 0:
                printf("Goodbye!\n");
                free_text(text);
                return 0;

            case 1: {
                char input[256];
                printf("Enter text to append: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                append_text(text, input);
                break;
            }

            case 2:
                add_line(text);
                printf("New line is started\n");
                break;

            case 3: {
                char filename[100];
                printf("Enter the file name for saving: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                save_to_file(text, filename);
                break;
            }

            case 4: {
                char filename[100];
                printf("Enter the file name for loading: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                load_from_file(text, filename);
                break;
            }

            case 5:
                print_text(text);
                break;

            case 6: {
                int line, index;
                char insert_str[256];
                printf("Choose line and index: ");
                scanf("%d %d", &line, &index);
                getchar();
                printf("Enter text to insert: ");
                fgets(insert_str, sizeof(insert_str), stdin);
                insert_str[strcspn(insert_str, "\n")] = '\0';
                insert_text(text, line, index, insert_str);
                break;
            }

            case 7: {
                char query[100];
                printf("Enter text to search: ");
                fgets(query, sizeof(query), stdin);
                query[strcspn(query, "\n")] = '\0';
                search_text(text, query);
                break;
            }

            default:
                printf("The command is not implemented\n");
        }
        printf("\nPress Enter to continue");
        getchar();
    }

    return 0;
}



