#ifndef HOMEROWS_H
#define HOMEROWS_H
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


extern homerow rows[];

extern homerow left_ex_01_rows[];

extern homerow left_ex_02_rows[];

extern homerow left_ex_03_rows[];

extern homerow left_ex_04_rows[];

extern homerow left_ex_05a_rows[];

extern homerow left_ex_05b_rows[];

extern homerow left_ex_06_rows[];

extern homerow left_ex_07_rows[];

extern homerow left_ex_08_rows[];

extern homerow left_ex_09_rows[];

extern homerow left_ex_10_rows[];

#endif // HOMEROWS_H


