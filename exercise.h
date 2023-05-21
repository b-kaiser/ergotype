#ifndef EXERCISE_H
#define EXERCISE_H

#include <stdbool.h>

#include "homerows.h"

typedef struct {
	homerow * rows;
	int n_rows;
	bool use_only_one_row;
} exercise;

bool is_same_height_exercise(exercise e);

#endif // EXERCISE_H
