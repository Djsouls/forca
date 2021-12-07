#ifndef _REQUEST_H
#define _REQUEST_H

#include <stdio.h>

#include <unistd.h>

#include <sys/socket.h>

#include "protocol/protocol.h"
#include "../util.h"

void send_hello(int);
void send_word_size(int, int);
void send_message(int, char*);
void send_letter(int, char);
void send_hits(int, uint8_t*, int);

int get_word_size(int);

char receive_char(int);
int receive_hits(int, int*);

#endif
