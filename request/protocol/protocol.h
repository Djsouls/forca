#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include <stdint.h>

#define MSG_MAX_SIZE 128

#define MSG_TYPE_INDEX 0
#define MSG_PAYLOAD_SIZE_INDEX1 1
#define MSG_PAYLOAD_SIZE_INDEX2 2
#define START_PAYLOAD_INDEX 3

#define HELLO_MSG 0
#define SEND_WORD_SIZE 1
#define SEND_LETTER 2

typedef struct message {
    uint8_t msg_type;
    uint16_t payload_size;
    char* payload;
} message;

void make_hello_message(char*);

void make_message(char*, message);

void add_msg_type(char*, uint8_t);
void add_msg_payload_size(char*, uint16_t);
void add_msg_payload(char*, char*, uint16_t);

#endif
