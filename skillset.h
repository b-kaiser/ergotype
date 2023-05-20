#ifndef SKILLSET_H
#define SKILLSET_H

#include "homerows.h"

typedef struct {
	homerow * rows;
	int n_rows;
} skillset;

skillset empty_skillset;

void add_homerow(skillset * s) {
	s->rows = realloc(s->rows, ((s->n_rows)+1)*sizeof(*rows));
	s->rows[s->n_rows] = rows[s->n_rows];
	s->n_rows++;
}

exercise get_next_exercise(skillset * s) {
	exercise e = { s-> rows, s->n_rows, true};
	return e;
}

#endif // SKILLSET_H
