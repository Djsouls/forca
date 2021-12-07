#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PORT 8080

#define BUFFER_SIZE 1024

#define MAX_WORD_SIZE 32
#define N_LIVES 5

void error(char*);
int index_of(char*, char, int);

#endif
