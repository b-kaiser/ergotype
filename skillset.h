#ifndef SKILLSET_H
#define SKILLSET_H

#include <stdbool.h>

#include "homerows.h"
#include "exercise.h"

typedef struct {
	side hand;
	homerow * rows;
	int n_rows;
	exercise * completed_exercises;
	int n_completed;
	exercise * new_exercises;
	int current_new_exercise;
	int n_new;
} skillset;

extern skillset empty_skillset;

bool add_homerow(skillset * s);

void create_new_exercises(skillset * s);

exercise get_next_exercise(skillset * s);

#endif // SKILLSET_H
