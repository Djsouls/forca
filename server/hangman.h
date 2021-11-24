#ifndef _HANGMAN_H
#define _HANGMAN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/socket.h>

#include "../util.h"

void play_hangman(int);

char* choose_word();

#endif
