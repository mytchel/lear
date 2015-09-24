/*
 *          DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 * Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 * TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 * 0. You just DO WHAT THE FUCK YOU WANT TO.
 * 
 */

#include <stdio.h>

#define LEN 512
#define CHAR_PER_LINE 70

int spaces(char *string) {
    int i, s;
    for (i = 0, s = 0; string[i]; i++)
        if (string[i] == ' ') s++;
    return s;
}

void move_chars_right(char *string, int p) {
    int i;
    for (i = LEN-1; i >= p; i--)
        string[i] = string[i - 1];
}

void format(char *line) {
    int i, j, k;
    for (i = 0; line[i]; i++) {
        if (i > CHAR_PER_LINE) {
            // Go back and find a space to word break
            for (k = i - 30; i > k; i--)
                if (line[i] == ' ')
                    break;

            move_chars_right(line, i);
            line[i] = '\n';
            
            for (j = 1; j < 5; j++) {
                move_chars_right(line, i + j);
                line[i + j] = ' ';
            }
            i += CHAR_PER_LINE;
        }
    }
}

int main() {
    char line[LEN];
    FILE *lear;
    int delay;

    lear = fopen(LEARPATH, "r");

    while (fgets(line, sizeof(line), lear) != NULL) {
        line[LEN-1] = '\0';
        format(line);
        printf("%s\n", line);
        delay = spaces(line) / 4;
        sleep(delay);
    }
}
