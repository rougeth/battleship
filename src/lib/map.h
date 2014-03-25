#ifndef _MAP_H_
#define _MAP_H_

// Size of the map
#define MAP_WIDTH 10
#define MAP_HEIGH 10

// Kind of points in the map
#define WATER 0
#define MISS 1
#define HIT 2

#define SHIP_HEAD_UP 31
#define SHIP_HEAD_RIGHT 32
#define SHIP_HEAD_BOTTOM 33
#define SHIP_HEAD_LEFT 32
#define SHIP 3

// Symbols
#define WATER_SYMBOL ~
#define MISS_SYMBOL ~
#define HIT_SYMBOL X
#define SHIP_SYMBOL O

typedef struct map
{
    int width;
    int height;
    int **map;

    int aircraft_carrier;
    int battleship;
    int submarine;
    int destroyer;
    int patrol_boat;
} Map;

void show_map(Map *m);

Map *init_map_matrix(int width, int height);

int insert_ship(Map *m, int ship, int *head, int way);

#endif