CC ?= cc
WORDLIST ?= eff_large_wordlist.txt
CFLAGS += -Wall -Wextra -pedantic -std=c11

all: pw

eff_large_wordlist.txt:
	curl -O https://www.eff.org/files/2016/07/18/eff_large_wordlist.txt

eff_short_wordlist_1.txt:
	curl -O https://www.eff.org/files/2016/09/08/eff_short_wordlist_1.txt

eff_short_wordlist_2_0.txt:
	curl -O https://www.eff.org/files/2016/09/08/eff_short_wordlist_2_0.txt

words.h: $(WORDLIST)
	./words.sh $< > words.h

pw: pw.c words.h
	$(CC) $(CFLAGS) -o $@ $<

run: pw
	./$<

clean:
	rm -f pw

dist-clean: clean
	rm -f eff_*.txt
	rm -f words.h
