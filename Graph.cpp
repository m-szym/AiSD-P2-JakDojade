#include "Graph.h"

Graph::Graph(int nodes_to_set)
    :   nodes_n(nodes_to_set), 
        nodes_hashtable(CStringHashTable<Node>(nodes_to_set)),
        nodes_array(new Node*[nodes_to_set])
{
    for (int i = 0; i < nodes_n; i++)
    {
        nodes_array[i] = nullptr;
    }
}

Graph::~Graph()
{
    delete[] nodes_array;
}

Node* Graph::insert_to_hash(Node* node)
{
    nodes_hashtable.insert(node->getName(), node);
    nodes_array[node->getIndex()] = node;

    return node;
}

Node* Graph::get_from_hash(char* name)
{
    return nodes_hashtable[name];
}


