#include "data_reading_and_manip.h"


int main()
{
    // read map (in text format) from stin into MapData object
    MapData m;
    m.load();
    
    // prepare graph of cities on the map
    Graph g(m.citiesNr);
    // load cities from map into the graph
    loadCities(m, g);
    // load flights from stdin, parse them 
    // and add directly into the graph (as directed, weighted edges)
    loadFlights(g);
    // find direct connections (roads) between cities on map (with BFS)
    // and add them to the graph (as undirected, weighted edges)
    findDirectCityConnections(m, g);
    
    // as we don't need the map anymore, we release its memory
    m.clear();

    // at this point we have a graph with cities (as vertices) 
    // and connections (i.e. roads and flights) (as edges) between them
    // we can now run the queries,
    // each one asking for the shortest path between two cities
    run(g);
}