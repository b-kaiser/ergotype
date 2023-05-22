#include <stdio.h>
#include <stdlib.h>

#include "homerows.h"

homerow rows[] = {
    { right, upper, 0, {'y','u','i','o'},}, 
    { right, upper, 1, {'u','i','o','p'},}, 
    { right, upper, 2, {'i','o','p','['},}, 
    { right, upper, 3, {'o','p','[',']'},}, 
    { right, upper, 4, {'p','[',']','\\'},},
    
    { left, upper, 0, {'y','t','r','e'},}, 
    { left, upper, 1, {'t','r','e','w'},}, 
    { left, upper, 2, {'r','e','w','q'},}, 
    { left, upper, 3, {'e','w','q','\t'},}, 

    { right, middle, 0, {'h', 'j' , 'k', 'l'},}, 
    { right, middle, 1, {'j', 'k' , 'l', ';'},}, 
    { right, middle, 2, {'k', 'l' , ';', '\''},},

    { left, middle, 0, {'h', 'g' , 'f', 'd'},}, 
    { left, middle, 1, {'g', 'f' , 'd', 's'},}, 
    { left, middle, 2, {'f', 'd' , 's', 'a'},},
    
    { right, numbers, 0, {'6','7','8','9'},},
    { right, numbers, 1, {'7','8','9','0'},},
    { right, numbers, 2, {'8','9','0','-'},},
    { right, numbers, 3, {'9','0','-','='},},

    { left, numbers, 0, {'6','5','4','3'},},
    { left, numbers, 1, {'5','4','3','2'},},
    { left, numbers, 2, {'4','3','2','1'},},
    { left, numbers, 3, {'3','2','1','`'},},

    { right, lower, 0, {'b','n','m',','},},
    { right, lower, 1, {'n','m',',','.'},},
    { right, lower, 2, {'m',',','.','/'},},

    { left, lower, 0, {'b','v','c','x'},},
    { left, lower, 1, {'v','c','x','z'},},
    { left, lower, 2, {'c','x','z','<'},},
};

homerow ordered_right_hand_rows[] = {
    { right, middle, 0, {'h', 'j' , 'k', 'l'},}, 
    { right, upper, 0, {'y','u','i','o'},}, 
    { right, lower, 0, {'b','n','m',','},},
    { right, numbers, 0, {'6','7','8','9'},},

    { right, middle, 1, {'j', 'k' , 'l', ';'},}, 
    { right, upper, 1, {'u','i','o','p'},}, 
    { right, lower, 1, {'n','m',',','.'},},
    { right, numbers, 1, {'7','8','9','0'},},

    { right, middle, 2, {'k', 'l' , ';', '\''},},
    { right, upper, 2, {'i','o','p','['},}, 
    { right, lower, 2, {'m',',','.','/'},},
    { right, numbers, 2, {'8','9','0','-'},},

    { right, upper, 3, {'o','p','[',']'},}, 
    { right, numbers, 3, {'9','0','-','='},},

    { right, upper, 4, {'p','[',']','\\'},},
};

homerow ordered_left_hand_rows[] = {
    { left, middle, 0, {'h', 'g' , 'f', 'd'},}, 
    { left, upper, 0, {'y','t','r','e'},}, 
    { left, lower, 0, {'b','v','c','x'},},
    { left, numbers, 0, {'6','5','4','3'},},

    { left, middle, 1, {'g', 'f' , 'd', 's'},}, 
    { left, upper, 1, {'t','r','e','w'},}, 
    { left, lower, 1, {'v','c','x','z'},},
    { left, numbers, 1, {'5','4','3','2'},},

    { left, middle, 2, {'f', 'd' , 's', 'a'},},
    { left, upper, 2, {'r','e','w','q'},}, 
    { left, lower, 2, {'c','x','z','<'},},
    { left, numbers, 2, {'4','3','2','1'},},
    
    { left, upper, 3, {'e','w','q','\t'},}, 
    { left, numbers, 3, {'3','2','1','`'},},

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
