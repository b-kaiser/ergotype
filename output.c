#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <curses.h>
#include <stdbool.h>

#include "line.h"

#include "output.h"
#include <stdlib.h>


#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define NORMAL "\x1b[0m"

bool use_colors = false;
WINDOW * main_win;

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

  int starty = LINES / 4;
  int startx = COLS / 8;
  int height = LINES / 2;
  int width  = (COLS / 8 ) * 6;
  printw("Lines %d, Cols %d, height %d, width %d, starty %d, startx %d\n",
		  LINES, COLS, height, width, starty, startx);
  refresh();
  main_win = newwin(height, width, starty, startx);

}


void restore_terminal() {
  	delwin(main_win);
	endwin();
}

void reprint_line(line l) {
	if ( false ) {
		print_line(l);
	} else {
		int x, y;
		getbegyx(main_win,y,x);
		wmove(main_win,y+1,x);
		wclrtoeol(main_win);
		wrefresh(main_win);	
	}

}

void print_line(line l) {
	int x, y;
	getbegyx(main_win,y,x);
	wmove(main_win,y+1,x);
	wclrtoeol(main_win);
	wmove(main_win,y,x);
	for (int i = 0; i < l.n_chars; i++) {
		wprintw(main_win, "%c", l.chars[i]);
	}
	wmove(main_win,y+1,x);
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

void print_incorrect(char got, char expected) {
	int x, y;
	getyx(main_win,y,x);
	wattron(main_win,COLOR_PAIR(2));
	mvwprintw(main_win, y-1,x,"%c", expected);
	wattroff(main_win,COLOR_PAIR(2));
	
	mvwprintw(main_win, y,x,"%c", got);
	
	wrefresh(main_win);
}
