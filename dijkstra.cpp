#include "dijkstra.h"




bool operator<(minh_node n1, minh_node n2)
{
    if (n1.distance <= n2.distance)
        return true;
    else 
        return false;
}



void enq(minh_node pr[], int& size, int nar_i, int dist)
{
    size++;

    //pr[size].set(nar_i, dist);
    pr[size].distance = dist;
    pr[size].nar_index = nar_i;
}
int top(minh_node pr[], int size)
{
    int min_dist = INT_MAX;
    int ind = -1;

    for (int i = 0; i <= size; i++) 
    {
        if (min_dist > pr[i].distance) 
        {
            min_dist = pr[i].distance;
            ind = i;
        }
    }


    return ind;
}
void deq(minh_node pr[], int& size)
{
    int ind = top(pr, size);

    for (int i = ind; i < size; i++) 
    {
        pr[i] = pr[i + 1];
    }

    size--;
}




void my_dijkstra5(Graph& g, Node* start_city_node, Node* end_city_node, int mode)
{
    int nodes = g.nodes_n;


    int* dist_arr = new int[nodes];
    bool* vis_arr = new bool[nodes];
    int* prev_arr = new int[nodes];

    minh_node* pr = new minh_node[2*nodes];
    int pr_size = -1;

    for (int i = 0; i < 2*nodes; i++)
    {
        if (i < nodes)
        {
            dist_arr[i] = INT_MAX;
            prev_arr[i] = -1;
            vis_arr[i] = false;
        }

        pr[i].set(-1, INT_MAX);
    }

    int start_i = start_city_node->arr_index;
    int end_i = end_city_node->arr_index;

    dist_arr[start_i] = 0;


    int k = 0;
    int tmp_dist = 0;
    int tmp_end = 0;
    int visited = 0;


    List2d<Link>* link_cur = nullptr;

    int minv = 0;
    int mini = 0;


    enq(pr, pr_size, start_i, 0);

    while(pr_size >= 0)
    {
        minv = INT_MAX;

        int t = top(pr, pr_size);
        k = pr[t].nar_index;
        deq(pr, pr_size);

        if (k == end_i) break;

        if (vis_arr[k] == false)
        {
            vis_arr[k] = true;
            visited++;
        }

        link_cur = g.nodes_array[k]->links.next;
        while (link_cur != nullptr)
        {
            tmp_end = link_cur->cont->end_node->arr_index;

            if (vis_arr[tmp_end] == false)
            {
                if (link_cur->cont->special)
                     tmp_dist = dist_arr[k] + link_cur->cont->length;    
                else
                    tmp_dist = dist_arr[k] + link_cur->cont->length + 1;
 

                if (tmp_dist < dist_arr[tmp_end])
                {
                    dist_arr[tmp_end] = tmp_dist;
                    prev_arr[tmp_end] = k;

                    enq(pr, pr_size, tmp_end, tmp_dist);
                }

            }
            link_cur = link_cur->next;
        }
    }


    if (mode == 0)
    {
        std::cout << dist_arr[end_i] << "\n";
    }
    else if (mode == 1)
    {

        std::cout << dist_arr[end_i] << " ";

        if (prev_arr[end_i] >= 0)
        {
            int p = prev_arr[end_i];

            List2dRoot<int> rec;
            while (prev_arr[p] >= 0)
            {
                rec.add_at_start(new int(p));
                p = prev_arr[p];
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



    delete[] dist_arr;
    delete[] vis_arr;
    delete[] prev_arr;
    //delete[] minh;
    //delete[] pr;
}


