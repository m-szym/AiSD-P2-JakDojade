#pragma once

#include <iostream>

#include "Node.h"
#include "Constants.h"
#include "RoadTile.h"

struct MapData
{
    int height;
    int width;

    int cities;
    int road_tiles;

    char** map;

    Node*** nmap;
    int** rvis2;
    RoadTile** x;

    MapData();
    MapData* load();
    ~MapData();

    bool out_of_map(int i, int j, char direction);
    bool out_of_map(int i, int j);

    bool out_of_map_coords(int i, int j, char direction) {
        //if (direction == DIR_UP)
    //{
        if (i < 0) return true;
        //else return false;
    //}
    //if (direction == DIR_DOWN)
    //{
        if (i >= height) return true;
        //else return false;
    //}

    //if (direction == DIR_LEFT)
    //{
        if (j < 0) return true;
        //else return false;
    //}
    //if (direction == DIR_RIGHT)
    //{
        if (j >= width) return true;
        else return false;
        //}

        return true;    //błąd jakiś
    
}

};