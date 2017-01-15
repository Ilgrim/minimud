#pragma once

#define  NAMES_MIN        5
#define  NAMES_MAX        45
struct map_t {
    uint8_t rname[NAMES_MAX];
    uint8_t rdesc[BUFFER_LENGTH];
    uint8_t owner[NAMES_MAX];
    uint8_t last_modified[NAMES_MAX];
    _Bool north;
    _Bool south;
    _Bool west;
    _Bool east;
    _Bool down;
    _Bool up;
    _Bool northeast;
    _Bool southeast;
    _Bool southwest;
    _Bool northwest;
}; 
typedef struct map_t Map;
Map *get_room ();
void free_room (const Map map);
#include "Map.c"
