#ifndef _CLIENT_H
#define _CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "request.h"
#include "../util.h"

#define HOST "127.0.0.1"

void play_hangman(int);

void init_word(char*, int);
void show_word(char*, int);
void update_word(char*, char, int*, int);

bool word_completed(char*, int);

void config_addr(struct sockaddr_in*);

#endif
