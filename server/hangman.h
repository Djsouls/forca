#ifndef _HANGMAN_H
#define _HANGMAN_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <string.h>

#include <time.h>

#include <unistd.h>

#include <sys/socket.h>

#include "../request/request.h"
#include "util.h"

typedef struct hangman {
    char word[MAX_WORD_SIZE];
    int doll_state; // From 0-5
} hangman;

void play_hangman(int);

char* choose_word();

int get_hits(char*, char, uint8_t*);
int index_of(char*, char, int);

bool word_completed(char*, int);
void update_word(char*, char, uint8_t*, int);
void init_word(char*, int);

#endif
