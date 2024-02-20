#pragma once

#include "CStringHashTable.hpp"
#include "Node.h"

class Graph
{
private:
    int nodesNr;
    Node** nodesArray;                                  //tablica wskaznikow na wezly
    CStringHashTable<Node> nodesNamesHashtable;         //wskaźnik na tablicę mieszającą

public:
    Graph(int newNodesNr);
    ~Graph();

    Node* insertNode(Node* node);
    Node* getNode(char* name);
    Node* getNode(int index);
};




