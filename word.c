#include <stdbool.h>
#include <stdlib.h>

#include "exercise.h"
#include "homerows.h"

#include "word.h"

void create_random_word(char * word, int n_chars, exercise e) {
	bool use_only_one_row;
	if (e.use_only_one_row) {
		use_only_one_row = true;
	} else {
		// Even if we want to train mixed words, roughly every
		// second word should be from a single row in order to
		// train multiple fingerings simultaneously.
		use_only_one_row = (rand() % 2 == 0) ? true : false;
	}
	for (int i = 0; i < n_chars; i++) {
		int j = (i != 0 && use_only_one_row) ?
			j : rand() % e.n_rows;
		char c = get_random_char(&e.rows[j]);
		word[i] = c;
	}
}
