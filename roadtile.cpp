#include "RoadTile.h"

RoadTile::RoadTile(int yi, int xi, int pathi)
{
	x = xi;
	y = yi;
	path = pathi;
}

void RoadTile::unload(int& x, int& y, int& path_length)
{
	x = this->x;
	y = this->y;
	path_length = this->path;
}

void set_road_tile(RoadTile** array_of_road_tiles, int oi, int oj, int i, int j, int path)
{
	array_of_road_tiles[oi][oj].x = j;
	array_of_road_tiles[oi][oj].y = i;
	array_of_road_tiles[oi][oj].path = path;
}