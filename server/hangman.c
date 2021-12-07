#include "hangman.h"

void play_hangman(int client_fd)
{
    char* word = choose_word();

    printf("Playing hangman!\n");
    send_word_size(client_fd, strlen(word));

    char letter = receive_char(client_fd);

    printf("Letra recebida: %i\n", letter);

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
