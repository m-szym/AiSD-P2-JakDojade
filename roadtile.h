#pragma once
struct RoadTile
{
    int x;
    int y;
    int path;
    RoadTile(int yi = 0, int xi = 0, int pathi = 0);
    void unload(int& x, int& y, int& l);
};

void set_road_tile(RoadTile** array_of_road_tiles, int oi, int oj, int i, int j, int path);

