#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>


#include "homerows.h"
#include "exercise.h"
#include "skillset.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define NORMAL "\x1b[0m"

typedef struct {
	char * chars;
	int max_line_length;
	int max_word_num;
	int max_word_length;
	int n_chars;
} line;


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

int check_line(line l) {
	int n_correct = 0;
	int n_incorrect = 0;
	while (n_correct < 3) {
		int n_mistakes = 0;
		for (int i = 0; i < l.n_chars; i++) {
			printf("%c", l.chars[i]);
		}
		printf("\n");
	  	for (int i = 0; i < l.n_chars; i++ ) {
			if (l.chars[i] == ' ') {
				printf(" ");
				continue;
			}
			char d;
			while (true) {
				d = getchar();
				if ( d == ' ' ) {
				  d = getchar();
				  if ( d == ' ' ) {
				    d = getchar();
				    if ( d == ' ' ) {
				      d = getchar(); 
				      if ( d == ' ' ) {
				        d = getchar();
					if ( d == 'n' ) {
				          printf("Skipping\n");
					  return 0;
					}
				      }
				    }
				  }
			        }
				if (isgraph(d)) {

					break;
				}
			}
			if (d == l.chars[i]) {
				printf("\33[1A");
				printf( GREEN "%c" NORMAL, d);
				printf("\33[1B");
				printf("\33[1D");
				printf(" ");
			} else {
				printf("\33[1A");
				printf( RED "%c" NORMAL, l.chars[i]);
				printf("\33[1B");
				printf("\33[1D");
				
				printf("%c", d);
	
				n_mistakes++;
			}
		}
		if (n_mistakes > 0) {
			printf("\nThis line was incorrect! You need to get it right three times in a row now.\n");
			n_correct = 0;
			n_incorrect++;
		} else {
			n_correct++;
			if (n_incorrect == 0) {
				printf("\n This line perfect on the first try!");
				break;
			}
		}
		printf("\n\n");
	}
	printf("Completed this line.\n");
	printf("\n\n");
	return n_incorrect;
}

int do_exercise(exercise e) {
	int max_line_length = 72;
	int max_word_length = 4;
	int max_word_num = 5;


	int n_perfect_lines = 0;
	int n_imperfect_lines = 0;
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
			printf("\nYou made some mistakes with this line. You need to get it three lines correct in a row now.\n");
			n_imperfect_lines++;
			n_perfect_lines = 0;
		} else {
			n_perfect_lines++;
			if (n_imperfect_lines == 0) {
				printf("\nYou completed this exercise perfectly on the first try!\n");
				break;
			}
		}
	}
	return n_imperfect_lines;	

}

void train_exercise(exercise e) {
	if ( true ) {
		printf("Training the following rows\n\n");
		for ( int i = 0 ; i < e.n_rows; i++) {
			homerow h = e.rows[i];
			printf("Hand: %d Height: %d Position: %d "
				"Chars: %c %c %c %c\n\n",
				h.hand, h.height, h.position,
				h.chars.index,
				h.chars.middle,
				h.chars.ring,
				h.chars.pinky);
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
				printf("\nThis exercise was imperfect. You need to get three perfect lines in a row now.\n");
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
			printf("Now the same training with mixed words.\n");
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

