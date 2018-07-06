#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

void check_heap(void *obj) {
    if(obj == NULL) {
        perror("Out of memory");
        exit(EXIT_FAILURE);
    }
}