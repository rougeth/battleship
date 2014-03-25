#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "ship.h"
#include "util.h"


void show_map(Map *m)
{
    int i, j;

    // Print first line
    printf("\\");
    for (i=0; i<m->width; i++)
        printf("  %i", i);
    printf("\n");

    // Print letters line
    for (i=0; i<m->width; i++)
    {
        // Print letter
        printf("%i", i);

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

    return m;
}

#define AIRCRAFT_CARRIER 5
#define BATTLESHIP 4
#define SUBMARINE 3
#define DESTROYER 3
#define PATROL_BOAT 2

int insert_ship(Map *m, int ship, int *head, int way)
{
    int i;

    switch(ship)
    {
        case AIRCRAFT_CARRIER:
            if (m->aircraft_carrier == 0)
                return -1;
        case BATTLESHIP:
            if (m->battleship == 0)
                return -1;
        case SUBMARINE:
            if (m->submarine == 0)
                return -1;
        case DESTROYER:
            if (m->destroyer == 0)
                return -1;
    }

    if (way == VERTICAL)
        if (head[0] <= m->width && head[1]+ship-1 >= m->height)
            return -1;

    if (way == HORIZONTAL)
        if (head[1] <= m->height && head[0]+ship-1 >= m->width)
            return -1;

    if (way == VERTICAL)
    {
        for (i=head[0]; i<head[0]+AIRCRAFT_CARRIER; i++)
            if (m->map[i][head[1]] != 0)
                return -1;

        for (i=head[0]; i<head[0]+AIRCRAFT_CARRIER; i++)
                m->map[i][head[1]] = SHIP;
    }

    if (way == HORIZONTAL)
    {
        for (i=head[1]; i<head[1]+AIRCRAFT_CARRIER; i++)
            if (m->map[head[0]][i] != 0)
                return -1;

        for (i=head[1]; i<head[1]+AIRCRAFT_CARRIER; i++)
            m->map[head[0]][i] = SHIP;
    }

    return 0;
}