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
    Map *server_map = init_map_matrix(MAP_WIDTH, MAP_HEIGH);
    int i, ship, x, y, orientation; // Ship insertion
    char my_nickname[30], opponent_nickname[30];

    // Socket settings
    int server_socket;
    struct addrinfo hints, *server_info;
    int status;
    char server_ip[INET6_ADDRSTRLEN];

    // Messages settings
    int end_game;
    status_message *s_msg;
    introducion_message *i_msg;
    attack_message *a_msg;

    // ------------------------------------------------------------------------

    if (argc != 3) {
        fprintf(stderr,"usage: client hostname port\n");
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

    if ((status = getaddrinfo(argv[1], argv[2], &hints, &server_info)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    // loop through all the results and connect to the first we can
    if ((server_socket = socket(server_info->ai_family,
        server_info->ai_socktype, server_info->ai_protocol)) == -1) {
        perror("socket");
    }

    if (connect(server_socket, server_info->ai_addr,
                server_info->ai_addrlen) == -1) {
        close(server_socket);
        perror("Connection");
    }

    inet_ntop(server_info->ai_family,
              get_in_addr((struct sockaddr *)server_info->ai_addr), server_ip,
              sizeof server_ip);

    freeaddrinfo(server_info); // all done with this structure

    // ------------------------------------------------------------------------
    // Send and receive introduction message

    i_msg = malloc(sizeof(introducion_message));

    if ((status = recv(server_socket, i_msg,
        sizeof(introducion_message), 0)) == -1) {
        perror("recv");
        exit(1);
    }
    strcpy(opponent_nickname, i_msg->nickname);

    strcpy(i_msg->nickname, my_nickname);
    if (send(server_socket, i_msg, sizeof(introducion_message), 0) == -1)
    {
        perror("send");
        exit(1);
    }

    free(i_msg);

    system("clear");
    printf("Opponent ready! ");
    PRINT_YELLOW(opponent_nickname);
    printf(" (%s)\n\n", server_ip);

    // ------------------------------------------------------------------------
    // Put the ships in the map

    while((i = check_used_ships(m)) > 0)
    {
        show_map(m);
        show_ships(m);

        printf("You still have %i ship(s) to organize\n", i);
        printf("Choose one to put in the map: ");
        scanf("%i", &ship);
        while(ship > 3 || ship < 0)
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

    show_map(m);

    system("clear");

    printf("\nShips ready!\n");

    // ------------------------------------------------------------------------

    s_msg = malloc(sizeof(status_message));
    s_msg->type = 3;
    s_msg->response = 2;
    send(server_socket, s_msg, sizeof(status_message), 0);
    free(s_msg);

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
        show_map(server_map);

        // Receive attack
        printf("Waiting for an attack\n");
        a_msg = malloc(sizeof(attack_message));
        recv(server_socket, a_msg, sizeof(attack_message), 0);

        // Send response
        s_msg = malloc(sizeof(status_message));
        s_msg->type = 3;

        if (attack_ship(m, a_msg->x, a_msg->y) == 1)
        {
            if (check_map(m) == 0)
            {
                s_msg->response = 3;
                send(server_socket, s_msg, sizeof(status_message), 0);
                free(a_msg);
                free(s_msg);
                system("clear");
                PRINT_RED("\nYOU LOST!!!\n\n");
                close(server_socket);
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

        send(server_socket, s_msg, sizeof(status_message), 0);
        free(a_msg);
        free(s_msg);

        system("clear");

        // Your turn to attack ------------------------------------------------
        printf("\n");
        PRINT_CYAN(my_nickname);
        printf(" vs ");
        PRINT_YELLOW(opponent_nickname);
        printf("\n");
        printf("\n");
        show_map(m);
        PRINT_YELLOW(opponent_nickname);
        printf("'s map:\n");
        show_map(server_map);

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
        send(server_socket, a_msg, sizeof(attack_message), 0);
        free(a_msg);

        // Get response
        s_msg = malloc(sizeof(status_message));
        printf("(AQUI)\n");
        recv(server_socket, s_msg, sizeof(status_message), 0);

        switch (s_msg->response)
        {
            case 0:
                server_map->map[y][x] = MISS;
                break;
            case 1:
                server_map->map[y][x] = HIT;
                break;
            case 3:
                system("clear");
                PRINT_BLUE("\nYOU WON!!!\n\n");
                close(server_socket);
                exit(1);
            default:
                break;
        }
        free(s_msg);

        system("clear");
    }

    close(server_socket);

    return 0;

}
