#include "word.h"
#include "exercise.h"

#include "line.h"

void create_line(line * l, exercise e) {
	l->n_chars = 0;
	for (int j = 0; j < l->max_word_num; j++) {
		if ( l->max_line_length - l->n_chars <= l->max_word_length) {
			break;
		}
		if ( j != 0) {
			l->chars[(l->n_chars)++] = ' ';
		}
  		char word[l->max_word_length];
	 	create_random_word(word, l->max_word_length, e); 
  		for (int i = 0; i < l->max_word_length; i++ ) {
			l->chars[(l->n_chars)++]=word[i];
		}
	}
}
