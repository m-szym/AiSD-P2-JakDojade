#include "dijkstra.h"

void dijkstra(Graph& g, Node* start_city_node, Node* end_city_node, int mode)
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

    int startNodeIndex = start_city_node->arr_index;
    int endNodeIndex = end_city_node->arr_index;

    knownDistance[startNodeIndex] = 0;


    int k = 0;
    int tmpDistance = 0;
    int tmpEnd = 0;
    int visitedNodes = 0;
    List2d<Link>* link_cur = nullptr;


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

        link_cur = g.nodes_array[k]->links.next;
        while (link_cur != nullptr)
        {
            tmpEnd = link_cur->cont->end_node->arr_index;

            if (wasVisited[tmpEnd] == false)
            {
                if (link_cur->cont->special)
                    tmpDistance = knownDistance[k] + link_cur->cont->length;    
                else
                    tmpDistance = knownDistance[k] + link_cur->cont->length + 1;
 

                if (tmpDistance < knownDistance[tmpEnd])
                {
                    knownDistance[tmpEnd] = tmpDistance;
                    previousStep[tmpEnd] = k;

                    queue.enque(tmpEnd, tmpDistance);
                }         
            }
            link_cur = link_cur->next;
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

            List2dRoot<int> rec;
            while (previousStep[p] >= 0)
            {
                rec.add_at_start(new int(p));
                p = previousStep[p];
            
            }
            List2d<int>* c = rec.start;
            while (c != nullptr)
            {
                if (*(c->cont) >= 0)
                    std::cout << g.nodes_array[*(c->cont)]->name << " ";
                c = c->next;
            
            }
            rec.delete_list();

        
        }
        std::cout << "\n";
    
    }
}
