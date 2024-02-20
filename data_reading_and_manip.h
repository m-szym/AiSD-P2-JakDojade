#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "MapData.h"
#include "Graph.h"
#include "string_helpers.h"


void load_cities(MapData& m, Graph& g);
// We traverse the map (left to right, top to bottom) looking for city names (groups of allowed symbols, i.e. letters)
// upon finding such symbol we read the entire name, create a new node and add it to graph.
// We also mark the location of the city on the cityNodesMask layer of MapData with a pointer to the node
// it'll be used later to find the shortest immediate path between connected cities.

void findDirectCityConnections(MapData& m, Graph& g);
// We find direct connections between cities and add them to the graph.
// BFS is used to traverse the map.

void read_flights(Graph& g);
//uses read_flight()

void read_flight(Graph& g);
//uses read_flight_declaration()

char* read_flight_declaration();