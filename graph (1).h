#pragma once

#include "HashTablet.h"
#include "Node.h"
#include <iostream>



class Graph
{
public:
	int nodes_n;
	Node* nodes;
	List2d<Node> nods;

	Node** nar;
	HashTablet<Node>* hash_nodes;
	Node* insert_to_hash(Node* node);
	Node* get_from_hash(char* name);

	Graph(int nodes_to_set);
	~Graph();

	void print_graph();
	void print_nodes();
	List2d<Node>* get_city_by_name(char* name);
	int get_city_node_i_by_name(char* name);
};




