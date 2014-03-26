#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
// #include <netinet/in.h>
#include <unistd.h>

#include "lib/map.h"
#include "lib/ship.h"
#include "lib/util.h"

#define PORT "5000"
#define BACKLOG 10
#define BUFFER 100

// void new_aircraft_carrier(Map *m)
// {
//     int orientation, head[2];

//     system("clear");

//     printf("New aircraft carrier\n");
//     printf("--------------------\n\n");

//     show_ships(m);
//     printf("\n");
//     show_map(m);

//     printf("\n");
//     printf("Choose orientation\n");
//     printf("1) Vertical\n");
//     printf("2) Horizontal\n");
//     printf("- ");
//     scanf("%i", &orientation);
//     printf("\n");

//     printf("Choose head position\n");
//     printf("x: ");
//     scanf("%i", &head[1]);
//     printf("y: ");
//     scanf("%i", &head[0]);
//     printf("\n");

//     insert_ship(m, AIRCRAFT_CARRIER, head, orientation);
// }

// void new_battleship(Map *m)
// {
//     int orientation, head[2];

//     system("clear");

//     printf("New battleship\n");
//     printf("--------------\n\n");

//     show_ships(m);
//     printf("\n");
//     show_map(m);

//     printf("\n");
//     printf("Choose orientation\n");
//     printf("1) Vertical\n");
//     printf("2) Horizontal\n");
//     printf("- ");
//     scanf("%i", &orientation);
//     printf("\n");

//     printf("Choose head position\n");
//     printf("x: ");
//     scanf("%i", &head[1]);
//     printf("y: ");
//     scanf("%i", &head[0]);
//     printf("\n");

//     insert_ship(m, BATTLESHIP, head, orientation);
// }

// void new_submarine(Map *m)
// {
//     int orientation, head[2];

//     system("clear");

//     printf("New submarine\n");
//     printf("-------------\n\n");

//     show_ships(m);
//     printf("\n");
//     show_map(m);

//     printf("\n");
//     printf("Choose orientation\n");
//     printf("1) Vertical\n");
//     printf("2) Horizontal\n");
//     printf("- ");
//     scanf("%i", &orientation);
//     printf("\n");

//     printf("Choose head position\n");
//     printf("x: ");
//     scanf("%i", &head[1]);
//     printf("y: ");
//     scanf("%i", &head[0]);
//     printf("\n");

//     insert_ship(m, SUBMARINE, head, orientation);
// }

// void new_patrol_boat(Map *m)
// {
//     int orientation, head[2];

//     system("clear");

//     printf("New patrol boat\n");
//     printf("---------------\n\n");

//     show_ships(m);
//     printf("\n");
//     show_map(m);

//     printf("\n");
//     printf("Choose orientation\n");
//     printf("1) Vertical\n");
//     printf("2) Horizontal\n");
//     printf("- ");
//     scanf("%i", &orientation);
//     printf("\n");

//     printf("Choose head position\n");
//     printf("x: ");
//     scanf("%i", &head[1]);
//     printf("y: ");
//     scanf("%i", &head[0]);
//     printf("\n");

//     insert_ship(m, PATROL_BOAT, head, orientation);
// }

// void insert_all_ships(Map *m)
// {
//     new_aircraft_carrier(m);
//     new_battleship(m);
//     new_submarine(m);
//     new_submarine(m);
//     new_patrol_boat(m);
//     new_patrol_boat(m);
// }

int main()
{

    int i, ship, x, y, orientation;
    Map *m = init_map_matrix(12, 20);


    welcome();
    // insert_all_ships(m);
    // new_aircraft_carrier(m);
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



    // int head[2] = {1,2};
    // insert_ship(m, 5, head2, 1);



    /* Socket setup
     */

    // int s; // Socket
    // int status; // Errors
    // struct addrinfo hints, *server_info;

    // // -----------------------------------------------------------------------

    // printf("Preparing conection... ");

    // memset(&hints, 0, sizeof(hints));
    // hints.ai_family = AF_UNSPEC;
    // hints.ai_socktype = SOCK_STREAM;
    // hints.ai_flags = AI_PASSIVE;

    // if ((status = getaddrinfo(NULL, PORT, &hints, &server_info)) != 0)
    // {
    //     printf("error\n");
    //     fprintf(stderr, "getaddrinfo: %s !\n", gai_strerror(status));
    //     exit(1);
    // }

    // printf("ok\n");

    // // -----------------------------------------------------------------------

    // printf("Creating socket... ");

    // s = socket(server_info->ai_family, server_info->ai_socktype,
    //            server_info->ai_protocol);

    // printf("ok\n");

    // // -----------------------------------------------------------------------

    // printf("Taking port... ");

    // if ((status = bind(s, server_info->ai_addr, server_info->ai_addrlen)) != 0)
    // {
    //     printf("error\n");
    //     fprintf(stderr, "bind: %i !\n", status);
    //     exit(1);
    // }

    // printf("ok\n");

    // // -----------------------------------------------------------------------

    // // printf("Conectando... ");

    // // if ((status = connect(s, server_info->ai_addr,
    // //      server_info->ai_addrlen)) != 0)
    // // {
    // //     printf("error\n");
    // //     fprintf(stderr, "connect: %i !!!\n", status);
    // //     exit(1);
    // // }

    // // printf("ok\n");

    // // -----------------------------------------------------------------------

    // printf("Listening... ");

    // if ((status = listen(s, BACKLOG)) == -1)
    // {
    //     printf("error\n");
    //     fprintf(stderr, "listen: %i !\n", status);
    //     exit(1);
    // }

    // printf("ok\n");


    // printf("Server is ready... Waiting for client... \n");

    // // -----------------------------------------------------------------------

    // struct sockaddr_in client_addr;
    // struct in_addr *ipaddr;
    // socklen_t addr_size;
    // int s_client;
    // char ipstr[INET6_ADDRSTRLEN];

    // while(1)
    // {
    //     if ((status = accept(s, (struct sockaddr *)&client_addr, &addr_size)) == -1)
    //     {
    //         printf("error\n");
    //         fprintf(stderr, "accept: %i !\n", status);
    //         exit(1);
    //     }

    //     welcome();
    //     show_map(m);

    //     ipaddr = &client_addr.sin_addr;

    //     inet_ntop(server_info->ai_family, ipaddr, ipstr, sizeof(ipstr));


    //     // printf("Conexão estabelecida com: %s\n", ipstr);

    // }


    // freeaddrinfo(server_info);
}
