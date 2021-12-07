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

/* Payload will be comma separated hits index
 * ex: 1,5...
 * ex without hits: #
*/

void make_send_hits_message(char* msg_buffer, uint8_t hits[], int hit_count) {
    char payload[MSG_MAX_SIZE];
    int payload_size = 0;

    /* Populates the payload in the format described above */
    int payload_index = 0;
    for(int i = 0; i < hit_count; i++) {
        payload[payload_index++] = hits[i];

        /* Last iteration */
        if(i == hit_count - 1) {
            break;
        }

        payload[payload_index++] = ',';
    }

    payload_size = 2 * hit_count - 1;
    if(hit_count == 0) {
        payload_size = 0;
    }

    // for(int i = 0; i < payload_index; i++) {
    //     printf("payload: %i\n", payload[i]);
    // }

    message msg = {
        .msg_type = SEND_HITS,
        .payload_size = payload_size,
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

   msg[MSG_PAYLOAD_SIZE_LOW] = lo;
   msg[MSG_PAYLOAD_SIZE_HIGH] = hi;
}

void add_msg_payload(char* msg, char* payload, uint16_t payload_size) {
    for(uint16_t i = START_PAYLOAD_INDEX; i < (START_PAYLOAD_INDEX + payload_size); i++) {
        msg[i] = payload[i - START_PAYLOAD_INDEX];
    }
}

int get_message_size(char* msg) {
    int headers_size = get_headers_size(msg);
    int payload_size = get_payload_size(msg);

    return headers_size + payload_size;
}

int get_headers_size(char* msg) {
    // 1 for message type and 2 for payload size
    return 3;
}

int get_payload_size(char* msg) {

    int size = (
        msg[MSG_PAYLOAD_SIZE_HIGH] << 8 |
        msg[MSG_PAYLOAD_SIZE_LOW]
    );

    return size;
}
