#pragma once

/* 
** This function is meant to be used after a call to malloc or calloc to test the result.
** If allocation failed exits with failure the program printing an error. 
**/
void check_heap(void *);