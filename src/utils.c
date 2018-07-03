#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "utils.h"

static const char BASE_DIGIT = '0';
static const char BASE_CHAR = 'a';
static const int CHAR_OFFSET = 10;

/* this function is meant to be used after a call to malloc or calloc to test the result */
void check_heap(void *obj) {
    if(obj == NULL) {
        perror("Out of memory");
        exit(EXIT_FAILURE);
    }
}

int map_char(char c) {
    if(isdigit(c)) 
        return (c - BASE_DIGIT);

    char lowercase = tolower(c);

    return islower(lowercase) ? (lowercase - BASE_CHAR + CHAR_OFFSET) : -1;
}