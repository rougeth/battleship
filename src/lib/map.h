#ifndef _MAP_H_
#define _MAP_H_

// Size of the map
#define MAP_WIDTH 10
#define MAP_HEIGH 10

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
void show_map(Map *m);
Map *init_map_matrix(int width, int height);


#endif