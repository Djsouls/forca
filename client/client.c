#include "client.h"

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
    int lives = N_LIVES;
    char word[MAX_WORD_SIZE];

    int word_size = get_word_size(server_fd);

    printf("Tamanho da palavra: %i\n", word_size);

    init_word(word, word_size);
    show_word(word, word_size);

    int hits[MAX_WORD_SIZE];
    char letter;
    while(lives > 0) {
        printf("\nLetra ");
        scanf(" %c", &letter);

        send_letter(server_fd, letter);

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
 * Prints the actual word state.
*/

void show_word(char* word, int word_size) {
    printf("Word: ");
    for(int i = 0; i < word_size; i++) {
        printf("%c ", word[i]);
    }
    printf("\n");
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

void update_word(char* word, char letter, int* hits, int hit_count) {
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

void config_addr(struct sockaddr_in* addr)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(SERVER_PORT);
}

