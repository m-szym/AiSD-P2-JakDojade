#pragma once

#include "CStringHashTable.hpp"
#include "Node.h"
#include "MinHeapQueue.h"

class Graph
{
private:
    int nodesNr;
    Node** nodesArray;                                  
    CStringHashTable<Node> nodesNamesHashtable;  


    void printDijkstraResults(int previousStep[], int knownDistance[], int endNodeIndex, int mode);
public:
    Graph(int newNodesNr);
    ~Graph();

    Node* insertNode(Node* node);
    Node* getNode(char* name);
    Node* getNode(int index);

    void dijkstra(int startNodeIndex, int endNodeIndex, int mode);
    void dijkstra(char* startCityName, char* endCityName, int mode);
    void dijkstra(Node* startCity, Node* endCity, int mode);
};