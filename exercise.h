#ifndef EXERCISE_H
#define EXERCISE_H

#include <stdbool.h>

#include "homerows.h"

typedef struct {
	homerow * rows;
	int n_rows;
	bool use_only_one_row;
} exercise;

exercise left_ex[] = { 
	{
		left_ex_01_rows,
    		1,
    		true,
	},
	{
		left_ex_02_rows,
    		1,
    		true,
	},
	{
		left_ex_03_rows,
    		2,
    		true,
	},
	{
		left_ex_04_rows,
    		1,
    		true,
	},
	{
		left_ex_05a_rows,
    		2,
    		true,
	},
	{
		left_ex_05b_rows,
    		2,
    		true,
	},
	{
		left_ex_06_rows,
    		3,
    		true,
	},
	{
		left_ex_07_rows,
    		1,
    		true,
	},
	{
		left_ex_08_rows,
    		2,
    		true,
	},
	{
		left_ex_09_rows,
    		3,
    		true,
	},
	{
		left_ex_10_rows,
    		4,
    		true,
	},
};

#endif // EXERCISE_H
