#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "MapData.h"
#include "Graph.h"
#include "string_helpers.h"


void loadCities(MapData& m, Graph& g);
// We traverse the map (left to right, top to bottom) looking for city names (groups of allowed symbols, i.e. letters)
// upon finding such symbol we read the entire name, create a new node and add it to graph.
// We also mark the location of the city on the cityNodesMask layer of MapData with a pointer to the node
// it'll be used later to find the shortest immediate path between connected cities.

void findDirectCityConnections(MapData& m, Graph& g);
// We find direct connections between cities and add them to the graph.
// BFS is used to traverse the map.


void loadFlights(Graph& g);
// We read the flights (directed connections between cities) from input and add them to the graph.

void run(Graph& g);
// Main working part of the program.
// We read commands, each one a pair of city names (start, end) and mode, 
// find the shortest path between the cities and print it according to mode.
