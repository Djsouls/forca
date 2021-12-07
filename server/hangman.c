#include "hangman.h"

void play_hangman(int client_fd)
{
    char* word = choose_word();

    printf("Playing hangman!\n");
    printf("%s\n", word);
    
    send_word_size(client_fd, strlen(word));

    char letter = receive_char(client_fd);
    printf("Letra recebida: %i\n", letter);
    
    int hit_count = 0;
    int hit_index = index_of(word, letter, 0);
    // Conta a quantidade de acertos
    while (hit_index != -1) {
        hit_count++;
        hit_index = index_of(word, letter, hit_index + 1);
    }


    hit_index = 0;
    int hits[hit_count];
    for (int i = 0; i < hit_count; i++) {
        hits[i] = index_of(word, letter, hit_index);
        hit_index = index_of(word, letter, hit_index + 1);
    }

    send_hit(client_fd, hits, 3);
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

int index_of(char* haystack, char needle, int start) {
    int size = strlen(haystack);

    for (int i = start; i < size; i++) {
        if (haystack[i] == needle) {
            return i;
        }
    }

    return -1;
}