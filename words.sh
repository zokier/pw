#!/bin/sh

WORD_COUNT=$(wc -l "$1"|awk '{print $1}')
WORD_ENTROPY=$(printf "scale=5;l(%d)/l(2)\n" "$WORD_COUNT" | bc -l)

printf "#define WORD_ENTROPY %f\n" "$WORD_ENTROPY"
printf "#define WORD_COUNT %d\n" "$WORD_COUNT"
printf "\n"
printf "const char *WORDS[] = {\n"
awk '{printf "%s\"%s \"",sep,$2; sep=",\n"}' "$1"
printf "\n};\n"
