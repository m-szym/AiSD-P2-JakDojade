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

void Graph::printDijkstraResults(int previousStep[], int knownDistance[], int endNodeIndex, int mode)
{
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

void Graph::dijkstra(int startNodeIndex, int endNodeIndex, int mode)
{
    int knownDistance[nodesNr]; 
    bool wasVisited[nodesNr];
    int previousStep[nodesNr];
    MinHeapQueue queue = MinHeapQueue(2*nodesNr);

    for (int i = 0; i < 2*nodesNr; i++)
    {
        if (i < nodesNr)
        {
            knownDistance[i] = INT_MAX;
            previousStep[i] = -1;
            wasVisited[i] = false;
        }
        queue[i].setNode(-1, INT_MAX);
    }
    knownDistance[startNodeIndex] = 0;
    queue.enque(startNodeIndex, 0);

    int currentNodeIndex = 0;
    int tmpDistance = 0;
    int tmpEnd = 0;
    LinkedListNode<Link*>* currentLink = nullptr;


    while(queue.getQueueSize() >= 0)
    {
        currentNodeIndex = queue[queue.top()].getIndex();
        queue.deque();

        if (currentNodeIndex == endNodeIndex) 
            break;

        if (wasVisited[currentNodeIndex] == false)
            wasVisited[currentNodeIndex] = true;


        currentLink = nodesArray[currentNodeIndex]->getLinks().getHead();
        while (currentLink != nullptr)
        {
            tmpEnd = currentLink->getData()->getEndNode()->getIndex();

            if (wasVisited[tmpEnd] == false)
            {
                tmpDistance = knownDistance[currentNodeIndex] + currentLink->getData()->getLength();

                if (!currentLink->getData()->isSpecial())
                    tmpDistance += 1;
 

                if (tmpDistance < knownDistance[tmpEnd])
                {
                    knownDistance[tmpEnd] = tmpDistance;
                    previousStep[tmpEnd] = currentNodeIndex;

                    queue.enque(tmpEnd, tmpDistance);
                }         
            }
            currentLink = currentLink->getNext();
        }           
    }

    printDijkstraResults(previousStep, knownDistance, endNodeIndex, mode);
}

