#pragma once

/* 
** This function is meant to be used after a call to malloc or calloc to test the result.
** If allocation failed exits with failure the program printing an error. 
**/
void check_heap(void *);

/*
**  Returns -1 if not mappable, 0-9 for digits and 10-35 for alpha 
**/
int map_char(char);