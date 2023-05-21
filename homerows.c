#include <stdio.h>
#include <stdlib.h>

#include "homerows.h"

homerow rows[] = {
    { left, upper, 0, {'y','u','i','o'},}, 
    { left, upper, 1, {'u','i','o','p'},}, 
    { left, upper, 2, {'i','o','p','['},}, 
    { left, upper, 3, {'o','p','[',']'},}, 
    { left, upper, 4, {'p','[',']','\\'},},
    
    { right, upper, 0, {'y','t','r','e'},}, 
    { right, upper, 1, {'t','r','e','w'},}, 
    { right, upper, 2, {'r','e','w','q'},}, 
    { right, upper, 3, {'e','w','q','\t'},}, 

    { left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
    { left, middle, 1, {'j', 'k' , 'l', ';'},}, 
    { left, middle, 2, {'k', 'l' , ';', '\''},},

    { right, middle, 0, {'h', 'g' , 'f', 'd'},}, 
    { right, middle, 1, {'g', 'f' , 'd', 's'},}, 
    { right, middle, 2, {'f', 'd' , 's', 'a'},},
    
    { left, numbers, 0, {'6','7','8','9'},},
    { left, numbers, 1, {'7','8','9','0'},},
    { left, numbers, 2, {'8','9','0','-'},},
    { left, numbers, 3, {'9','0','-','='},},

    { right, numbers, 0, {'6','5','4','3'},},
    { right, numbers, 1, {'5','4','3','2'},},
    { right, numbers, 2, {'4','3','2','1'},},
    { right, numbers, 3, {'3','2','1','`'},},

    { left, lower, 0, {'b','n','m',','},},
    { left, lower, 1, {'n','m',',','.'},},
    { left, lower, 2, {'m',',','.','/'},},

    { right, lower, 0, {'b','v','c','x'},},
    { right, lower, 1, {'v','c','x','z'},},
    { right, lower, 2, {'c','x','z','<'},},
};

homerow ordered_left_hand_rows[] = {
    { left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
    { left, upper, 0, {'y','u','i','o'},}, 
    { left, lower, 0, {'b','n','m',','},},
    { left, numbers, 0, {'6','7','8','9'},},

    { left, middle, 1, {'j', 'k' , 'l', ';'},}, 
    { left, upper, 1, {'u','i','o','p'},}, 
    { left, lower, 1, {'n','m',',','.'},},
    { left, numbers, 1, {'7','8','9','0'},},

    { left, middle, 2, {'k', 'l' , ';', '\''},},
    { left, upper, 2, {'i','o','p','['},}, 
    { left, lower, 2, {'m',',','.','/'},},
    { left, numbers, 2, {'8','9','0','-'},},

    { left, upper, 3, {'o','p','[',']'},}, 
    { left, numbers, 3, {'9','0','-','='},},

    { left, upper, 4, {'p','[',']','\\'},},
};

homerow ordered_right_hand_rows[] = {
    { right, middle, 0, {'h', 'g' , 'f', 'd'},}, 
    { right, upper, 0, {'y','t','r','e'},}, 
    { right, lower, 0, {'b','v','c','x'},},
    { right, numbers, 0, {'6','5','4','3'},},

    { right, middle, 1, {'g', 'f' , 'd', 's'},}, 
    { right, upper, 1, {'t','r','e','w'},}, 
    { right, lower, 1, {'v','c','x','z'},},
    { right, numbers, 1, {'5','4','3','2'},},

    { right, middle, 2, {'f', 'd' , 's', 'a'},},
    { right, upper, 2, {'r','e','w','q'},}, 
    { right, lower, 2, {'c','x','z','<'},},
    { right, numbers, 2, {'4','3','2','1'},},
    
    { right, upper, 3, {'e','w','q','\t'},}, 
    { right, numbers, 3, {'3','2','1','`'},},

};

charrow chartorow(char *chars) {
  charrow r;
  r.index = chars[0];
  r.middle = chars[1];
  r.ring = chars[2];
  r.pinky = chars[3];
  return r;
}

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
