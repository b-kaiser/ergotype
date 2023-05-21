#ifndef LINE_H
#define LINE_H

#include "exercise.h"

typedef struct {
	char * chars;
	int max_line_length;
	int max_word_num;
	int max_word_length;
	int n_chars;
} line;

void create_line(line * l, exercise e);

#endif // LINE_H
