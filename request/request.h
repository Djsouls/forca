#ifndef _REQUEST_H
#define _REQUEST_H

#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

#include "protocol/protocol.h"


void send_hello(int);
void send_word_size(int, int);
void send_message(int, char*);

void send_letter(int, char);
void send_hit(int, int[], int);

void send_hits(int, uint8_t*, int);

char receive_char(int);
int receive_hits(int, int*);

#endif
