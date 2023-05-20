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

homerow left_ex_01_rows[] = {
	{ left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
};

homerow left_ex_02_rows[] = {
    { left, upper, 0, {'y','u','i','o'},}, 
};

homerow left_ex_03_rows[] = {
    { left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
    { left, upper, 0, {'y','u','i','o'},}, 
};

homerow left_ex_04_rows[] = {
    { left, lower, 0, {'b','n','m',','},},
};

homerow left_ex_05a_rows[] = {
    { left, lower, 0, {'b','n','m',','},},
    { left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
};

homerow left_ex_05b_rows[] = {
    { left, lower, 0, {'b','n','m',','},},
    { left, upper, 0, {'y','u','i','o'},}, 
};

homerow left_ex_06_rows[] = {
    { left, upper, 0, {'y','u','i','o'},}, 
    { left, lower, 0, {'b','n','m',','},},
    { left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
};

homerow left_ex_07_rows[] = {
    { left, numbers, 0, {'6','7','8','9'},},
};

homerow left_ex_08_rows[] = {
    { left, upper, 0, {'y','u','i','o'},}, 
    { left, numbers, 0, {'6','7','8','9'},},
};

homerow left_ex_09_rows[] = {
    { left, upper, 0, {'y','u','i','o'},}, 
    { left, numbers, 0, {'6','7','8','9'},},
    { left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
};

homerow left_ex_10_rows[] = {
    { left, upper, 0, {'y','u','i','o'},}, 
    { left, numbers, 0, {'6','7','8','9'},},
    { left, middle, 0, {'h', 'j' , 'k', 'l'},}, 
    { left, lower, 0, {'b','n','m',','},},
};


