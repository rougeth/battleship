#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "map.h"
#include "ship.h"
#include "util.h"


int check_map(Map* m)
{
    int i, j;

    for(i=0; i<m->width; i++)
        for(j=0; j<m->height; j++)
            if (m->map[i][j] == SHIP)
                return 1;

    return 0;
}

void show_ships(Map *m)
{
    int i;

    printf("Size:\t\t\t  1  2  3  4  5\n");

    printf("0) Aircraft carier (%i)\t", m->ships[0]);
    for(i=0;i<AIRCRAFT_CARRIER_SIZE; i++) PRINT_GREEN("  O");

    printf("\n1) Battleship (%i)\t", m->ships[1]);
    for(i=0;i<BATTLESHIP_SIZE; i++) PRINT_GREEN("  O");
    for(i=0;i<AIRCRAFT_CARRIER_SIZE-BATTLESHIP_SIZE; i++) PRINT_BLUE("  ~");

    printf("\n2) Submarine (%i)\t", m->ships[2]);
    for(i=0;i<SUBMARINE_SIZE; i++) PRINT_GREEN("  O");
    for(i=0;i<AIRCRAFT_CARRIER_SIZE-SUBMARINE_SIZE; i++) PRINT_BLUE("  ~");

    printf("\n3) Patrol boat (%i)\t", m->ships[3]);
    for(i=0;i<PATROL_BOAT_SIZE; i++) PRINT_GREEN("  O");
    for(i=0;i<AIRCRAFT_CARRIER_SIZE-PATROL_BOAT_SIZE; i++) PRINT_BLUE("  ~");

    printf("\n\n");
}

void show_map(Map *m)
{
    int i, j;

    // Print first line
    printf(" y\\x ");
    for (i=0; i<m->height; i++)
        if (i<10)
            printf("%i  ", i);
        else
            printf("%i ", i);

    printf("\n");

    // Print letters line
    for (i=0; i<m->width; i++)
    {
        // Print letter
        if (i<10)
            printf("  %i", i);
        else
            printf(" %i", i);

        for (j=0; j<m->height; j++)
        {
            switch(m->map[i][j])
            {
                case WATER:
                    PRINT_BLUE("  ~");
                    break;
                case MISS:
                    PRINT_RED("  ~");
                    break;
                case SHIP:
                    PRINT_GREEN("  O");
                    break;
                case HIT:
                    PRINT_RED("  X");
                    break;
                default:
                    printf("  ?");
                    break;
            }
            // printf("  %i", m->map[i][j]);

        }
        printf("\n");
    }
    printf("\n");
}

Map *init_map_matrix(int width, int height)
{
    Map *m = malloc(sizeof(Map));
    int i, j;

    m->width = width;
    m->height = height;

    m->map = malloc(m->width * sizeof(int *));

    for(i=0; i<m->width; i++)
    {
        m->map[i] = malloc(m->height * sizeof(int));
        for(j=0; j<m->height; j++)
            m->map[i][j] = 0;
    }

    m->ships[0] = 1;
    m->ships[1] = 1;
    m->ships[2] = 2;
    m->ships[3] = 2;

    return m;
}

