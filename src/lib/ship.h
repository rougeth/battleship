#ifndef _SHIP_H_
#define _SHIP_H_

// Kind of ships
#define AIRCRAFT_CARRIER 0
#define BATTLESHIP 1
#define SUBMARINE 2
#define PATROL_BOAT 3

#define AIRCRAFT_CARRIER_SIZE 5
#define BATTLESHIP_SIZE 4
#define SUBMARINE_SIZE 3
#define PATROL_BOAT_SIZE 2

#define VERTICAL 1
#define HORIZONTAL 2

int insert_ship(Map *m, int ship, int x, int y, int orientation);
void show_ships(Map *m);

int check_used_ships(Map *m);

#endif