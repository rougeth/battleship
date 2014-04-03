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

char opponent_nickname[30];

int main(int argc, char *argv[])
{
    Map *m = init_map_matrix(10, 10);

    int i, ship, x, y, orientation; // ship insertion
    char my_nickname[30];


    /* Welcome screen
     */
    welcome();

    /* Get nickname
     */
    printf("Insert your nickname: ");
    fgets(my_nickname, 30, stdin);
    if (my_nickname[strlen(my_nickname) - 1] == '\n')
        my_nickname[strlen(my_nickname) - 1] = '\0';

    system("clear");

    /* Insert ships until its done
     */
    while((i = check_used_ships(m)) > 0)
    {
        // Show the map and the ships
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

        printf("Orientation (1-vert/2-hori): ");
        scanf("%i", &orientation);
        while(orientation != 1 || orientation != 2)
        {
            printf("Invalid choice\n");
            printf("Please, choose another option: ");
            scanf("%i", &orientation);
        }

        insert_ship(m, ship, x, y, orientation);

        system("clear");
    }

    show_map(m);

    printf("ships ready!\n");
}
