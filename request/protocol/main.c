#include <stdio.h>

#include "protocol.h"

int main() {
    char payload[62000] = "oiee";

    message msg = {
        .msg_type = 3,
        .payload_size = 62000,
        .payload = payload
    };

    char m[10];
    make_message(m, msg);

    char mm[10];
    make_hello_message(mm);

    for(int i = 0; i < 7; i++) {
        printf("%c\n", m[i]);
        printf("%i\n", (uint8_t) m[i]);
    }
    printf("\nhmm\n");
    for(int i = 0; i < 3; i++) {
        //printf("%c\n", m[i]);
        printf("%i\n", (uint8_t) mm[i]);
    }
}
