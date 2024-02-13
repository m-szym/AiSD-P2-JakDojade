#pragma once

#include "HashTablet.h"
#include "Node.h"
#include <iostream>



class Graph
{
public:
	int nodes_n;
	Node** nodes_array;
	HashTablet<Node>* nodes_hashtable;

	Node* insert_to_hash(Node* node);
	Node* get_from_hash(char* name);

	Graph(int nodes_to_set);
	~Graph();


};




