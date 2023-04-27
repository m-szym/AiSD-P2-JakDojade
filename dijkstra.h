#pragma once
#include "Graph.h"
#include <algorithm>

class Dijkstra_wrapper {
public:
	List2d<Node>* lnode;
	int current_distance;
};

void my_dijkstra(Graph& g, List2d<Node>* start_city_node, List2d<Node>* end_city_node);
void my_dijkstra2(Graph& g, int start_city_node, int end_city_node);
void my_dijkstra3(Graph& g, int start_city_node, int end_city_node, int mode);
void rec_read_prev(Graph& g, int* prev_arr, int i);

int get_length_of_road_to_node(List2d<Node>* start_city_node, List2d<Node>* end_city_node);

bool node_was_visited(Node* node, Dijkstra_wrapper* t, int tsize);
int get_dw(Node* node, int tsize, Dijkstra_wrapper* t);

int get_arr_i_of_node(Node* node, Graph& g);

// C / C++ program for Dijkstra's
// shortest path algorithm for adjacency
// list representation of graph
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// A structure to represent a
// node in adjacency list
struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode* next;
};

// A structure to represent
// an adjacency list
struct AdjList
{

    // Pointer to head node of list
    struct AdjListNode* head;
};

// A structure to represent a graph.
// A graph is an array of adjacency lists.
// Size of array will be V (number of
// vertices in graph)
struct Graph_out
{
    int V;
    struct AdjList* array;
};


// Structure to represent a min heap node
struct MinHeapNode
{
    int  v;
    int dist;
};

// Structure to represent a min heap
struct MinHeap
{

    // Number of heap nodes present currently
    int size;

    // Capacity of min heap
    int capacity;

    // This is needed for decreaseKey()
    int* pos;
    struct MinHeapNode** array;
};

AdjListNode* newAdjListNode(int dest, int weight);
MinHeapNode* newMinHeapNode(int v, int dist);
struct MinHeap* createMinHeap(int capacity);
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
void minHeapify(struct MinHeap* minHeap, int idx);
int isEmpty(struct MinHeap* minHeap);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
void decreaseKey(struct MinHeap* minHeap, int v, int dist);
bool isInMinHeap(struct MinHeap* minHeap, int v);
void printArr(int dist[], int n);
void dijkstra(struct Graph_out* graph, int src);
struct Graph_out* createGraph(int V);
void addEdge(Graph_out* graph, int src, int dest, int weight);