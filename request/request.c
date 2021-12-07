#include "request.h"

void send_hello(int client_fd) {
    char hello[MSG_MAX_SIZE];

    make_hello_message(hello);

    send_message(client_fd, hello);
}

void send_word_size(int client_fd, int word_size) {
    char msg[MSG_MAX_SIZE];

    make_send_word_size_message(msg, word_size);

    send_message(client_fd, msg);
}

void send_letter(int server_fd, char letter) {
    char msg[MSG_MAX_SIZE] = {0};
    
    make_send_letter_message(msg, letter);

    send_message(server_fd, msg);
}

void send_hits(int client_fd, uint8_t hits[], int hit_count) {
    char msg[MSG_MAX_SIZE] = {0};

    make_send_hits_message(msg, hits, hit_count);

    send_message(client_fd, msg);
}

void send_message(int sock, char* msg) {
    int msg_size = get_message_size(msg);
    send(sock, msg, msg_size, 0);
}

char receive_char(int sock) {
    char msg[MSG_MAX_SIZE];

    read(sock, msg, MSG_MAX_SIZE);

    for(int i = 0; i < 5; i++) {
        // printf("%i: %i\n", i, msg[i]);
    }

    return msg[START_PAYLOAD_INDEX];
}

int receive_hits(int sock, int* hits) {
    char msg[MSG_MAX_SIZE];

    read(sock, msg, MSG_MAX_SIZE);

    int size = (
        msg[MSG_PAYLOAD_SIZE_HIGH] << 8 |
        msg[MSG_PAYLOAD_SIZE_LOW]
    );

    int hits_index = 0;
    int hit_count = 0;

    for(int i = START_PAYLOAD_INDEX; i < START_PAYLOAD_INDEX + size; i = i+2) {
        // printf("%i: %i\n", i, msg[i]);
        hits[hits_index++] = msg[i];
        hit_count++;
    }


    return hit_count;
}
