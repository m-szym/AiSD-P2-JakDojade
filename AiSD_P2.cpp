#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>


#include "other.h"
#include "data_reading_and_manip.h"




int main()
{
    MapData m;
    m.load();

    Graph g(m.cities);

    load_cities(m, g);

    find_first_level_connections(m, g);

    read_flights(g);
    

    //int n = 0;
    //List2d<Node>* cur = nullptr;
    //List2d<Link>* l = nullptr;
    //for (int i = 0; i < g.nodes_hashtable->array_size; i++)
    //{
    //    if (g.nodes_hashtable->harray[i] != nullptr)
    //    {
    //        std::cout << n << "-ta niepusta";
    //        n++;
    //        cur = g.nodes_hashtable->harray[i];
    //        int c = 0;
    //        while (cur != nullptr)
    //        {
    //            std::cout << "\n\t " << cur->cont->name << " [" << cur->cont->arr_index << "]";

    //            l = cur->cont->links.next;
    //            while (l != nullptr)
    //            {
    //                std::cout << "\n\t\t " << "from" << l->cont->start_node->name << " to " << l->cont->end_node->name << " in " << l->cont->length;

    //                l = l->next;
    //            }


    //            cur = cur->next;
    //            c++;
    //        }
    //        std::cout << "\n razem " << c << "\n";
    //    }
    //}

    //return 0;
    
    int q = 0;
    std::cin >> q;
    while (q >= 0)
    {
        do_command(g);
        q--;
    }

}













