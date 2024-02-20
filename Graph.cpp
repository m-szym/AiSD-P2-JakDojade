#include "Graph.h"

Graph::Graph(int nodes_to_set)
    :   nodesNr(nodes_to_set), 
        nodesNamesHashtable(CStringHashTable<Node>(nodes_to_set)),
        nodesArray(new Node*[nodes_to_set])
{
    for (int i = 0; i < nodesNr; i++)
    {
        nodesArray[i] = nullptr;
    }
}

Graph::~Graph()
{
    delete[] nodesArray;
}

Node* Graph::insertNode(Node* node)
{
    nodesNamesHashtable.insert(node->getName(), node);
    nodesArray[node->getIndex()] = node;

    return node;
}

Node* Graph::getNode(char* name)
{
    return nodesNamesHashtable[name];
}

Node* Graph::getNode(int index)
{
    return nodesArray[index];
}


