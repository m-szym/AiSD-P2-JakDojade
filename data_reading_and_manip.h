#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "MapData.h"
#include "Graph.h"
#include "string_helpers.h"


void load_cities(MapData& m, Graph& g);
//uses read_name() and register_star()

char* read_name(MapData& m, Graph& g, int oi, int oj);
//uses count_letters()

int count_letters(MapData& m, Graph& g, int oi, int oj, char direction, int count);

void register_star(MapData& m, Graph& g, Node* o_start_node, int oi, int oj, int strlen);


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