#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>


#include "homerows.h"
#include "exercise.h"
#include "skillset.h"
#include "input.h"
#include "word.h"
#include "line.h"
#include "output.h"

int check_line(line l) {
	int n_correct = 0;
	int n_incorrect = 0;
	print_line(l);
	int penalty = 1; 
	while (penalty > 0) {
		int n_mistakes = 0;
		reprint_line(l);
	  	for (int i = 0; i < l.n_chars; i++ ) {
			if (l.chars[i] == ' ') {
				print_whitespace();
				continue;
			}
			char d;
			if ( obtain_key(&d) != 0 ) {
				return 0;
			}
			if (d == l.chars[i]) {
				print_correct(d);
			} else {
				if ( penalty < 3 ) {
					penalty = 3;
				} else {
					if (penalty < 9) {
						penalty++;
					}
				}
				print_incorrect(d,l.chars[i], penalty);
				n_mistakes++;
			}
		}
		if (n_mistakes > 0) {
			n_correct = 0;
			print_lower_penalty(penalty);
			n_incorrect++;
		} else {
			n_correct++;
			if (n_incorrect == 0) {
				break;
			} else {
				print_lower_penalty(--penalty);
			}
		}
		//printw("\n\n");
	}
	print_remove_penalty();
	//printw("Completed this line.\n");
	//printw("\n\n");
	return n_incorrect;
}

int do_exercise(exercise e) {
	int max_line_length = 72;
	int max_word_length = 4;
	int max_word_num = 5;


	int n_perfect_lines = 0;
	int n_imperfect_lines = 0;

	print_fingering(e);

	while (n_perfect_lines < 3) {
		char line_chars[max_line_length];
	
		line l = {
			line_chars,
			max_line_length,
			max_word_num,
			max_word_length,
			0
		};
	
	
		create_line(&l, e);
		int n_incorrect = check_line(l);
		if (n_incorrect > 0) {
			//printw("\nYou made some mistakes with this line. You need to get it three lines correct in a row now.\n");
			n_imperfect_lines++;
			n_perfect_lines = 0;
		} else {
			n_perfect_lines++;
			if (n_imperfect_lines == 0) {
				//printw("\nYou completed this exercise perfectly on the first try!\n");
				break;
			}
		}
	}
	return n_imperfect_lines;	

}

void train_exercise(exercise e) {
	if ( true ) {
		//printw("Training the following rows\n\n");
		for ( int i = 0 ; i < e.n_rows; i++) {
			//homerow h = e.rows[i];
			//printw("Hand: %d Height: %d Position: %d "
			//	"Chars: %c %c %c %c\n\n",
			//	h.hand, h.height, h.position,
			//	h.chars.index,
			//	h.chars.middle,
			//	h.chars.ring,
			//	h.chars.pinky);
		}
		if ( false ) {
			char d = getchar();
			if ( d == 's' ) {
				return;
			}
		}
	}	

	e.use_only_one_row = true;
	for (int i = 0; i < 2; i++) {
		int n_perfect_exercises = 0;
		int n_imperfect_exercises = 0;
	
		while (n_perfect_exercises < 3) {
			int n_imperfect_lines = do_exercise(e);
			if (n_imperfect_lines > 0) {
				n_perfect_exercises = 0;
				n_imperfect_exercises++;
			} else {
				n_perfect_exercises++;
				if (n_imperfect_exercises == 0) {
					break;
				}
			}
		}
		
		if (e.n_rows < 2) {
			break;
		} else {
			e.use_only_one_row = false; 
			//printw("Now the same training with mixed words.\n");
		}
	}

}

void train(skillset * s) {
	create_new_exercises(s);
	while ( s->current_new_exercise < s->n_new ) {
		exercise e = get_next_exercise(s);
		train_exercise(e);
	}
}

