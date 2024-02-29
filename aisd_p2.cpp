#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include "data_reading_and_manip.h"


int main()
{
    // read map (in text format) from stin into MapData object
    MapData m;
    m.load();
    

    Graph g(m.citiesNr);
    loadCities(m, g);
    loadFlights(g);
    findDirectCityConnections(m, g);
    
    run(g);
}