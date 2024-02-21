#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include "data_reading_and_manip.h"

MapData loadData()
{
    MapData m;
    m.load();
    return m;
}

Graph createGraph(MapData& m)
{
    Graph g(m.citiesNr);
    loadCities(m, g);
    loadFlights(g);
    findDirectCityConnections(m, g);
    return g;
}

int main()
{
    MapData m = loadData();
    Graph g = createGraph(m);

    run(g);
}