#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
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


int main(int argc, char *argv[])
{
    Map *m = init_map_matrix(10, 10);

    int i, ship, x, y, orientation; // Ship insertion
    char my_nickname[30], opponent_nickname[30];

    // Socket stuff
    int server_socket;
    struct addrinfo hints, *server_info;
    int status;
    char server_ip[INET6_ADDRSTRLEN];

    // Messages
    int end_game;
    introducion_message *i_msg;
    attack_message *a_msg;
    response_message *r_msg;


    welcome();

    // Just for test!
    insert_ship(m, 0, 0, 0, 2);
    insert_ship(m, 1, 6, 0, 2);
    insert_ship(m, 2, 0, 2, 1);
    insert_ship(m, 2, 0, 6, 1);
    insert_ship(m, 3, 1, 9, 2);
    insert_ship(m, 3, 4, 9, 2);

    while((i = check_used_ships(m)) > 0)
    {
        show_map(m);
        show_ships(m);

        printf("You still have %i ship(s) to organize\n", i);
        printf("Choose one to put in the map: ");
        scanf("%i", &ship);
        printf("Ship head position\n");
        printf("x: ");
        scanf("%i", &x);
        printf("y: ");
        scanf("%i", &y);
        printf("Orientation (1-vert/2-hori): ");
        scanf("%i", &orientation);
        insert_ship(m, ship, x, y, orientation);

        system("clear");
    }

    show_map(m);

    printf("Ships ready!\n");

    printf("Nickname: ");
    fgets(my_nickname, 30, stdin);
    if (my_nickname[strlen(my_nickname) - 1] == '\n')
        my_nickname[strlen(my_nickname) - 1] = '\0';

    // ----------------------------------------------------------------------

    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(argv[1], PORT, &hints, &server_info)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    // loop through all the results and connect to the first we can
    if ((server_socket = socket(server_info->ai_family,
        server_info->ai_socktype, server_info->ai_protocol)) == -1) {
        perror("client: socket");
    }

    if (connect(server_socket, server_info->ai_addr,
                server_info->ai_addrlen) == -1) {
        close(server_socket);
        perror("client: connect");
    }

    if (server_info == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(server_info->ai_family,
              get_in_addr((struct sockaddr *)server_info->ai_addr), server_ip,
              sizeof server_ip);
    printf("client: connecting to %s\n", server_ip);

    freeaddrinfo(server_info); // all done with this structure

    // ------------------------------------------------------------------------
    // Send and receive introduction message

    i_msg = malloc(sizeof(introducion_message));

    if ((status = recv(server_socket, i_msg, sizeof(introducion_message), 0)) == -1) {
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

    Map *server_map = init_map_matrix(10, 10);

    while(1)
    {
        // Server attacks -----------------------------------------------------
        a_msg = malloc(sizeof(attack_message));
        printf("you: %s vs %s\n", my_nickname, opponent_nickname);
        printf("Your map:\n");
        show_map(m);
        printf("%s's map:\n", opponent_nickname);
        show_map(server_map);

        // Receive attack
        printf("Waiting for an attack\n");
        recv(server_socket, a_msg, sizeof(attack_message), 0);


        // Send response
        r_msg = malloc(sizeof(response_message));
        r_msg->type = 3;
        r_msg->response = attack_ship(m, a_msg->x, a_msg->y);

        if (r_msg->response == 1)
        {
            if (m->total == 1)
            {
                end_game = 0;
                break;
            }
            else
                m->total--;
        }
        send(server_socket, r_msg, sizeof(response_message), 0);
        free(a_msg);
        free(r_msg);

        system("clear");

        // Your turn to attack ------------------------------------------------
        printf("you: %s vs %s\n", my_nickname, opponent_nickname);
        printf("Your map:\n");
        show_map(m);
        printf("%s's map:\n", opponent_nickname);
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
        r_msg = malloc(sizeof(response_message));
        recv(server_socket, r_msg, sizeof(response_message), 0);
        if (r_msg->response == 1)
        {
            server_map->map[y][x] = HIT;
            if (server_map->total == 1)
            {
                end_game = 1;
                break;
            }
            else
                server_map->total--;
        }
        else {
            server_map->map[y][x] = MISS;
        }
        free(r_msg);

        // // Send ok
        // r_msg->response = OK;
        // send(server_socket, r_msg, sizeof(response_message), 0);

        system("clear");

    }

    close(server_socket);

    return 0;

}
