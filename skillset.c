#include <stddef.h>
#include <stdlib.h>

#include "skillset.h"
#include "exercise.h"

skillset empty_skillset = {
	.hand = 0,
	.rows = NULL,
	.n_rows = 0,
	.completed_exercises = NULL,
	.n_completed = 0,
	.new_exercises = NULL,
	.n_new = 0,
};

int get_n_of_positions(skillset * s) {
	int n_positions = 0;
	for ( int i = 0 ; i < s->n_rows ; i++ ) {
		latitude p = s->rows[i].position;
		int j = 0;
		for ( ; j < i ; j++) {
			latitude p_old = s->rows[j].position;
			if ( p == p_old ) {
				break;
			}
		}
		if ( j == i ) {
			n_positions++;
		}
	}
	return n_positions;
}

bool add_homerow(skillset * s) {
	int initial_n_of_positions = get_n_of_positions(s);


	s->rows = realloc(s->rows, ((s->n_rows)+1)*sizeof(*rows));
	if (s->hand == left) {
		s->rows[s->n_rows] = ordered_left_hand_rows[s->n_rows];
	} else {
		s->rows[s->n_rows] = ordered_right_hand_rows[s->n_rows];
	}
	s->n_rows++;

	int new_n_of_positions = get_n_of_positions(s);

	return (new_n_of_positions > initial_n_of_positions);


}

void create_latest_new_row_exercise(skillset * s) {
	exercise * e = &(s->new_exercises[(s->n_new)++]);
	e->rows = malloc(1 * sizeof(*(e->rows)));
	e->rows[0] = s->rows[(s->n_rows)-1];
	e->n_rows = 1;
	e->use_only_one_row = true;
}

void move_new_exercises_to_completed(skillset *s) {
	int new_n_completed = (s->n_completed)+(s->n_new); 
	s->completed_exercises = realloc(
		s->completed_exercises,
		new_n_completed *sizeof(*(s->completed_exercises)));
	int j = 0;
	for ( int i = s->n_completed; i < new_n_completed; i++) {
		s->completed_exercises[i]=
			s->new_exercises[j++];
	}
	if ( j != s -> n_new ) {
		abort();
	}

	s->n_new = 0;
	s->n_completed = new_n_completed;
}

void perlocate(exercise * e, int j, int i) {
	if ( j <= i ) {
		abort();
	}

	exercise tmp = e[j];
	for ( int k = j; k > i; k--) {
		e[k] = e[k-1];
	}
	e[i] = tmp;
}


void move_same_height_exercises_to_end(exercise *e, int n_e) {
	for ( int i = 0; i < n_e; i++) {
		if ( is_same_height_exercise(e[i]) ) {
			int j = i;
			for ( ; j < n_e; j++) {
				if ( ! is_same_height_exercise(e[j]) ) {
					break;
				}
			}
			if ( j == n_e ) {
				break;
			}
			perlocate(e, j, i);	
		}
	}
}

void create_new_exercises_from_completed(skillset *s) {

	for (int i = 0 ; i < s->n_completed; i++) {
		exercise * e_new = &(s->new_exercises[(s->n_new)++]);
		exercise * e_old = &(s->completed_exercises[i]);
		e_new->n_rows = (e_old->n_rows)+1;
		e_new->rows = malloc( ((e_old->n_rows)+1) *
			sizeof(*(e_new->rows)));
		for ( int j = 0; j < e_old->n_rows; j++) {
			(e_new->rows)[j] = (e_old->rows)[j];
		}
		(e_new->rows)[e_old->n_rows] = s->rows[(s->n_rows)-1];
		e_new->use_only_one_row = true;
	}

	move_same_height_exercises_to_end(s->new_exercises, s->n_new);

}

void create_new_exercises(skillset * s) {
	if ( s->n_new == 0) {
		s->new_exercises = malloc(1 * sizeof(*(s->new_exercises)));
		create_latest_new_row_exercise(s);
	} else {
		move_new_exercises_to_completed(s);
		int new_n_new = s->n_completed+1;
		s->new_exercises = realloc(s->new_exercises,
			(new_n_new)*sizeof(*(s->new_exercises)));

		create_latest_new_row_exercise(s);
		create_new_exercises_from_completed(s);

	}
	s->current_new_exercise = 0;
}

exercise get_next_exercise(skillset * s) {
	return s->new_exercises[(s->current_new_exercise)++];
}
