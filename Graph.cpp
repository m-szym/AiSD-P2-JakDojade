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

void Graph::dijkstra(char* startCityName, char* endCityName, int mode)
{
    int startNodeIndex = nodesNamesHashtable[startCityName]->getIndex();
    int endNodeIndex = nodesNamesHashtable[endCityName]->getIndex();

    dijkstra(startNodeIndex, endNodeIndex, mode);
}

void Graph::dijkstra(Node* startCity, Node* endCity, int mode)
{
    int startNodeIndex = startCity->getIndex();
    int endNodeIndex = endCity->getIndex();

    dijkstra(startNodeIndex, endNodeIndex, mode);
}

void Graph::dijkstra(int startNodeIndex, int endNodeIndex, int mode)
{
    int nodes = nodesNr;

    int knownDistance[nodes]; 
    bool wasVisited[nodes];
    int previousStep[nodes];

    MinHeapQueue queue = MinHeapQueue(2*nodes);

    for (int i = 0; i < 2*nodes; i++)
    {
        if (i < nodes)
        {
            knownDistance[i] = INT_MAX;
            previousStep[i] = -1;
            wasVisited[i] = false;
        }
        queue[i].setNode(-1, INT_MAX);
    }

    knownDistance[startNodeIndex] = 0;


    int k = 0;
    int tmpDistance = 0;
    int tmpEnd = 0;
    int visitedNodes = 0;
    LinkedListNode<Link*>* currentLink = nullptr;


    queue.enque(startNodeIndex, 0);

    while(queue.getQueueSize() >= 0)
    {
        k = queue[queue.top()].getIndex();
        queue.deque();

        if (k == endNodeIndex) 
            break;

        if (wasVisited[k] == false)
        {
            wasVisited[k] = true;
            visitedNodes++;
        }

        currentLink = nodesArray[k]->getLinks().getHead();
        while (currentLink != nullptr)
        {
            tmpEnd = currentLink->getData()->getEndNode()->getIndex();

            if (wasVisited[tmpEnd] == false)
            {
                if (currentLink->getData()->isSpecial())
                    tmpDistance = knownDistance[k] + currentLink->getData()->getLength();    
                else
                    tmpDistance = knownDistance[k] + currentLink->getData()->getLength() + 1;
 

                if (tmpDistance < knownDistance[tmpEnd])
                {
                    knownDistance[tmpEnd] = tmpDistance;
                    previousStep[tmpEnd] = k;

                    queue.enque(tmpEnd, tmpDistance);
                }         
            }
            currentLink = currentLink->getNext();
        }           
    }


    if (mode == 0)
    {
        std::cout << knownDistance[endNodeIndex] << "\n";
    }
    else if (mode == 1)
    {
        std::cout << knownDistance[endNodeIndex] << " ";

        if (previousStep[endNodeIndex] >= 0)
        {
            int p = previousStep[endNodeIndex];

            LinkedList<int> rec;
            while (previousStep[p] >= 0)
            {
                rec.pushFront(p);
                p = previousStep[p];
            }
            LinkedListNode<int>* c = rec.getHead();
            while (c != nullptr)
            {
                if (c != nullptr)
                    std::cout << nodesArray[c->getData()]->getName() << " ";

                c = c->getNext();
            }      
        }
        std::cout << "\n";
    
    }
}

