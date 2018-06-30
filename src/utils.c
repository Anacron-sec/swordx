#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "utils.h"

static const char BASE_DIGIT = '0';
static const char BASE_CHAR = 'a';
static const int CHAR_OFFSET = 10;

void heap_check(void *obj) {
    if(obj == NULL) {
        perror("Out of memory");
        exit(EXIT_FAILURE);
    }
}

int map_char(char c) {
    return isdigit(c) ? (c - BASE_DIGIT) : (c - BASE_CHAR + CHAR_OFFSET);
}