#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "util.h"


void show_map(Map *m)
{
    int i, j;

    printf("Map:\n");

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

