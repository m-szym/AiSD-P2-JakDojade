#pragma once

#include <iostream>

#include "Node.h"
#include "Constants.h"
#include "RoadTile.h"

struct MapData
{
    int height;
    int width;

    int citiesNr;
    int road_tiles;

    char** map;

    Node*** cityNodesMask;
    int** rvis2;
    RoadTile** x;

    MapData();
    MapData* load();
    ~MapData();

    bool out_of_map(int i, int j, char direction);
    bool out_of_map(int i, int j);

};