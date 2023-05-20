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

#endif // HOMEROWS_H


