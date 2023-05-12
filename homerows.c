#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define NORMAL "\x1b[0m"


typedef enum { left, right } side;
typedef enum { numbers, upper, middle, lower } altitude;
typedef unsigned int latitude; // with 0 being the outermost possible

typedef struct {
  char index;
  char middle;
  char ring;
  char pinky;
} charrow;

typedef struct {
  side hand;
  altitude height;
  latitude position;
  charrow chars;
} homerow;

charrow chartorow(char *chars) {
  charrow r;
  r.index = chars[0];
  r.middle = chars[1];
  r.ring = chars[2];
  r.pinky = chars[3];
  return r;
}

homerow rows[] = {
    { left, upper, 0, {'y','u','i','o'},}, 
    { left, upper, 1, {'u','i','o','p'},}, 
    { left, upper, 2, {'i','o','p','['},}, 
    { left, upper, 3, {'o','p','[',']'},}, 
    { left, upper, 4, {'p','[',']','\\'},},

    { left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
    { left, middle, 1, {'j', 'k' , 'l', ';'},}, 
    { left, middle, 2, {'k', 'l' , ';', '\''},},
    
    { left, numbers, 0, {'6','7','8','9'},},
    { left, numbers, 1, {'7','8','9','0'},},
    { left, numbers, 2, {'8','9','0','-'},},
    { left, numbers, 3, {'9','0','-','='},},

    { left, lower, 0, {'b','n','m',','},},
    { left, lower, 1, {'n','m',',','.'},},
    { left, lower, 2, {'m',',','.','/'},},
};

char get_random_char(homerow * h) {
	int r = rand() % 4;
	char f;
	switch (r) {
		case 0:
			f = h->chars.index;
			break;
		case 1:
			f = h->chars.middle;
			break;
		case 2:
			f = h->chars.ring;
			break;
		case 3:
			f = h->chars.pinky;
			break;
		default:
			fprintf(stderr,"%s line %d function %s: unexpected finger %d\n",
					__FILE__, __LINE__, __func__, r);
			exit(1);
		}

	return f;	
}

void create_random_word(char * word, int n_chars, homerow * r, int n_rows, bool use_only_one_row) {
	for (int i = 0; i < n_chars; i++) {
		int j = (i != 0 && use_only_one_row) ?
			j : rand() % n_rows;
		char c = get_random_char(&rows[j]);
		word[i] = c;
	}
}	

int main() {
  // https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar-for-reading-a-single-character-only
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);
  newt = oldt;

  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);

  srand(time(NULL));


  while (true) {

	int max_line_length = 72;
	int max_word_length = 4;
	int max_word_num = 5;

	char line[max_line_length];
	int n_chars = 0;
	for (int j = 0; j < max_word_num; j++) {
		if ( max_line_length - n_chars <= max_word_length) {
			break;
		}
		if ( j != 0) {
			line[n_chars++] = ' ';
		}
  		char word[max_word_length];
	 	create_random_word(word, max_word_length, rows, 15, true); 
  		for (int i = 0; i < max_word_length; i++ ) {
			line[n_chars++]=word[i];
		}
	}

	int n_correct = 0;
	while (n_correct < 3) {
		int n_mistakes = 0;
		for (int i = 0; i < n_chars; i++) {
			printf("%c", line[i]);
		}
		printf("\n");
	  	for (int i = 0; i < n_chars; i++ ) {
			if (line[i] == ' ') {
				printf(" ");
				continue;
			}
			char d = getchar();
			if (d == line[i]) {
				printf("\33[1A");
				printf( GREEN "%c" NORMAL, d);
				printf("\33[1B");
				printf("\33[1D");
				printf(" ");
			} else {
				printf("\33[1A");
				printf( RED "%c" NORMAL, line[i]);
				printf("\33[1B");
				printf("\33[1D");
				
				printf("%c", d);
	
				n_mistakes++;
			}
		}
		if (n_mistakes > 0) {
			n_correct = 0;
		} else {
			n_correct++;
		}
		printf("\n\n");

	}
}
  
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
  return EXIT_SUCCESS;
}
