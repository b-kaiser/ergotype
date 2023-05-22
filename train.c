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

	char line_chars_01[max_line_length];
	char line_chars_02[max_line_length];
	char line_chars_03[max_line_length];
	char line_chars_04[max_line_length];
	
	line l_01 = {
		line_chars_01,
		max_line_length,
		max_word_num,
		max_word_length,
		0
	};
	
	line l_02 = {
		line_chars_02,
		max_line_length,
		max_word_num,
		max_word_length,
		0
	};
	
	line l_03 = {
		line_chars_03,
		max_line_length,
		max_word_num,
		max_word_length,
		0
	};
	
	line l_04 = {
		line_chars_04,
		max_line_length,
		max_word_num,
		max_word_length,
		0
	};

	line * current = &l_01;
	line * next = &l_02;
	line *middle = &l_03;
	line *last = &l_04;
	
	create_line(current, e);
	create_line(next, e);
	create_line(middle, e);
	create_line(last, e);
	int remaining_lines = 1;
	while (n_perfect_lines < remaining_lines) {
		print_register_following_lines(next, middle, last);

		int n_incorrect = check_line(*current);
		line * tmp = current;
		current = next;
		next = middle;
		middle = last;
		last = tmp;
		create_line(last, e);

		if (n_incorrect > 0) {
			if ( n_imperfect_lines == 0 ) {
				remaining_lines = 3;
			}
			
			n_imperfect_lines++;
			n_perfect_lines = 0;
		} else {
			if (n_imperfect_lines == 0) {
				break;
			}
			
			n_perfect_lines++;
		}
		if ( n_perfect_lines != remaining_lines ) {
			int n_pending_lines =
				remaining_lines - n_perfect_lines -1;
			print_remove_following_line(
					next,
				       	middle,
					n_pending_lines);
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
		do_exercise(e);
		
		if (e.n_rows < 2) {
			break;
		} else {
			e.use_only_one_row = false; 
			//printw("Now the same training with mixed words.\n");
		}
	}

}

int level = 0;

void train(skillset * s) {
	create_new_exercises(s);
	while ( s->current_new_exercise < s->n_new ) {
		exercise e = get_next_exercise(s);
		level++;
		mvprintw(6, (COLS / 2) - 5, "Level %4d", level);
		refresh();
		train_exercise(e);
	}
}

