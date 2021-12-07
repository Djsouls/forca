#include "util.h"

void error(char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int index_of(char* haystack, char needle, int start) {
    int size = strlen(haystack);

    for (int i = start; i < size; i++) {
        if (haystack[i] == needle) {
            return i;
        }
    }

    return -1;
}