#ifndef _CLIENT_H
#define _CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "../util.h"

#define HOST "127.0.0.1"

void config_addr(struct sockaddr_in*);

void play_hangman(int);

#endif
