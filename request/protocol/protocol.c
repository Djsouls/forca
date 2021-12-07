#include "protocol.h"

void make_hello_message(char* msg_buffer) {
    message msg = {
        .msg_type = HELLO_MSG,
        .payload_size = 0,
        .payload = 0
    };

    make_message(msg_buffer, msg);
}

void make_send_word_size_message(char* msg_buffer, int word_size) {
    uint8_t size = word_size;

    /* This is ugly af */
    char payload[1];
    payload[0] = size;

    message msg = {
        .msg_type = SEND_WORD_SIZE,
        .payload_size = sizeof(size),
        .payload = payload
    };

    make_message(msg_buffer, msg);
}

void make_send_letter_message(char* msg_buffer, char letter) {
    char payload[1];
    payload[0] = letter;

    message msg = {
        .msg_type = SEND_LETTER,
        .payload_size = sizeof(letter),
        .payload = payload
    };

    make_message(msg_buffer, msg);
}

void make_message(char* msg_buffer, message msg) {
    add_msg_type(msg_buffer, msg.msg_type);
    add_msg_payload_size(msg_buffer, msg.payload_size);
    add_msg_payload(msg_buffer, msg.payload, msg.payload_size);
}

void add_msg_type(char* msg, uint8_t msg_type) {
    msg[MSG_TYPE_INDEX] = msg_type;
}

void add_msg_payload_size(char* msg, uint16_t payload_size) {
    char lo = payload_size & 0xFF; // Gets the lower 8 bits of the payload size
    char hi = payload_size >> 8;   // Gets the upper 8 buts of the payload size

   msg[MSG_PAYLOAD_SIZE_INDEX1] = lo;
   msg[MSG_PAYLOAD_SIZE_INDEX2] = hi;
}

void add_msg_payload(char* msg, char* payload, uint16_t payload_size) {
    for(uint16_t i = START_PAYLOAD_INDEX; i < (START_PAYLOAD_INDEX + payload_size); i++) {
        msg[i] = payload[i - START_PAYLOAD_INDEX];
    }
}
