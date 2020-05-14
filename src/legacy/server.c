#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "lib/msg.h"
#include "lib/map.h"
#include "lib/ship.h"
#include "lib/socket.h"
#include "lib/util.h"
#include "lib/config.h"

int main(int argc, char *argv[])
{
    // Map settings
    Map *m = init_map_matrix(MAP_WIDTH, MAP_HEIGH);
    Map *client_map = init_map_matrix(MAP_WIDTH, MAP_HEIGH);
    int i, ship, x, y, orientation; // ship insertion
    char my_nickname[30], opponent_nickname[30];

    // Socket settings
    char port[5];
    int server_socket, client_socket;
    struct addrinfo hints, *server_info;
    struct sockaddr_storage client_addr;
    socklen_t sin_size;
    char client_ip[INET6_ADDRSTRLEN];
    int status;

    // Messages settings
    int end_game;
    status_message *s_msg;
    introducion_message *i_msg;
    attack_message *a_msg;

    // ------------------------------------------------------------------------

    if (argc != 2) {
        fprintf(stderr,"usage: server port\n");
        exit(1);
    }

    // ------------------------------------------------------------------------

    // Welcome message
    welcome();

    printf("Please, insert your nickname: ");
    fgets(my_nickname, 30, stdin);
    if (my_nickname[strlen(my_nickname) - 1] == '\n')
        my_nickname[strlen(my_nickname) - 1] = '\0';

    system("clear");

    // ------------------------------------------------------------------------
    // Prepare socket

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((status = getaddrinfo(NULL, argv[1], &hints, &server_info)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    if ((server_socket = socket(server_info->ai_family,
         server_info->ai_socktype, server_info->ai_protocol)) == -1) {
        perror("server: socket");
    }

    if (bind(server_socket, server_info->ai_addr,
             server_info->ai_addrlen) == -1) {
        close(server_socket);
        perror("server: bind");
    }

    if (server_info == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    freeaddrinfo(server_info);

    if (listen(server_socket, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    printf("\nWaiting for opponents...\n");

    sin_size = sizeof client_addr;
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr,
                           &sin_size);
    if (client_socket == -1) {
        perror("accept");
    }

    inet_ntop(client_addr.ss_family,
        get_in_addr((struct sockaddr *)&client_addr),
        client_ip, sizeof client_ip);

    // ------------------------------------------------------------------------
    // Send and receive introduction message

    i_msg = malloc(sizeof(introducion_message));
    i_msg->type = 1;
    strcpy(i_msg->nickname, my_nickname);

    if (send(client_socket, i_msg, sizeof(introducion_message), 0) == -1)
    {
        perror("send");
        exit(1);
    }

    if ((status = recv(client_socket, i_msg,
                       sizeof(introducion_message), 0)) == -1) {
        perror("recv");
        exit(1);
    }
    strcpy(opponent_nickname, i_msg->nickname);
    free(i_msg);

    system("clear");
    printf("Opponent ready! ");
    PRINT_YELLOW(opponent_nickname);
    printf(" (%s)\n\n", client_ip);

    // ------------------------------------------------------------------------
    // Put the ships in the map

    while((i = check_used_ships(m)) > 0)
    {
        // Show the map and the ships
        show_map(m);
        show_ships(m);

        printf("You still have %i ship(s) to organize\n", i);
        printf("Choose one to put in the map: ");
        scanf("%i", &ship);
        while(ship > 3 || ship < 0 || m->ships[ship] == 0)
        {
            printf("Invalid choice\n");
            printf("Please, choose another one: ");
            scanf("%i", &ship);
        }

        printf("Orientation (1-vert/2-hori): ");
        scanf("%i", &orientation);
        while(orientation != 1 && orientation != 2)
        {
            printf("Invalid choice\n");
            printf("Please, choose another option: ");
            scanf("%i", &orientation);
        }

        printf("Ship head position\n");
        printf("x: ");
        scanf("%i", &x);
        while(x > m->width || x < 0)
        {
            printf("Invalid choice\n");
            printf("Please, choose another x: ");
            scanf("%i", &x);
        }

        printf("y: ");
        scanf("%i", &y);
        while(y > m->height || y < 0)
        {
            printf("Invalid choice\n");
            printf("Please, choose another y: ");
            scanf("%i", &y);
        }

        system("clear");
        if (insert_ship(m, ship, x, y, orientation) == -1)
            printf("\nOut of limit!\nChoose again...\n\n");

    }

    printf("\nShips ready!\n");

    // ------------------------------------------------------------------------

    printf("Waiting for ");
    PRINT_YELLOW(opponent_nickname);
    printf("\n");

    s_msg = malloc(sizeof(status_message));
    recv(client_socket, s_msg, sizeof(status_message), 0);

    if (s_msg->response != 2)
    {
        exit(1);
    }
    free(s_msg);

    system("clear");

    // ------------------------------------------------------------------------
    // Game starts

    while(1)
    {
        // Server attacks -----------------------------------------------------
        printf("\n");
        PRINT_CYAN(my_nickname);
        printf(" vs ");
        PRINT_YELLOW(opponent_nickname);
        printf("\n");
        printf("\n");
        show_map(m);
        PRINT_YELLOW(opponent_nickname);
        printf("'s map:\n");
        show_map(client_map);

        printf("Your turn to attack\n");
        printf("x: ");
        scanf("%i", &x);
        printf("y: ");
        scanf("%i", &y);

        // Send attack
        a_msg = malloc(sizeof(attack_message));
        a_msg->type = 2;
        a_msg->x = x;
        a_msg->y = y;
        send(client_socket, a_msg, sizeof(attack_message), 0);
        free(a_msg);

        // Get response
        s_msg = malloc(sizeof(status_message));
        recv(client_socket, s_msg, sizeof(status_message), 0);

        switch (s_msg->response)
        {
            case 0:
                client_map->map[y][x] = MISS;
                break;
            case 1:
                client_map->map[y][x] = HIT;
                break;
            case 3:
                system("clear");
                PRINT_BLUE("\nYOU WON!!!\n\n");
                close(server_socket);
                close(client_socket);
                exit(1);
            default:
                break;
        }
        free(s_msg);

        system("clear");

        // Client attacks -----------------------------------------------------
        printf("\n");
        PRINT_CYAN(my_nickname);
        printf(" vs ");
        PRINT_YELLOW(opponent_nickname);
        printf("\n");
        printf("\n");
        show_map(m);
        PRINT_YELLOW(opponent_nickname);
        printf("'s map:\n");
        show_map(client_map);

        // Receive attack
        printf("Waiting for an attack\n");
        a_msg = malloc(sizeof(attack_message));
        recv(client_socket, a_msg, sizeof(attack_message), 0);

        // Send response
        s_msg = malloc(sizeof(status_message));
        s_msg->type = 3;

        if (attack_ship(m, a_msg->x, a_msg->y) == 1)
        {
            if (check_map(m) == 0)
            {
                s_msg->response = 3;
                send(client_socket, s_msg, sizeof(status_message), 0);
                free(a_msg);
                free(s_msg);
                system("clear");
                PRINT_RED("\nYOU LOST!!!\n\n");
                close(server_socket);
                close(client_socket);
                exit(1);
            }
            else
            {
                s_msg->response = 1;
            }
        }
        else {
            s_msg->response = 0;
        }
        send(client_socket, s_msg, sizeof(status_message), 0);
        free(a_msg);
        free(s_msg);
        system("clear");
    }

    system("clear");
}
