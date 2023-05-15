#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <ctype.h>

#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#include <errno.h>
#include <sys/stat.h>

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


void print_introduction() {
  char * skip_intro_file = "data/config/skip_intro";
  if (access(skip_intro_file, F_OK) == 0) {
	  return;
  }


  char * projectname = "ERGOTYPE";
  printf("\n\n\t\t %s\n\n", projectname);
  printf(" (always press enter to continue)\n\n");
  getchar();
  printf("Welcome to %s, which is an typing trainer. \n\n"
	" %s is born out of the idea that the keyboard is an instrument, \n"
	" in the sense of how musical intruments are intruments. \n" 
	" A keyboard is a tool which by the intended userbase is used \n"
	" to an extent that makes a time consuming exercise in mastering\n" 
	" ones own usage of it worthwhile. Just as cellists and violinist\n"
	" master their tool to feel comfortable in any position, \n"
	" playing any node with any (reasonable) finger, the aim of %s is to \n"
	" enable a similar mastery of our tool of choice: the keyboard.\n"
	" \n", "ERGOTYPE", "ERGOTYPE", "ERGOTYPE");
  getchar();
  printf(
	" Regardless of whether you are new to what commonly is kown as\n"
	" touch typing or already an expierienced practitioner, I believe \n"
	" this program might be of value to you.\n"
	" \n");
  getchar();
  printf(
	" For expierienced typist, we might start of slow. For absolute \n"
	" beginners, even the first exercises might seem too hard (I disagree). \n\n");
  getchar();
  printf(
	" To these absolute beginners it might be said that most expiriences \n"
	" typist will suffer almost similarly, likely relearning how to \n"
	" approach typing. At least after a couple of exercises. \n"
	" The expirienced programmer on the other hand shall be warned.\n"
	" The difficulty is rising sharply and furthermore, rougly\n"
	" based on your recent past performance. You may easily find\n"
	" yourself in a position where you are not able to even type a\n"
	" singel word correctly. I advise not to rush.\n"
	" \n "
	);
  getchar();
  printf(
	" Absolute beginners that are frustrated with these exercises \n"
	" are advised to turn to different typing exercise programs first.\n"
	" And return at wish. Other programs will much more likely \n"
	" enable fast progress at the beginning. \n"
	" \n");
  getchar();
  printf(
	" Experienced typists, on the other hand, which are frustrated\n"
	" with these exercises are advised to re-evaluate whether the \n"
	" mastery of the keyboard as aimed for by these exercises is \n"
	" indeed their goal. Exercises using dictionary words appear\n"
	" only after a long time. Many experienced typist frustrated\n"
	" with these exercises most likely are frustrated by their\n"
	" own performance.\n"
	" \n");
  getchar();
  printf(
	" As a final note, as this program is still in alpha, many \n"
	" many essential things are missing. I will comment on them \n"
	" and on the difficulties to realize them along the way. \n"
	" I highly appreciate some help. You will find extensive \n"
	" remarks in the source code of where help is needed. \n"
	" Also, I am open to new ideas. If no agreement can be \n"
	" made, I am also open to forks of this project. But in \n"
	" case you fork this project, please stay in touch as \n"
	" collobaration most likely will benefit everybody.\n",
	  "ERGOTYPE", "ERGOTYPE", "ERGOTYPE", "ERGOTYPE"
 );
 getchar();
 while (true) {
 	printf(" Do you want to skip the introduction in the future? (y/n)\n");
	char answer = getchar();
	if (answer != 'y' && answer != 'n') {
		printf("Please press either 'y' or 'n'.\n");
		continue;
	} else {
		if ( answer == 'y' ) {
			FILE * indicator_file = fopen(skip_intro_file,"w");
			if (indicator_file == NULL) {
				perror(NULL);
				exit(1);
			}

			fclose(indicator_file);
		}
		break;
	}
        	
 }
 printf("\n\n\n\n\n");  

}

char * data_dir = "data";
char * config_dir = "data/config";

void create_dir_if_non_existing(char * dir_name) {
  int result = mkdir(dir_name, 0777);
  if (result != 0) {
  	if (errno == EEXIST) {
		return;
	} else {
		perror(NULL);
		exit(1);
	}
  }

}


void init_data() {
	create_dir_if_non_existing(data_dir);
	create_dir_if_non_existing(config_dir);
}

static struct termios oldt, newt;

void init_terminal() {

  tcgetattr( STDIN_FILENO, &oldt);
  newt = oldt;

  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);

}

typedef struct {
	char * chars;
	int max_line_length;
	int max_word_num;
	int max_word_length;
	int n_chars;
} line;


typedef struct {
	homerow * rows;
	int n_rows;
	bool use_only_one_row;
} exercise;

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

homerow left_ex_01_rows[] = {
	{ left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
};

homerow left_ex_02_rows[] = {
    { left, upper, 0, {'y','u','i','o'},}, 
};

homerow left_ex_03_rows[] = {
    { left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
    { left, upper, 0, {'y','u','i','o'},}, 
};

homerow left_ex_04_rows[] = {
    { left, lower, 0, {'b','n','m',','},},
};

homerow left_ex_05a_rows[] = {
    { left, lower, 0, {'b','n','m',','},},
    { left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
};

homerow left_ex_05b_rows[] = {
    { left, lower, 0, {'b','n','m',','},},
    { left, upper, 0, {'y','u','i','o'},}, 
};

homerow left_ex_06_rows[] = {
    { left, upper, 0, {'y','u','i','o'},}, 
    { left, lower, 0, {'b','n','m',','},},
    { left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
};

homerow left_ex_07_rows[] = {
    { left, numbers, 0, {'6','7','8','9'},},
};

homerow left_ex_08_rows[] = {
    { left, upper, 0, {'y','u','i','o'},}, 
    { left, numbers, 0, {'6','7','8','9'},},
};

homerow left_ex_09_rows[] = {
    { left, upper, 0, {'y','u','i','o'},}, 
    { left, numbers, 0, {'6','7','8','9'},},
    { left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
};

homerow left_ex_10_rows[] = {
    { left, upper, 0, {'y','u','i','o'},}, 
    { left, numbers, 0, {'6','7','8','9'},},
    { left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
    { left, lower, 0, {'b','n','m',','},},
};


exercise left_ex[] = { 
	{
		left_ex_01_rows,
    		1,
    		true,
	},
	{
		left_ex_02_rows,
    		1,
    		true,
	},
	{
		left_ex_03_rows,
    		2,
    		true,
	},
	{
		left_ex_04_rows,
    		1,
    		true,
	},
	{
		left_ex_05a_rows,
    		2,
    		true,
	},
	{
		left_ex_05b_rows,
    		2,
    		true,
	},
	{
		left_ex_06_rows,
    		3,
    		true,
	},
	{
		left_ex_07_rows,
    		1,
    		true,
	},
	{
		left_ex_08_rows,
    		2,
    		true,
	},
	{
		left_ex_09_rows,
    		3,
    		true,
	},
	{
		left_ex_10_rows,
    		4,
    		true,
	},
};


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

int main() {
  // https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar-for-reading-a-single-character-only
  srand(time(NULL));

  init_terminal();
  init_data();

  print_introduction();

  for (int i = 0; i < sizeof(left_ex) / sizeof(left_ex[0]) ; i++) {
    printf("\n\nTraining exercise %d of %lu\n\n", i, sizeof(left_ex) / sizeof(left_ex[0]));	
    train_exercise(left_ex[i]);
  }

  printf("Congratulations! You achieved mastery.\n");
  
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
  return EXIT_SUCCESS;
}
