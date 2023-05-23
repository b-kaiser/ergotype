#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <curses.h>

#include "input.h"

char safe_getch() {
	while (true) {
		char d = getch();
		if (isgraph(d)) {
			return d;
		} else if ( d == ' ' ) {
			return d;
		} else if ( d == '\033' ) {
			getch();
			getch();
		}
	}
}

int obtain_key(char * c) {
	char d;
	while (true) {
		d = safe_getch();
		if ( d == ' ' ) {
		  d = safe_getch();
		  if ( d == ' ' ) {
		    d = safe_getch();
		    if ( d == ' ' ) {
		      d = safe_getch(); 
		      if ( d == ' ' ) {
		        d = safe_getch();
			if ( d == 'n' ) {
		          printw("Skipping\n");
			  return 1;
			}
		      }
		    }
		  }
	        }
		if (isgraph(d)) {
			break;
		}
	}
	*c = d;
	return 0;
}
