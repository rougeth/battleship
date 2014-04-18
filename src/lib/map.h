#ifndef _MAP_H_
#define _MAP_H_


// Kind of points in the map
#define WATER 0
#define MISS 1
#define HIT 2
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

    // ships[0] -> aircraft carrier
    // ships[1] -> battleship
    // ships[2] -> submarine
    // ships[3] -> patrol boat
    int ships[4];
    int total;
} Map;


// Map funcionts
int check_map(Map *);
void show_ships(Map *);
void show_map(Map *);
Map *init_map_matrix(int, int);


#endif