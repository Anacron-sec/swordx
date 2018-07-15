#pragma once

typedef enum {ERROR_TYPE = -1, OTHER , REGULAR_FILE, DIRECTORY, SYMBOLIC_LINK} fileType;

/* 
** This function is meant to be used after a call to malloc or calloc to test the result.
** If allocation failed exits with failure the program printing an error. 
**/
void check_heap(void *);

/*
** This function return an enum fileType depending on the type of file passed as argument
*/
fileType type_of_file(char *);








































































































































































































































































void pirate(void);