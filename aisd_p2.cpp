#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include "data_reading_and_manip.h"

int main()
{
    MapData m;
    m.load();

    Graph g(m.citiesNr);

    loadCities(m, g);

    findDirectCityConnections(m, g);

    loadFlights(g);
    
        
    run(g);
}