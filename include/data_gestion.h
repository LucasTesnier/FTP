/*
** EPITECH PROJECT, 2022
** Project
** File description:
** data_gestion
*/

#ifndef DATA_GESTION_H_
    #define DATA_GESTION_H_

    #include <stdbool.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    #define closesocket(s) close(s)

typedef int SOCKET;

typedef struct sockaddr_in sockaddr_in_t;
typedef struct sockaddr sockaddr_t;

typedef enum authentification_s {
    OFFLINE,
    USER,
    CONNECTED
} authentification_t;

typedef struct connexion_s {
    SOCKET my_socket;
    sockaddr_in_t interface;
    bool is_active;
    authentification_t is_auth;
} connexion_t;

typedef struct data_s {
    connexion_t **data;
    size_t size;
    int port;
    char *home_path;
} data_t;

data_t *init_data(void);
void destroy_data(data_t *head);
connexion_t *server_init(data_t *head);
void destroy_server(connexion_t *server);
int add_in_head(data_t *head, connexion_t *client);

#endif /* !DATA_GESTION_H_ */
