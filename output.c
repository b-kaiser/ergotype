#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <curses.h>
#include <stdbool.h>

#include "line.h"
#include "exercise.h"
#include "output.h"
#include <stdlib.h>


#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define NORMAL "\x1b[0m"

bool use_colors = false;
WINDOW * main_win;
WINDOW * penalty_win;
WINDOW * right_fingering_win;
WINDOW * left_fingering_win;


void print_intro() {
  int starty = LINES / 4;
  int startx = (COLS / 2) - (72 /2);
  int height = LINES / 4;
  int width  = 72;
 
  WINDOW * intro_win = newwin(height, width, starty, startx);
  curs_set(0);
  mvwprintw(intro_win, height / 2, width / 6,
"always press enter (or any other key) to continue");
  wrefresh(intro_win);
  getch();
  wclear(intro_win);
  wprintw(intro_win,
"\"Homerows\" are combinations of four consecutive keys on the same row\n"
"such as the traditional homerows\n"
"\n"
"         \"asdf\" (left hand)      and     \"jkl;\" (right hand)\n"
"\n"
"These can easily be typed with the four fingers of one hand.\n");
  wrefresh(intro_win);
  getch();
  wclear(intro_win);
  wprintw(intro_win,
"The levels in ergotype are based on homerows and involve a fingering\n"
"that shall be used to complete the level. In each level required\n"
"fingering is based on some combination of homerows that shall be\n"
"used together. The intent is to get familiar with the topology of\n"
"the keyboard and unfold the ability to press any key comfortably\n"
"with any finger in any situation.\n"
);
  wrefresh(intro_win);
  getch();
  wclear(intro_win);
  wprintw(intro_win,
"Optimal fingerings depend on the word and sentence that needs to be\n"
"written, as well as the keyboard you are using and and personal\n"
"preferences.\n"
"\n"
"The intent of the suggested fingering in the exercises is not to\n"
"learn an optimal fingering right away. In many cases, the fingering\n"
"required by the level is far from optimal. Instead, you are going\n"
"to learn the full spectrum of possible fingerings. In subsequent\n"
"levels you will not be provided a completely determined fingering and\n"
"naturally start to vary which finger you use for pressing a key.\n"
);
  wrefresh(intro_win);
  getch();
  wclear(intro_win);
  wprintw(intro_win,
"The approach used in ergotype differs from traditional methods to\n"
"teach touch typing by expanding the idea of homerows to any\n"
"combination of four subsequent keys in a row. Furthermore, ergotype\n"
"guides you to adjust the fingering dynamically, depending on other\n"
"keys that need to be pressed. Traditionally, only the above\n"
"mentioned two homerows \"jkl;\" and \"asdf\" are used, as well as\n"
"a fixed finger for any other key.\n"
);
  wrefresh(intro_win);
  getch();
  wclear(intro_win);
  wprintw(intro_win,
"We will start with training homerows in the middle of the keyboard,\n"
"where the set of keys pressed by the left hand overlaps with the set\n"
"of keys pressed by the right hand. We will start with homerows\n"
"containing numbers almost right away, but only slowly expand\n"
"outwards. Special characters are treated as any other key. We will\n"
"focus on one hand at a time. Levels involving both hands, uppercase\n"
"letters and dictionary words follow thereafter and focus on applying\n"
"previously acquired fingerings.\n"
);
  wrefresh(intro_win);
  getch();
  wclear(intro_win);
  wprintw(intro_win,
"A last remark before we start. We aim to treat both hands equally.\n"
"This leads to exercising pressing some keys with both hands, that in\n"
"more traditional touch typing system only get pressed by the right\n"
"hand. For some with prior touch typing experience this may seem\n"
"unusual. In particular, because we start with these keys right away\n"
);
wrefresh(intro_win);
getch();
wclear(intro_win);
curs_set(1);
wrefresh(intro_win);
delwin(intro_win);
}

void init_terminal() {
  initscr();
  cbreak();
  noecho();
  clear();

  use_colors = has_colors();
  if ( use_colors ) {
	  start_color();
  }
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);

  mvprintw(3, (COLS / 2)-4, "ERGOTYPE");
  refresh();

  int starty = LINES / 4;
  int startx = (COLS / 2) - 12;
  int height = LINES / 4;
  int width  = COLS / 4;
 
  main_win = newwin(height, width, starty, startx);
  print_intro();

  int penalty_width  = 4;
  int penalty_starty = starty;
  int penalty_startx = startx - penalty_width;
  int penalty_height = height;

  penalty_win = newwin(penalty_height,
	 	  penalty_width, penalty_starty, penalty_startx);


  int left_fingering_width  = width / 2;
  int left_fingering_starty = starty + height + 1;
  int left_fingering_startx = ((COLS / 8) *2) + 18;
  int left_fingering_height = height;

  left_fingering_win = newwin(left_fingering_height,
	 	  left_fingering_width, left_fingering_starty, left_fingering_startx);

  int right_fingering_width  = width / 2;
  int right_fingering_starty = starty + height + 1;
  int right_fingering_startx = (COLS / 8 ) * 5;
  int right_fingering_height = height;

  right_fingering_win = newwin(right_fingering_height,
	 	  right_fingering_width, right_fingering_starty, right_fingering_startx);
}

line * p_next;
line * p_middle;
line * p_last;

void print_register_following_lines(line * next, line * middle, line * last) {
	p_next = next;
	p_middle = middle;
	p_last = last;
}

void print_following_lines() {
	int y, x;
	getyx(main_win, y, x);

	wmove(main_win, 6, 0);
	wclrtoeol(main_win);
	wmove(main_win, 7, 0);
	wclrtoeol(main_win);
	wmove(main_win, 8, 0);
	wclrtoeol(main_win);
	mvwprintw(main_win, 6,0, "%s", p_next->chars);
	mvwprintw(main_win, 7,0, "%s", p_middle->chars);
	mvwprintw(main_win, 8,0, "%s", p_last->chars);
	wmove(main_win, y, x);
//	wrefresh(main_win);
}

void print_remove_following_line(line * next, line * middle, int remaining) {
	wmove(main_win, 6, 0);
	wclrtoeol(main_win);
	wmove(main_win, 7, 0);
	wclrtoeol(main_win);
	wmove(main_win, 8, 0);
	wclrtoeol(main_win);
	switch (remaining) {
		case 2:
			mvwprintw(main_win, 7, 0, "%s", middle->chars);
			__attribute__((fallthrough));
		case 1:
			mvwprintw(main_win, 6, 0, "%s", next->chars);
			__attribute__((fallthrough));
		case 0:
			break;
		default:
			restore_terminal();
			abort();
	}

	wrefresh(main_win);

}

void print_fingering_hand(exercise e, side hand) {

	char index_string[30];
	char middle_string[30];
	char ring_string[30];
	char pinky_string[30];
	int n = 0;
	for ( int i = 0 ; i < e.n_rows ; i++) {
		homerow h = e.rows[i];
		if ( h.hand  == hand ) {
			index_string[n] = (h.chars).index;	
			middle_string[n] = (h.chars).middle;	
			ring_string[n] = (h.chars).ring;	
			pinky_string[n] = (h.chars).pinky;	
			n++;
			index_string[n] = ' ';	
			middle_string[n] = ' ';	
			ring_string[n] = ' ';	
			pinky_string[n] = ' ';
			n++;
		}
	}
	index_string[n] = '\0';	
	middle_string[n] = '\0';	
	ring_string[n] = '\0';	
	pinky_string[n] = '\0';


	char * left_string = "Left Hand";
	char * right_string = "Right Hand";
	char * hand_string;
	WINDOW * win;
	switch (hand) {
		case left:
			win = left_fingering_win;
			hand_string = left_string;
			break;
		case right:
			win = right_fingering_win;
			hand_string = right_string;
			break;
	}

	wclear(win);
	if ( n > 0 ) {
		mvwprintw(win, 0, 0, "%s", hand_string);
		mvwprintw(win, 3, 0, "index  : %s", index_string);
		mvwprintw(win, 4, 0, "middle : %s", middle_string);
		mvwprintw(win, 5, 0, "ring   : %s", ring_string);
		mvwprintw(win, 6, 0, "pinky  : %s", pinky_string);
	}
	wrefresh(win);
}

void print_fingering(exercise e) {
	print_fingering_hand(e, left); 
	print_fingering_hand(e, right); 
}

void restore_terminal() {
  	delwin(main_win);
  	delwin(penalty_win);
	delwin(right_fingering_win);
	delwin(left_fingering_win);
	endwin();
}

void reprint_line(line l) {
	if ( false ) {
		print_line(l);
	} else {
		wmove(main_win,1,0);
		wclrtoeol(main_win);
		wrefresh(main_win);	
	}

}

void print_line(line l) {
	wmove(main_win,1,0);
	wclrtoeol(main_win);
	wmove(main_win,0,0);
	for (int i = 0; i < l.n_chars; i++) {
		wprintw(main_win, "%c", l.chars[i]);
	}
	wmove(main_win,1,0);
	wrefresh(main_win);

}

void print_whitespace() {
	wprintw(main_win, " ");
	wrefresh(main_win);
}

void print_correct(char d) {
	int x, y;
	getyx(main_win,y,x);
	wattron(main_win,COLOR_PAIR(1));
	mvwprintw(main_win,y-1,x,"%c", d);
	wattroff(main_win,COLOR_PAIR(1));
	mvwprintw(main_win, y,x," ");
	wrefresh(main_win);
}

void print_incorrect(char got, char expected, int penalty) {

	int x, y;
	getyx(main_win,y,x);
	wattron(main_win,COLOR_PAIR(2));
	mvwprintw(main_win, y-1,x,"%c", expected);
	wattroff(main_win,COLOR_PAIR(2));
	
	mvwprintw(main_win, y,x,"%c", got);
	
	wattron(penalty_win,COLOR_PAIR(2));
	mvwprintw(penalty_win, 0 ,0,"+%dx", penalty);
	wattroff(penalty_win,COLOR_PAIR(2));
	
	wrefresh(penalty_win);
	print_following_lines();
	wrefresh(main_win);
}

void print_increase_penalty(int penalty) {
	wattron(penalty_win,COLOR_PAIR(2));
	mvwprintw(penalty_win, 0 ,0,"+%dx", penalty);
	wattroff(penalty_win,COLOR_PAIR(2));
	
	wrefresh(penalty_win);

}

void print_lower_penalty(int penalty) {
 
	wattron(penalty_win,COLOR_PAIR(2));
	mvwprintw(penalty_win, 0 ,0," %dx", penalty);
	wattroff(penalty_win,COLOR_PAIR(2));
	
	wrefresh(penalty_win);

}

void print_remove_penalty() {
	wmove(penalty_win,0,0);
        wclrtoeol(penalty_win);	
	
	wrefresh(penalty_win);

}
