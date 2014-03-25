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

int main()
{

    Map *m = init_map_matrix(10, 10);

    m->aircraft_carrier = 2;
    m->battleship = 1;
    m->submarine = 2;
    m->destroyer = 2;
    m->patrol_boat = 3;

    welcome();
    show_ships();
    int head[2] = {1,2};
    int head2[2] = {0,3};
    insert_ship(m, 5, head, 2);
    insert_ship(m, 5, head2, 1);
    show_map(m);



    // /* Socket setup
    //  */

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

    // countdown();

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

    //     ipaddr = &client_addr.sin_addr;

    //     inet_ntop(server_info->ai_family, ipaddr, ipstr, sizeof(ipstr));

    //     countdown();

    //     // printf("Conexão estabelecida com: %s\n", ipstr);

    // }


    // freeaddrinfo(server_info);
}
