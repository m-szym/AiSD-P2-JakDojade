#pragma once

#include <iostream>

#include "Node.h"
#include "Constants.h"

struct MapData
{
    int height;
    int width;

    int citiesNr;
    int road_tiles;

    char** map;

    Node*** cityNodesMask;
    int** lastVisitCycleNr;

    MapData();
    MapData* load();
    ~MapData();

    bool out_of_map(int i, int j, char direction);
    bool out_of_map(int i, int j);

};