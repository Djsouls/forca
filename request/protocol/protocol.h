#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include <stdint.h>

#define MSG_MAX_SIZE 128

#define MSG_TYPE_INDEX 0
#define MSG_PAYLOAD_SIZE_LOW 1
#define MSG_PAYLOAD_SIZE_HIGH 2
#define START_PAYLOAD_INDEX 3

#define HELLO_MSG 0
#define SEND_WORD_SIZE 1
#define SEND_LETTER 2
#define SEND_HITS 3

typedef struct message {
    uint8_t msg_type;
    uint16_t payload_size;
    char* payload;
} message;

void make_hello_message(char*);

void make_message(char*, message);

/* Review */
void make_send_word_size_message(char*, int);
void make_send_letter_message(char*, char);

void make_send_hits_message(char*, uint8_t*, int);
/**/

void add_msg_type(char*, uint8_t);
void add_msg_payload_size(char*, uint16_t);
void add_msg_payload(char*, char*, uint16_t);

int get_message_size(char*);
int get_headers_size(char*);
int get_payload_size(char*);


#endif
