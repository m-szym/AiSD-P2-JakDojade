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

void find_first_level_connections(MapData& m, Graph& g);
//uses main_bfs20()

void main_bfs20(MapData& m, Node* o_start_node, int start_node_i, int start_node_j);
//uses update_skipper()

void update_skipper(int inner_limit, int& outer, int& inner);



void read_flights(Graph& g);
//uses read_flight()

void read_flight(Graph& g);
//uses read_flight_declaration()

char* read_flight_declaration();