#ifndef _HANGMAN_H
#define _HANGMAN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/socket.h>

#include "../request/request.h"
#include "../util.h"

#define MAX_WORD_SIZE 32

typedef struct hangman {
    char word[MAX_WORD_SIZE];
    char current_word[MAX_WORD_SIZE];
    int doll_state; // From 0-5
} hangman;

void play_hangman(int);

char* choose_word();

#endif
