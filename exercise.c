#include "exercise.h"


bool is_same_height_exercise(exercise e) {
	for ( int i = 0 ; i < e.n_rows ; i++ ) {
		altitude h = e.rows[i].height;
		for ( int j = i+1 ; j < e.n_rows; j++) {
			if (e.rows[j].height == h ) {
				return true;
			}
		}
	}
	return false;
}

