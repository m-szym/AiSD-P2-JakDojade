#include "Graph.h"

Node* Graph::insert_to_hash(Node* node)
{
        this->nodes_hashtable->insert(node->name, node);
        this->nodes_array[node->arr_index] = node;

        return node;
}

Node* Graph::get_from_hash(char* name)
{
        return this->nodes_hashtable->operator[](name);
}

Graph::Graph(int nodes_to_set)
{
        this->nodes_n = nodes_to_set;

        this->nodes_hashtable = new HashTablet<Node>(nodes_n);
        this->nodes_array = new Node*[nodes_n];

        for (int i = 0; i < nodes_n; i++)
        {
                nodes_array[i] = nullptr;
        
}
}

Graph::~Graph()
{
        delete nodes_hashtable;
        delete[] nodes_array;
}
