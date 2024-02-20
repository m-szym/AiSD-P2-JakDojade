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
    
    
    int q = 0;
    std::cin >> q;
    while (q >= 0)
    {
        do_command(g);
        q--;
    
}

}