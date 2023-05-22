#ifndef OUTPUT_H
#define OUTPUT_H

#include <termios.h>

#include "line.h"

void print_line(line l);
void reprint_line(line l);
void print_whitespace();

void print_correct(char d);
void print_incorrect(char got, char expected); 


void init_terminal();
void restore_terminal();

#endif // OUTPUT_H
