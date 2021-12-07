#include "hangman.h"

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

        send_hits(client_fd, hits, hit_count);

        if(hit_count == 0) {
            lives--;
            printf("Lives %i\n", lives);
        }

        update_word(current_word, letter, hits, hit_count);
    }
}

/**
 * Choose a random word from our very big massive dataset of words.
*/
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

/**
 * Populates the array "hits" with the indexes of the hits
 * of the letter in the word. Return the number of hits in the word.
 *
 * For example:
 *     word = banana,
 *     letter = a
 * Will populate hits with
 *     hits = [1, 3, 5]
 *
*/
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

/**
 * Initiante the word with "_" for checking.
 * Given a word with size 7, the "word" array will be:
 *
 * word = "_______"
*/
void init_word(char* word, int word_size) {
    for(int i = 0; i < word_size; i++) {
        word[i] = '_';
    }
}

/**
 * Update the word state with the hit letter
 *
 * For example:
 *     letter = a
 *     hits = [1, 3, 5]
 *     hit_count = 3
 *     word = "______"
 *
 * The word state will be:
 *     word = "_a_a_a_"
*/
void update_word(char* word, char letter, uint8_t* hits, int hit_count) {
    for(int i = 0; i < hit_count; i++) {
        word[hits[i]] = letter;
    }
}

/**
 * Checks if a word is completed. A word is completede when there's
 * no '_' left in it.
*/
bool word_completed(char* word, int word_size) {
    for(int i = 0; i < word_size; i++) {
        if(word[i] == '_') {
            return false;
        }
    }

    return true;
}
