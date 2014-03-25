#include <stdio.h>

#include "util.h"

#include "ship.h"


void show_ships()
{
    int i;

    printf("Size:\t\t\t  1  2  3  4  5\n");

    printf("1) Aircraft carier\t");
    for(i=0;i<AIRCRAFT_CARRIER; i++) PRINT_GREEN("  O");

    printf("\n2) Battleship\t\t");
    for(i=0;i<BATTLESHIP; i++) PRINT_GREEN("  O");
    for(i=0;i<AIRCRAFT_CARRIER-BATTLESHIP; i++) PRINT_BLUE("  ~");

    printf("\n3) Submarine\t\t");
    for(i=0;i<SUBMARINE; i++) PRINT_GREEN("  O");
    for(i=0;i<AIRCRAFT_CARRIER-SUBMARINE; i++) PRINT_BLUE("  ~");

    printf("\n4) Destroyer\t\t");
    for(i=0;i<DESTROYER; i++) PRINT_GREEN("  O");
    for(i=0;i<AIRCRAFT_CARRIER-DESTROYER; i++) PRINT_BLUE("  ~");

    printf("\n5) Patrol boat\t\t");
    for(i=0;i<PATROL_BOAT; i++) PRINT_GREEN("  O");
    for(i=0;i<AIRCRAFT_CARRIER-PATROL_BOAT; i++) PRINT_BLUE("  ~");

    printf("\n");
}