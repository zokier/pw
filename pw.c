#include <stdio.h>
#include <stdint.h>
#include <sys/random.h>

#include "words.h"

#define RANDOM_LEN 128
#define MIN_ENTROPY 64.0

int main(int argc, char **argv) {
    uint16_t random_bytes[RANDOM_LEN] = {0};
    double pw_entropy = 0.0;
    getrandom(random_bytes, RANDOM_LEN*2, 0);
    size_t rand_mask = (2 << (size_t)WORD_ENTROPY) - 1;
    for (size_t random_index = 0; pw_entropy < MIN_ENTROPY; random_index++) {
        if (random_index >= RANDOM_LEN) return -1;
        size_t rand = random_bytes[random_index];
        rand = rand & rand_mask;
        if (rand < WORD_COUNT) {
            const char *word = WORDS[rand];
            // skip space at the beginning for the first word
            if (pw_entropy == 0.0) word++;
            int res = fputs(word, stdout);
            if (res < 0) return -1;
            pw_entropy += WORD_ENTROPY;
        }
    }
    fputc('\n', stdout);
    return 0;
}
