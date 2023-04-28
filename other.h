#pragma once

#define _CRT_SECURE_NO_WARNINGS

//#include "Graph.h"
#include "Constants.h"
#include "dijkstra.h"

//#include "HashTablet.h"

char* find_name(char** map, int width, int height, int oi, int oj);

char* read_name(char** map, int width, int height, int oi, int oj);

int count_letters(char** map, int width, int height, int oi, int oj, char direction, int count);

void read_path(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction);
void read_path2(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction);

void read_all_paths(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node);

char* read_flight_declaration();

void read_flight(Graph& g);

void register_star(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int strlen);

void do_command(Graph& g);
bool out_of_map(int width, int height, int i, int j, char direction);

