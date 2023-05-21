#ifndef HOMEROWS_H
#define HOMEROWS_H
typedef enum { left, right } side;
typedef enum { numbers, upper, middle, lower } altitude;
typedef unsigned int latitude;

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

extern homerow ordered_left_hand_rows[];
extern homerow ordered_right_hand_rows[];
#endif // HOMEROWS_H


