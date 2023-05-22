#ifndef OUTPUT_H
#define OUTPUT_H

#include <termios.h>

#include "line.h"
#include "exercise.h"

void print_line(line l);
void reprint_line(line l);
void print_whitespace();

void print_correct(char d);
void print_incorrect(char got, char expected, int penalty); 

void print_lower_penalty(int n_correct);
void print_remove_penalty();
void init_terminal();
void restore_terminal();

void print_remove_following_line(line * middle, line * last, int remaining);
void print_register_following_lines(line * next, line * middle, line * last);
void print_following_lines();
void print_fingering(exercise e);
#endif // OUTPUT_H
