#include "util.h"

void error(char* msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

