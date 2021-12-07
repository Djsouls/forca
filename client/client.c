#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "client.h"
#include "../util.h"

#define HOST "127.0.0.1"

void config_addr(struct sockaddr_in*);

void play_hangman(int);

void init_word(char*, int);
void show_word(char*, int);
void update_word(char*, char, int*, int);

bool word_completed(char*, int);

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

    close(sock);
}

void play_hangman(int server_fd) {
    int lives = 5;
    char word[32];

    char server_buffer[BUFFER_SIZE] = {0};

    read(server_fd, server_buffer, BUFFER_SIZE);

    int word_size = server_buffer[START_PAYLOAD_INDEX];
    printf("Tamanho da palavra: %i\n", word_size);

    init_word(word, word_size);
    show_word(word, word_size);

    char letter;
    while(lives > 0) {
        printf("Letra ");
        scanf(" %c", &letter);

        send_letter(server_fd, letter);

        int hits[32];
        int hit_count = receive_hits(server_fd, hits);

        if (hit_count == 0) {
            lives--;
            printf("Lives: %i\n", lives);

            if(lives == 0) {
                printf("You loose!\n");
                break;
            }
        }
        
        update_word(word, letter, hits, hit_count);
        show_word(word, word_size);

        if(word_completed(word, word_size)) {
            printf("You win!!\n");
            break;
        }
    }
}

void init_word(char* word, int word_size) {
    for(int i = 0; i < word_size; i++) {
        word[i] = '_';
    }
}

void show_word(char* word, int word_size) {
    printf("Word: ");
    for(int i = 0; i < word_size; i++) {
        printf("%c ", word[i]);
    }
    printf("\n");
}

void update_word(char* word, char letter, int* hits, int hit_count) {
    for(int i = 0; i < hit_count; i++) {
        word[hits[i]] = letter;
    }
}

bool word_completed(char* word, int word_size) {
    for(int i = 0; i < word_size; i++) {
        if(word[i] == '_') {
            return false;
        }
    }

    return true;
}

void config_addr(struct sockaddr_in* addr)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(SERVER_PORT);
}

