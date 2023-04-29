#include "dijkstra.h"

void my_dijkstra(Graph& g, List2d<Node>* start_city_node, List2d<Node>* end_city_node)
{
	int nodes = g.nodes_n;
    Node* start = start_city_node->cont;
    Node* end = end_city_node->cont;

    int* dist_arr = new int[nodes];
    bool* vis_arr = new bool[nodes];
    int* prev_arr = new int[nodes];

    for (int i = 0; i < nodes; i++)
    {
        dist_arr[i] = INT_MAX;
        prev_arr[i] = -1;
        vis_arr[i] = false;
    }

    int start_i = get_arr_i_of_node(start_city_node->cont, g);
    int end_i = get_arr_i_of_node(end_city_node->cont, g);

    /*int start_i = 6;
    int end_i = 4;*/

    dist_arr[start_i] = 0;


    int k = 0;
    int tmp_dist = 0;
    int tmp_end = 0;
    int visited = 0;

    List2d<Link>* link_cur = g.nodes[k].links.next;

    int minv = 0;
    int mini = 0;

    while (visited < nodes)
    {
        minv = INT_MAX;
        for (int i = 0; i < nodes; i++)
        {
            if (vis_arr[i] == true) 
                continue;
            if (dist_arr[i] < minv)
                minv = dist_arr[i];
        }
        for (int i = 0; i < nodes; i++)
        {
            if (dist_arr[i] == minv)
            {
                mini = i;
                break;
            }
        }
        k = mini;

        vis_arr[k] = true;
        visited++;

        link_cur = g.nodes[k].links.next;
        while (link_cur != nullptr)
        {
            tmp_end = link_cur->cont->end_node->arr_index;

            if (vis_arr[tmp_end] == false)
            {

                tmp_dist = dist_arr[k] + link_cur->cont->length;
                if (tmp_dist < dist_arr[tmp_end])
                {
                    dist_arr[tmp_end] = tmp_dist;
                    prev_arr[tmp_end] = k;
                }
            }
            link_cur = link_cur->next;
        }
    }

    std::cout << "Odleg³oœci od " << g.nodes[start_i].name << "\n";
    for (int i = 0; i < nodes; i++)
    {
        if (i == start_i) continue;
        std::cout << "\tDo " << g.nodes[i].name << " : " << dist_arr[i] << /*" , ostatni stop w " << g.nodes[prev_arr[i]].name << */"\n";
    }
    std::cout << "Szukano do" << g.nodes[end_i].name << " i znaleziono " << dist_arr[end_i];



    delete[] dist_arr;
    delete[] vis_arr;
    delete[] prev_arr;
}

void my_dijkstra2(Graph& g, int start_city_node, int end_city_node)
{
    int nodes = g.nodes_n;


    int* dist_arr = new int[nodes];
    bool* vis_arr = new bool[nodes];
    int* prev_arr = new int[nodes];

    for (int i = 0; i < nodes; i++)
    {
        dist_arr[i] = INT_MAX;
        prev_arr[i] = -1;
        vis_arr[i] = false;
    }

    int start_i = start_city_node;
    int end_i = end_city_node;

    /*int start_i = 6;
    int end_i = 4;*/

    dist_arr[start_i] = 0;


    int k = 0;
    int tmp_dist = 0;
    int tmp_end = 0;
    int visited = 0;

    List2d<Link>* link_cur = g.nodes[k].links.next;

    int minv = 0;
    int mini = 0;

    while (visited < nodes)
    {
        minv = INT_MAX;
        for (int i = 0; i < nodes; i++)
        {
            if (vis_arr[i] == true)
                continue;
            if (dist_arr[i] < minv)
                minv = dist_arr[i];
        }
        for (int i = 0; i < nodes; i++)
        {
            if (dist_arr[i] == minv)
            {
                mini = i;
                break;
            }
        }
        k = mini;

        vis_arr[k] = true;
        visited++;

        link_cur = g.nodes[k].links.next;
        while (link_cur != nullptr)
        {
            tmp_end = link_cur->cont->end_node->arr_index;

            if (vis_arr[tmp_end] == false)
            {

                //tmp_dist = dist_arr[k] + link_cur->cont->length;
                tmp_dist = dist_arr[k] + link_cur->cont->length + 1;    //za odwiedzenia miasta
                if (tmp_dist < dist_arr[tmp_end])
                {
                    dist_arr[tmp_end] = tmp_dist;
                    prev_arr[tmp_end] = k;
                }
            }
            link_cur = link_cur->next;
        }
    }

    int a = 0;
    int b = 0;
    std::cout << "Odleg³oœci od " << g.nodes[start_i].name << "\n";
    for (int i = 0; i < nodes; i++)
    {
        if (i == start_i) continue;
        std::cout << "\tDo " << g.nodes[i].name << " : " << dist_arr[i] << "\n";
        //if (prev_arr[i] >= 0) std::cout << " ostatni stop w " << g.nodes[prev_arr[i]].name;
        std::cout << "\t\t";
        //a = i;
        //while (prev_arr[a] >= 0) {
        //    std::cout << " -> " << g.nodes[prev_arr[a]].name;
        //    a = prev_arr[a];
        //}
        rec_read_prev(g, prev_arr, i);

        std::cout << "\n";
    }
    std::cout << "Szukano do" << g.nodes[end_i].name << " i znaleziono " << dist_arr[end_i];



    delete[] dist_arr;
    delete[] vis_arr;
    delete[] prev_arr;
}

void my_dijkstra3(Graph& g, int start_city_node, int end_city_node, int mode)
{
    int nodes = g.nodes_n;


    int* dist_arr = new int[nodes];
    bool* vis_arr = new bool[nodes];
    int* prev_arr = new int[nodes];

    for (int i = 0; i < nodes; i++)
    {
        dist_arr[i] = INT_MAX;
        prev_arr[i] = -1;
        vis_arr[i] = false;
    }

    int start_i = start_city_node;
    int end_i = end_city_node;

    /*int start_i = 6;
    int end_i = 4;*/

    dist_arr[start_i] = 0;


    int k = 0;
    int tmp_dist = 0;
    int tmp_end = 0;
    int visited = 0;

    List2d<Link>* link_cur = g.nodes[k].links.next;

    int minv = 0;
    int mini = 0;

    while (visited < nodes)
    {
        minv = INT_MAX;
        for (int i = 0; i < nodes; i++)
        {
            if (vis_arr[i] == false && dist_arr[i] <= minv)
                minv = dist_arr[i];
        }
        for (int i = 0; i < nodes; i++)
        {
            if (vis_arr[i] == false &&  dist_arr[i] == minv)
            {
                mini = i;
                break;
            }
        }
        k = mini;

        if (vis_arr[k] == false)
        {
            vis_arr[k] = true;
            visited++;
        }

        link_cur = g.nodes[k].links.next;
        while (link_cur != nullptr)
        {
            tmp_end = link_cur->cont->end_node->arr_index;

            if (vis_arr[tmp_end] == false)
            {

                //tmp_dist = dist_arr[k] + link_cur->cont->length;
                if (link_cur->cont->special)
                {
                    if (tmp_end != end_i)
                        tmp_dist = dist_arr[k] + link_cur->cont->length ;    //za odwiedzenia miasta
                    else
                        tmp_dist = dist_arr[k] + link_cur->cont->length;
                } else
                    tmp_dist = dist_arr[k] + link_cur->cont->length + 1;

                if (tmp_dist < dist_arr[tmp_end])
                {
                    dist_arr[tmp_end] = tmp_dist;
                    prev_arr[tmp_end] = k;
                }
            }
            link_cur = link_cur->next;
        }
    }

    //int a = 0;
    //int b = 0;
    //std::cout << "Odleg³oœci od " << g.nodes[start_i].name << "\n";
    //for (int i = 0; i < nodes; i++)
    //{
    //    if (i == start_i) continue;
    //    std::cout << "\tDo " << g.nodes[i].name << " : " << dist_arr[i] << "\n";
    //    //if (prev_arr[i] >= 0) std::cout << " ostatni stop w " << g.nodes[prev_arr[i]].name;
    //    std::cout << "\t\t";
    //    //a = i;
    //    //while (prev_arr[a] >= 0) {
    //    //    std::cout << " -> " << g.nodes[prev_arr[a]].name;
    //    //    a = prev_arr[a];
    //    //}
    //    rec_read_prev(g, prev_arr, i);

    //    std::cout << "\n";
    //}
    //std::cout << "Szukano do" << g.nodes[end_i].name << " i znaleziono " << dist_arr[end_i];

    if (mode == 0)
    {
        std::cout << dist_arr[end_i] << "\n";
    }
    else if (mode == 1)
    {
        //if (dist_arr[end_i] < 2147483647)
            std::cout << dist_arr[end_i] << " ";
        /*else
        {
            std::cout << "int of " << prev_arr[end_i] << " - " << vis_arr[end_i] << " + ";
            std::cout << dist_arr[g.get_city_node_i_by_name((char*)"FF")];
        }*/

        rec_read_prev(g, prev_arr, end_i);

        std::cout << "\n";
    }



    delete[] dist_arr;
    delete[] vis_arr;
    delete[] prev_arr;
}

#include <queue>
void my_dijkstra4(Graph& g, Node* start_city_node, Node* end_city_node, int mode)
{
    int nodes = g.nodes_n;


    int* dist_arr = new int[nodes];
    bool* vis_arr = new bool[nodes];
    int* prev_arr = new int[nodes];

    for (int i = 0; i < nodes; i++)
    {
        dist_arr[i] = INT_MAX;
        prev_arr[i] = -1;
        vis_arr[i] = false;
    }

    int start_i = start_city_node->arr_index;
    int end_i = end_city_node->arr_index;

    /*int start_i = 6;
    int end_i = 4;*/

    dist_arr[start_i] = 0;


    int k = 0;
    int tmp_dist = 0;
    int tmp_end = 0;
    int visited = 0;

    //List2d<Link>* link_cur = g.nar[k].links.next;
    List2d<Link>*link_cur = nullptr;

    int minv = 0;
    int mini = 0;

    //start_city_node->sort_links();

    while (visited < nodes)
    {
        if (nodes > 10000 && visited > 10000) return;
        minv = INT_MAX;
        for (int i = 0; i < nodes; i++)
        {
            if (vis_arr[i] == false && dist_arr[i] <= minv)
            {
                minv = dist_arr[i];
                mini = i;
            }
        }
        /*
        for (int i = 0; i < nodes; i++)
        {
            if (vis_arr[i] == false && dist_arr[i] == minv)
            {
                mini = i;
                break;
            }
        }*/
        k = mini;
        if (k == end_i) break;

        if (vis_arr[k] == false)
        {
            vis_arr[k] = true;
            visited++;
        }

        link_cur = g.nar[k]->links.next;
        while (link_cur != nullptr)
        {
            tmp_end = link_cur->cont->end_node->arr_index;

            if (vis_arr[tmp_end] == false)
            {

                //tmp_dist = dist_arr[k] + link_cur->cont->length;
                if (link_cur->cont->special)
                {
                    if (tmp_end != end_i)
                        tmp_dist = dist_arr[k] + link_cur->cont->length;    //za odwiedzenia miasta
                    else
                        tmp_dist = dist_arr[k] + link_cur->cont->length;
                }
                else
                    tmp_dist = dist_arr[k] + link_cur->cont->length + 1;

                if (tmp_dist < dist_arr[tmp_end])
                {
                    dist_arr[tmp_end] = tmp_dist;
                    prev_arr[tmp_end] = k;
                }
            }
            link_cur = link_cur->next;
        }
    }

    //int a = 0;
    //int b = 0;
    //std::cout << "Odleg³oœci od " << g.nar[start_i].name << "\n";
    //for (int i = 0; i < nodes; i++)
    //{
    //    if (i == start_i) continue;
    //    std::cout << "\tDo " << g.nar[i].name << " : " << dist_arr[i] << "\n";
    //    //if (prev_arr[i] >= 0) std::cout << " ostatni stop w " << g.nar[prev_arr[i]].name;
    //    std::cout << "\t\t";
    //    //a = i;
    //    //while (prev_arr[a] >= 0) {
    //    //    std::cout << " -> " << g.nar[prev_arr[a]].name;
    //    //    a = prev_arr[a];
    //    //}
    //    rec_read_prev(g, prev_arr, i);

    //    std::cout << "\n";
    //}
    //std::cout << "Szukano do" << g.nar[end_i].name << " i znaleziono " << dist_arr[end_i];

    if (mode == 0)
    {
        std::cout << dist_arr[end_i] << "\n";
    }
    else if (mode == 1)
    {
        //if (dist_arr[end_i] < 2147483647)
        std::cout << dist_arr[end_i] << " ";
        /*else
        {
            std::cout << "int of " << prev_arr[end_i] << " - " << vis_arr[end_i] << " + ";
            std::cout << dist_arr[g.get_city_node_i_by_name((char*)"FF")];
        }*/

        if (g.nodes_n < 10000) rec_read_prev(g, prev_arr, end_i);
        else {
            int p = prev_arr[end_i];
            List2dRoot<int> rec;
            while (prev_arr[p] >= 0)
            {
                //std::cout << g.nar[prev_arr[p]]->name << " ";
                rec.add_at_start(new int(p));
                p = prev_arr[p];
            }
            List2d<int>* c = rec.start;
            while (c != nullptr)
            {
                if (*(c->cont) >= 0)
                    std::cout << g.nar[prev_arr[*(c->cont)]]->name << " ";
                c = c->next;
            }
            rec.delete_list();
        }

        std::cout << "\n";
    }



    delete[] dist_arr;
    delete[] vis_arr;
    delete[] prev_arr;
}


void rec_read_prev(Graph& g, int* prev_arr, int i) {
    if (prev_arr[prev_arr[i]] < 0) return;

    if (prev_arr[i] >= 0) {
        rec_read_prev(g, prev_arr, prev_arr[i]);
        std::cout  << g.nar[prev_arr[i]]->name << " ";
    }
}

int get_length_of_road_to_node(List2d<Node>* start_city_node, List2d<Node>* end_city_node)
{
	List2d<Link>* linknode = start_city_node->cont->links.next;
	while (linknode != nullptr)
	{
		if (linknode->cont->end_node == end_city_node->cont) 
			return linknode->cont->length;
		linknode = linknode->next;
	}
	return 0;
}

bool node_was_visited(Node* node, Dijkstra_wrapper* t, int tsize)
{
	for (int i = 0; i < tsize; i++)
	{
		if (t[i].lnode->cont == node) return true;
	}
	return false;
}

int get_dw(Node* node, int tsize, Dijkstra_wrapper* t)
{
    for (int i = 0; i < tsize; i++)
    {
        if (t[i].lnode->cont == node) 
            return i;
    }
    return -1;
}

int get_arr_i_of_node(Node* node, Graph &g)
{
    for (int i = 0; i < g.nodes_n; i++)
    {
        if (g.nods.cont == node) return i;
    }
    return -1;  //err   
}

List2d<Link>** sort_links(List2d<Link>* root)
{
    int len = root->root_get_lenght() - 1;
    List2d<Link>** arr = new List2d<Link>*[len];
    List2d<Link>* tmp = nullptr;
    

    int i, j;
    bool swapped;
    for (i = 0; i < len - 1; i++)
    {
        swapped = false;
        for (j = 0; j < len - i - 1; j++)
        {
            if (arr[j]->cont->length > arr[j + 1]->cont->length)
            {
                tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;

                swapped = true;
            }
        }
    
        if (swapped == false)
            break;
    }

    return arr;
}



// Adds an edge to an undirected graph
void addEdge(struct Graph_out* graph, int src,
    int dest, int weight)
{
    // Add an edge from src to dest. 
    // A new node is added to the adjacency
    // list of src.  The node is
    // added at the beginning
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since graph is undirected,
    // add an edge from dest to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}



// A utility function to create a
// new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int dist)
{
    struct MinHeapNode* minHeapNode =(struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =(struct MinHeap*)malloc(sizeof(struct MinHeap));

    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =(struct MinHeapNode**)malloc(capacity *sizeof(struct MinHeapNode*));

    return minHeap;
}

// A utility function to swap two
// nodes of min heap.
// Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// A standard function to
// heapify at given idx
// This function also updates
// position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist <
        minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist <
        minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        MinHeapNode* smallestNode =
            minHeap->array[smallest];
        MinHeapNode* idxNode =
            minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest],
            &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// A utility function to check if
// the given minHeap is empty or not
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}

// Standard function to extract
// minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];

    // Replace root node with last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update position of last node
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Function to decreasekey dist value
// of a given vertex v. This function
// uses pos[] of min heap to get the
// current index of node in min heap
void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];

    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;

    // Travel up while the complete
    // tree is not heapified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist <
        minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] =
            (i - 1) / 2;
        minHeap->pos[minHeap->array[
            (i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],
            &minHeap->array[(i - 1) / 2]);

        // move to parent index
        i = (i - 1) / 2;
    }
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(struct MinHeap* minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}

// A utility function used to print the solution
void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// The main function that calculates
// distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra(struct Graph_out* graph, int src)
{

    // Get the number of vertices in graph
    int V = graph->V;

    // dist values used to pick
    // minimum weight edge in cut
    int* dist = new int[V];

    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);

    // Initialize min heap with all
    // vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v,dist[v]);
        minHeap->pos[v] = v;
    }

    // Make dist value of src vertex
    // as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    // Initially size of min heap is equal to V
    minHeap->size = V;

    // In the following loop,
    // min heap contains all nodes
    // whose shortest distance
    // is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with
        // minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);

        // Store the extracted vertex number
        int u = minHeapNode->v;

        // Traverse through all adjacent
        // vertices of u (the extracted
        // vertex) and update
        // their distance values
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;

            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its
            // previously calculated distance
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;

                // update distance
                // value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    // print the calculated shortest distances
    printArr(dist, V);
}


// A utility function to create
// a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));

    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;

    return newNode;
}

// A utility function that creates
// a graph of V vertices
struct Graph_out* createGraph(int V)
{
    struct Graph_out* graph = (struct Graph_out*)malloc(sizeof(struct Graph_out));
    graph->V = V;

    // Create an array of adjacency lists. 
    // Size of array will be V
    graph->array = (struct AdjList*)
        malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list
    // as empty by making head as NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}
