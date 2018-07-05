#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/random.h>

#include "words.h"

#define RANDOM_LEN 64
#define LINE_LEN 256
#define MIN_ENTROPY 64.0

ssize_t append_line(char *line, const char *word, size_t line_pos) {
    size_t word_len = strlen(word);
    if (word_len+line_pos+1 >= LINE_LEN) {
        return -1;
    }
    memcpy(line+line_pos, word, word_len);
    line_pos += word_len;
    line[line_pos++] = ' ';
    return line_pos;
}

int main(int argc, char **argv) {
    char line[LINE_LEN] = {0};
    size_t line_pos = 0;
    uint16_t random_bytes[RANDOM_LEN] = {0};
    double pw_entropy = 0.0;
    size_t random_index = 0;
    size_t random_available = 0;
    uint16_t rand_mask = (2 << (size_t)WORD_ENTROPY) - 1;
    while (pw_entropy < MIN_ENTROPY) {
        if (2*(random_index+1) >= random_available) {
            ssize_t res = getrandom(random_bytes, RANDOM_LEN, 0);
            if (res < 0) {
                return -1;
            }
	    random_available = res;
            random_index = 0;
        }
        uint16_t rand = random_bytes[random_index++];
        rand = rand & rand_mask;
        if (rand < WORD_COUNT) {
            pw_entropy += WORD_ENTROPY;
            ssize_t res = append_line(line, WORDS[rand], line_pos);
            if (res < 0) {
                return -1;
            }
	    line_pos = res;
        }
    }
    puts(line);
    return 0;
}
