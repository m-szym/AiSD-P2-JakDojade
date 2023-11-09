#pragma once
#include "Graph.h"
#include "PriorityQueueList2d.h"

struct minh_node
{
    //bool visited;
    int distance;
    int nar_index;

    void set(int i, int d) {
        this->distance = d;
        this->nar_index = i;
    }
    minh_node(int i = -1, int d = INT_MAX) {
        distance = d;
        nar_index = i;
    }


};

bool operator<(minh_node n1, minh_node n2);

void enq(minh_node pr[], int& size, int nar_i, int dist);
int top(minh_node pr[], int size);
void deq(minh_node pr[], int& size);


void my_dijkstra5(Graph& g, Node* start_city_node, Node* end_city_node, int mode);


