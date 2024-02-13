#include "MapData.h"

MapData::MapData()
{
    this->height = 0;
    this->width = 0;

    this->cities = 0;
    this->road_tiles = 0;

    this->map = nullptr;

    this->nmap = nullptr;
    this->rvis2 = nullptr;
    this->x = nullptr;
}

MapData* MapData::load()
{
    std::cin >> width >> height;

    map = new char* [height];

    nmap = new Node * *[height];
    rvis2 = new int* [height];
    x = new RoadTile * [height];

    for (int i = 0; i < height; i++)
    {
        map[i] = new char[width];

        x[i] = new RoadTile[width];
        rvis2[i] = new int[width];
        nmap[i] = new Node * [width];
        for (int j = 0; j < width; j++)
        {
            std::cin >> map[i][j];
            if (map[i][j] == CITY_SYMBOL)      
                cities++; 
            else if (map[i][j] == ROAD_SYMBOL) 
                road_tiles++;

            rvis2[i][j] = -1;
            nmap[i][j] = nullptr;
        }
    }

    return this;
}

MapData::~MapData()
{
    for (int i = 0; i < height; i++)
    {
        delete[] map[i];

        delete[] nmap[i];
        delete[] rvis2[i];
        delete[] x[i];
    }
    delete[] map;

    delete[] nmap;
    delete[] rvis2;
    delete[] x;
}

bool MapData::out_of_map(int i, int j, char direction)
{
    if (direction == DIR_UP && i - 1 < 0)               return true;
    else if (direction == DIR_DOWN && i + 1 >= height)  return true;
    else if (direction == DIR_LEFT && j - 1 < 0)        return true;
    else if (direction == DIR_RIGHT && j + 1 >= width)  return true;
    else                                                
        return false;    
}

bool MapData::out_of_map(int i, int j)
{
    if ((i < 0) || (i >= height) ||
        (j < 0) || (j >= width))
        return true;
    else
        return false;
}
