#include <stdio.h>

#include "util.h"
#include "map.h"

#include "ship.h"

int attack_ship(Map *m, int x, int y)
{
    if (x > m->width || x < 0 || y > m->width || y < 0)
        return -1;

    if (m->map[y][x] == SHIP)
    {
        m->map[y][x] = HIT;
        return 1;
    }
    else {
        m->map[y][x] = MISS;
        return 0;
    }
}

int insert_ship(Map *m, int ship, int x, int y, int orientation)
{
    int i, size;

    switch(ship)
    {
        case AIRCRAFT_CARRIER:
            if (m->ships[0] == 0)
                return -1;
            else
                size = AIRCRAFT_CARRIER_SIZE;
            break;
        case BATTLESHIP:
            if (m->ships[1] == 0)
                return -1;
            else
                size = BATTLESHIP_SIZE;
            break;
        case SUBMARINE:
            if (m->ships[2] == 0)
                return -1;
            else
                size = SUBMARINE_SIZE;
            break;
        case PATROL_BOAT:
            if (m->ships[3] == 0)
                return -1;
            else
                size = PATROL_BOAT_SIZE;
            break;
    }

    if (orientation == VERTICAL)
        if (x >= m->height || y+size-1 >= m->width)
            return -1;

    if (orientation == HORIZONTAL)
        if (y >= m->width || x+size-1 > m->height)
            return -1;

    if (orientation == VERTICAL)
    {
        for (i=y; i<y+size; i++)
            if (m->map[i][x] != 0)
                return -1;

        for (i=y; i<y+size; i++)
                m->map[i][x] = SHIP;
    }

    if (orientation == HORIZONTAL)
    {
        for (i=x; i<x+size; i++)
            if (m->map[y][i] != 0)
                return -1;

        for (i=x; i<x+size; i++)
            m->map[y][i] = SHIP;
    }

    m->ships[ship]--;

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

int check_used_ships(Map *m)
{
    int i, missing = 0;

    for (i=0; i<sizeof(m->ships)/sizeof(int); i++)
        if (m->ships[i] > 0)
            missing += m->ships[i];

    return missing;
}