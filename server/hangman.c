#include "hangman.h"

#include <stdbool.h>

int get_hits(char*, char, uint8_t*);
int index_of(char*, char, int);

bool word_completed(char*, int);
void update_word(char*, char, uint8_t*, int);
void init_word(char*, int);

void play_hangman(int client_fd)
{
    char* word = choose_word();
    int word_size = strlen(word);

    char current_word[word_size];
    init_word(current_word, word_size);

    int lives = 5;

    printf("Playing hangman!\n");
    printf("Word: %s\n", word);

    send_word_size(client_fd, word_size);

    while(lives > 0) {
        if(word_completed(current_word, word_size)) {
            printf("word completed!\n");
            break;
        }

        char letter = receive_char(client_fd);

        printf("Letra recebida: %i\n", letter);

        uint8_t hits[MAX_WORD_SIZE];
        int hit_count = get_hits(word, letter, hits);

        update_word(current_word, letter, hits, hit_count);

        send_hits(client_fd, hits, hit_count);

        if(hit_count == 0) {
            lives--;
            printf("Lives %i\n", lives);
        }
    }
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

int get_hits(char* word, char letter, uint8_t* hits) {

    int i = 0;
    int hit_index = index_of(word, letter, 0);
    int hit_count = 0;

    while(hit_index != -1) {
        hits[i++] = hit_index;
        hit_index = index_of(word, letter, hit_index + 1);
        hit_count++;
    }

    return hit_count;
}

void init_word(char* word, int word_size) {
    for(int i = 0; i < word_size; i++) {
        word[i] = '_';
    }
}

void update_word(char* word, char letter, uint8_t* hits, int hit_count) {
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
