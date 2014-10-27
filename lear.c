#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define delay_from_spaces(X) (X / 3)
#define MIN_TIME  40
#define LEN 512
#define CHAR_PER_LINE 70

int stop_being_a_cunt = 0;
int reset = 0;
int delayed_for = 0;

int spaces(char *string) {
    int i, s;
    for (i = 0, s = 0; string[i]; i++)
        if (string[i] == ' ')
            s++;
    return s;
}

void move_chars_right(char string[LEN], int p) {
    int i;
    for (i = LEN - 1; i >= p; i--)
        string[i] = string[i - 1];
    string[LEN - 1] = '\0';
}

void format(char line[LEN]) {
    int i, j, k;
    for (i = 0; line[i]; i++) {
        if (i > CHAR_PER_LINE) {
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

void sigintHandler(int sig_num) {
    if (delayed_for >= MIN_TIME)
        stop_being_a_cunt = 1;
    else {
        reset = 1;
        
        system("/usr/bin/clear");
        printf("Do you not appreciate this? Have another read. At least read for another %i seconds.\n", MIN_TIME - delayed_for);
        sleep(3);
    }
}

int main() {
    char line[LEN];
    FILE *lear;
    int delay;

    signal(SIGINT, sigintHandler);
    lear = fopen("/lib/lear", "r");

    while (!stop_being_a_cunt && fgets(line, sizeof(line), lear) != NULL) {
        if (reset) {
            fseek(lear, 0, SEEK_SET);
            system("/usr/bin/clear");
            reset = 0;
            continue;
        }

        format(line);
        printf("%s\n", line);
        delay = delay_from_spaces(spaces(line));
        sleep(delay);
        delayed_for += delay;
    }
}
