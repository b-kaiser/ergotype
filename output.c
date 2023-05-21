#include <stdio.h>

#include "line.h"

#include "output.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define NORMAL "\x1b[0m"


void print_line(line l) {
	for (int i = 0; i < l.n_chars; i++) {
		printf("%c", l.chars[i]);
	}
	printf("\n");

}

void print_whitespace() {
	printf(" ");
}

void print_correct(char d) {
	printf("\33[1A");
	printf( GREEN "%c" NORMAL, d);
	printf("\33[1B");
	printf("\33[1D");
	printf(" ");
}

void print_incorrect(char got, char expected) {
	printf("\33[1A");
	printf( RED "%c" NORMAL, expected);
	printf("\33[1B");
	printf("\33[1D");
	
	printf("%c", got);
}
