#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/random.h>

#include "words.h"

#define RANDOM_LEN 64
#define MIN_ENTROPY 64.0

int main(int argc, char **argv) {
    uint16_t random_bytes[RANDOM_LEN/2] = {0};
    double pw_entropy = 0.0;
    ssize_t random_index = 0;
    ssize_t random_available = 0;
    size_t rand_mask = (2 << (size_t)WORD_ENTROPY) - 1;
    while (pw_entropy < MIN_ENTROPY) {
        if (2*(random_index+1) >= random_available) {
            // getrandom will not fail for requests smaller than 256 bytes
            random_available = getrandom(random_bytes, RANDOM_LEN, 0);
            random_index = 0;
            continue;
        }
        size_t rand = random_bytes[random_index++];
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
