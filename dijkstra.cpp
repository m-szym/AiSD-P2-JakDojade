#include "dijkstra.h"

void dijkstra(Graph& g, Node* startCity, Node* endCity, int mode)
{
    int nodes = g.nodes_n;

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

    int startNodeIndex = startCity->getIndex();
    int endNodeIndex = endCity->getIndex();

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

        currentLink = g.nodes_array[k]->getLinks().getHead();
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
                    std::cout << g.nodes_array[c->getData()]->getName() << " ";

                c = c->getNext();
            }      
        }
        std::cout << "\n";
    
    }
}
