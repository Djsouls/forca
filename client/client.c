#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "client.h"
#include "../util.h"

#define HOST "127.0.0.1"

void config_addr(struct sockaddr_in*);

void play_hangman(int);

void main()
{
    int sock;
    struct sockaddr_in server_addr;

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        error("Deu ruim criando o socket");
    }

    config_addr(&server_addr);

    if(inet_pton(AF_INET, HOST, &server_addr.sin_addr) <= 0)
    {
        error("Deu ruim convertendo endereço");
    }

    if(connect(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0)
    {
        error("Deu ruim conectando");
    }

    play_hangman(sock);
}

void play_hangman(int server_fd) {
    char server_buffer[BUFFER_SIZE] = {0};

    read(server_fd, server_buffer, BUFFER_SIZE);

    printf("Tamanho da palavra: %i\n", server_buffer[START_PAYLOAD_INDEX]);

    char letter;

    scanf("%c", &letter);

    send_letter(server_fd, letter);

    int hits[10];
    int hit_count = receive_hits(server_fd, hits);

    for(int i = 0; i < hit_count; i++) {
        printf("%d\n", hits[i]);
    }
}

void config_addr(struct sockaddr_in* addr)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(SERVER_PORT);
}

