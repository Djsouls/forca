#ifndef _SERVER_H
#define _SERVER_H

typedef struct server_thread_context {
    int server_fd;
    struct sockaddr_in server_address;
} server_thread_context;

void* create_server(void*);

void create_server_threads(server_thread_context);

int create_socket();
void set_socket_opt(int);
void bind_server(int, struct sockaddr_in);
void listen_server(int);
void config_addr(struct sockaddr_in*);

#endif
