#include "hangman.h"

void play_hangman(int client_fd)
{
    char* word = choose_word();
    char* word_size;

    sprintf(word_size, "%i", strlen(word));

    send(client_fd, word_size, strlen(word), 0);

    char* buffer;

    read(client_fd, buffer, BUFFER_SIZE);
    printf("Recebido do cliente %s\n", buffer);
}

char* choose_word() {
    #define n_words 4
        
    char* words[n_words] = {
        "microscopio",
        "banana",
        "odorico",
        "sabado"
    };

    return words[rand() % n_words];
}

