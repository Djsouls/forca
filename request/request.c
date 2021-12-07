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

void send_message(int sock, char* msg) {
    send(sock, msg, MSG_MAX_SIZE, 0);
}

char receive_char(int sock) {
    char msg[MSG_MAX_SIZE];

    read(sock, msg, MSG_MAX_SIZE);

    for(int i = 0; i < 5; i++) {
        printf("%i: %i\n", i, msg[i]);
    }

    return msg[3];
}
