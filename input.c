#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <curses.h>

#include "input.h"

int obtain_key(char * c) {
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
