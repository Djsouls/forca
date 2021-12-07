#include "server.h"

#define MAX_THREADS 4

void main()
{
    struct sockaddr_in server_address;
    int addr_len = sizeof(server_address);

    pthread_t threads[MAX_THREADS];

    int server_fd = create_socket();

    set_socket_opt(server_fd);

    config_addr(&server_address);

    bind_server(server_fd, server_address);

    listen_server(server_fd);

    server_thread_context thread_context = {
        .server_fd = server_fd,
        .server_address = server_address    
    };

    printf("Inicializando as threads.\n");
    for(int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&threads[i], NULL, create_server, &thread_context);
    }

    printf("Esperando threads acabarem...\n");
    for(int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Threads finalizadas!\n");

}

void* create_server(void* thread_context) {
    server_thread_context* context = (server_thread_context *) thread_context;
    
    int client_fd;
    int addr_len = sizeof(context->server_address);

    while(true) {
        client_fd = accept(
            context->server_fd, 
            (struct sockaddr *) &context->server_address,
            (socklen_t *) &addr_len
        );

        if(client_fd < 0) {
            error("Deu ruim na conexão");
        }

        play_hangman(client_fd);
        printf("Exited client!\n");
    }
}

int create_socket()
{
    int server_fd;

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        error("Deu ruim em criar o server socket");
    }

    return server_fd;
}

void set_socket_opt(int socket_fd)
{
    int opt = 1;
    if(setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        error("Deu ruim no setsockopt");
    }
}

void bind_server(int server_fd, struct sockaddr_in server_address)
{
    if(bind(server_fd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
    {
        error("Deu ruim no bind");
    }
}

void listen_server(int server_fd)
{
    if(listen(server_fd, 3) < 0)
    {
        error("Deu ruim no listen");
    }
}

void config_addr(struct sockaddr_in* addr)
{
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(SERVER_PORT);
}

