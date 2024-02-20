#pragma once

#include "CStringHashTable.hpp"
#include "Node.h"



class Graph
{
public:
        int nodes_n;
        Node** nodes_array;                     //tablica wskaznikow na wezly
        CStringHashTable<Node> nodes_hashtable;      //wskaźnik na tablicę mieszającą

        Node* insert_to_hash(Node* node);
        Node* get_from_hash(char* name);

        Graph(int nodes_to_set);
        ~Graph();


};




