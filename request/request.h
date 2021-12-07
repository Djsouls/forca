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

char receive_char(int);

#endif
