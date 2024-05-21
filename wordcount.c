#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void count_characters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        return;
    }

    int character_count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        character_count++;
    }
    fclose(file);
    printf("字符数：%d\n", character_count);
}

void count_words(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        return;
    }

    int word_count = 0;
    char ch;
    char prev_ch = ' ';
    while ((ch = fgetc(file)) != EOF) {
        if ((ch == ' ' || ch == '\t' || ch == '\n' || ch == ',') &&
            !(prev_ch == ' ' || prev_ch == '\t' || prev_ch == '\n' || prev_ch == ',')) {
            word_count++;
        }
        prev_ch = ch;
    }
    // If the file does not end with a space or newline, count the last word
    if (!(prev_ch == ' ' || prev_ch == '\t' || prev_ch == '\n' || prev_ch == ',')) {
        word_count++;
    }
    fclose(file);
    printf("单词数：%d\n", word_count);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s -c|-w input_file_name\n", argv[0]);
        return 1;
    }

    const char *parameter = argv[1];
    const char *input_file_name = argv[2];

    if (strcmp(parameter, "-c") == 0) {
        count_characters(input_file_name);
    } else if (strcmp(parameter, "-w") == 0) {
        count_words(input_file_name);
    } else {
        fprintf(stderr, "Invalid parameter. Use -c for character count or -w for word count.\n");
        return 1;
    }

    return 0;
}
