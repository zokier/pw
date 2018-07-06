#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
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
            pw_entropy += WORD_ENTROPY;
            int res = fputs(WORDS[rand], stdout);
            if (res < 0) return -1;
            res = fputc(' ', stdout);
            if (res < 0) return -1;
        }
    }
    fputc('\n', stdout);
    return 0;
}
