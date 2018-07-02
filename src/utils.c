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
    /* 0-9 for digits and 10-35 for alphabet 36 for nul*/
    char lowercase_c = tolower(c);
    if(lowercase_c == '\0') return 36;
    return isdigit(lowercase_c) ? (lowercase_c - BASE_DIGIT) : (lowercase_c - BASE_CHAR + CHAR_OFFSET);
}