#include "TextEditor.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include "Line.h"
#include "TextLine.h"
#include "CaesarCipher.h"

const int MAX_TABS = 10;

TextEditor tabs[MAX_TABS];
int current_tab = 0;
int tabs_count = 1;

void print_tabs_menu() {
    printf("Current tab: %d, total tabs: %d\n", current_tab + 1, tabs_count);
    printf("Commands:\n"
           "11 - Create new tab\n"
           "12 - Switch tab\n"
           "13 - Close current tab\n");
}

int main() {
    tabs[0].init_text();

    tabs[0].print_menu();
    while (1) {
        int command;
        char buffer[10];
        printf("Enter command number > ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &command);

        TextEditor& text_editor = tabs[current_tab];

        switch (command) {
            case 0:
                printf("Goodbye!\n");
                for (int i = 0; i < tabs_count; ++i) {
                    tabs[i].free_text();
                }
                return 0;

            case 1: {
                char input[256];
                printf("Enter text to append: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                text_editor.append_text(input);
                break;
            }

            case 2: {
                printf("Choose line type:\n1 - Text\n2 - Contact\n3 - Checklist\n> ");
                int type;
                scanf("%d", &type);
                while (getchar() != '\n');

                bool is_completed = false;
                if (type == 3) {
                    printf("Is the task completed? (1 = Yes, 0 = No): ");
                    int temp;
                    scanf("%d", &temp);
                    while (getchar() != '\n');
                    is_completed = (temp != 0);
                }

                text_editor.add_line(type, is_completed);
                printf("New line added\n");
                break;
            }

            case 3: {
                char filename[100];
                printf("Enter the file name for saving: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                text_editor.save_to_file(filename);
                break;
            }

            case 5:
                text_editor.print_text();
                break;

            case 6: {
                int key;
                printf("Enter encryption key: ");
                scanf("%d", &key);
                while (getchar() != '\n');
                text_editor.encrypt_text(key);
                printf("Text encrypted successfully.\n");
                break;
            }

            case 7: {
                char filename[100];
                printf("Enter file name to save encrypted text: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                text_editor.save_encrypted_text(filename);
                printf("Encrypted text saved.\n");
                break;
            }

            case 8: {
                char filename[100];
                printf("Enter file name to load encrypted text: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                text_editor.load_encrypted_text(filename);
                break;
            }

            case 9: {
                int key;
                printf("Enter decryption key: ");
                scanf("%d", &key);
                while (getchar() != '\n');
                text_editor.decrypt_text(key);
                printf("Text decrypted.\n");
                break;
            }
            case 10: {
                print_tabs_menu();
                break;;
            }

            case 11:
                if (tabs_count < MAX_TABS) {
                    tabs[tabs_count].init_text();
                    current_tab = tabs_count;
                    tabs_count++;
                    printf("New tab created. Current tab: %d\n", current_tab + 1);
                } else {
                    printf("Maximum tabs reached.\n");
                }
                break;

            case 12: {
                int new_tab;
                printf("Enter tab number to switch (1-%d): ", tabs_count);
                scanf("%d", &new_tab);
                while(getchar() != '\n');
                if (new_tab >= 1 && new_tab <= tabs_count) {
                    current_tab = new_tab - 1;
                    printf("Switched to tab %d\n", new_tab);
                } else {
                    printf("Invalid tab number.\n");
                }
                break;
            }

            case 13: {
                if (tabs_count > 1) {
                    tabs[current_tab].free_text();

                    for (int i = current_tab; i < tabs_count - 1; i++) {
                        tabs[i] = std::move(tabs[i + 1]);
                    }
                    tabs_count--;
                    if (current_tab >= tabs_count) current_tab = tabs_count - 1;
                    printf("Closed tab. Current tab: %d\n", current_tab + 1);
                } else {
                    printf("Cannot close the last tab.\n");
                }
                break;
            }
            case 14: {
                int mode;
                char in_path[256], out_path[256];
                int key;

                printf("Choose operation:\n1 - Encrypt\n2 - Decrypt\n> ");
                scanf("%d", &mode);
                while (getchar() != '\n');

                printf("Enter input file path: ");
                fgets(in_path, sizeof(in_path), stdin);
                in_path[strcspn(in_path, "\n")] = '\0';

                printf("Enter output file path: ");
                fgets(out_path, sizeof(out_path), stdin);
                out_path[strcspn(out_path, "\n")] = '\0';

                printf("Enter key: ");
                scanf("%d", &key);
                while (getchar() != '\n');

                FILE* fin = fopen(in_path, "r");
                if (!fin) {
                    printf("Cannot open input file.\n");
                    break;
                }

                fseek(fin, 0, SEEK_END);
                long size = ftell(fin);
                rewind(fin);

                char* buffer = new char[size];
                fread(buffer, 1, size, fin);
                fclose(fin);

                CaesarCipher cipher("caesar.dll");
                char* result = nullptr;

                if (mode == 1)
                    result = cipher.encrypt(buffer, key, size);
                else if (mode == 2)
                    result = cipher.decrypt(buffer, key, size);

                FILE* fout = fopen(out_path, "w");
                if (fout && result) {
                    fwrite(result, 1, size, fout);
                    fclose(fout);
                    printf("Done.\n");
                } else {
                    printf("Failed to write output.\n");
                }

                delete[] buffer;
                break;
            }
            default:
                printf("The command is not implemented\n");
        }
    }

    return 0;
}
