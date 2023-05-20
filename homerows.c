#include "homerows.h"

homerow rows[] = {
    { left, upper, 0, {'y','u','i','o'},}, 
    { left, upper, 1, {'u','i','o','p'},}, 
    { left, upper, 2, {'i','o','p','['},}, 
    { left, upper, 3, {'o','p','[',']'},}, 
    { left, upper, 4, {'p','[',']','\\'},},

    { left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
    { left, middle, 1, {'j', 'k' , 'l', ';'},}, 
    { left, middle, 2, {'k', 'l' , ';', '\''},},
    
    { left, numbers, 0, {'6','7','8','9'},},
    { left, numbers, 1, {'7','8','9','0'},},
    { left, numbers, 2, {'8','9','0','-'},},
    { left, numbers, 3, {'9','0','-','='},},

    { left, lower, 0, {'b','n','m',','},},
    { left, lower, 1, {'n','m',',','.'},},
    { left, lower, 2, {'m',',','.','/'},},
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
