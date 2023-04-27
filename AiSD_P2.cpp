#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include <cstdlib>
#include <cstring>
#include <cstdio>

#include "other.h"
#include <stack>
#include <queue>
#include "List2d.h"


struct XY
{
    int x;
    int y;
    int path;
    XY(int yi=0, int xi=0, int pathi=0) {
        x = xi;
        y = yi;
        path = pathi;
    }
};

bool** rvis = nullptr;
int** rvis2 = nullptr;
int** vist = nullptr;
List2d<XY> stack;
List2dRoot<XY> Q;
std::stack<XY*> sta;
std::queue<XY*> que;

void main_dfs(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction);
void main_bfs(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction);
void main_bfs2(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length);
void main_bfs20(char** map, Node*** nmap, int width, int height, int ooi, int ooj, Node* o_start_node, int path_length, XY** x);


int main()
{
    int width = 0;
    int height = 0;

    //tworzenie mapy
    std::cin >> width >> height;
    XY** x = new XY * [height];
    char** map = new char*[height];

    for (int i = 0; i < height; i++)
    {
        map[i] = new char[width];
        x[i] = new XY[width];
    }

    int cities = 0;
    
    //wczytywanie mapy
    char c = ' ';
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cin >> map[i][j];
            //c = getchar();
            //while (c >= ' ')
            //{
            //    c = getchar();
            //}
        
            //map[i][j] = c;
            //else
            //    --j;
            //std::cout << map[i][j] << " ";

            if (map[i][j] == CITY_SYMBOL) cities++; //zlicznie miast
        }
        //std::cout << "\n";
    }


    //std::cout << "\n\n";
    //for (int i = 0; i < height; i++)
    //{
    //    for (int j = 0; j < width; j++)
    //    {
    //        //std::cin >> map[i][j];
    //        //map[i][j] = getchar();
    //        std::cout << map[i][j];

    //        //if (map[i][j] == CITY_SYMBOL) cities++; //zlicznie miast
    //    }
    //    std::cout << "\n";
    //}

    //tworzenie grafu
    Graph g(cities);

    rvis2 = new int* [height];
    rvis = new bool* [height];
    //pomocnicza tablica
    Node*** nmap = new Node** [height];
    vist = new int*[height];
    for (int i = 0; i < height; i++)
    {
        rvis2[i] = new int[width];
        nmap[i] = new Node*[width];
        rvis[i] = new bool[width];
        vist[i] = new int[width];
        for (int j = 0; j < width; j++)
        {
            rvis2[i][j] = -1;
            nmap[i][j] = nullptr;
            rvis[i][j] = false;
            vist[i][j] = 0;
        }
    }


    //wypełnianie grafu - nazwy miast
    //rzutowanie miast na mapę pomoczniczą
    int k = 0;
    char* tmp_s = nullptr;
    int stop_i = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] != ROAD_SYMBOL && map[i][j] != EMPTY_SYMBOL && map[i][j] != CITY_SYMBOL)
            {
                if (stop_i == 0)
                {
                    tmp_s = read_name(map, width, height, i, j);
                    if (tmp_s != nullptr)
                    {
                        stop_i = strlen(tmp_s) - 1;

                        g.nodes[k].set_name(tmp_s);     //zapisuję nazwę miasta
                        g.nodes[k].arr_index = k;

                        g.nods.add_after(new Node);
                        g.nods.next->cont->set_name(tmp_s);
                        
                        //nmap[i][j] = &(g.nodes[k]);     //zapisuję adres do węzła w grafie odpowiadającego miastu na tej pozycji na mapie pomoczniczej
                        //nmap[i][j] = g.nods.next->cont;
                        // 
                        //register_star(map, nmap, width, height, i, j, g.nods.next->cont, strlen(tmp_s));
                        register_star(map, nmap, width, height, i, j, &(g.nodes[k]), strlen(tmp_s));    //powinno wczytać do tablicowych
                        
                        delete[] tmp_s;
                    }
                    k++;

                }
                else 
                    stop_i--;
            }
        }
    }
    //delete[] tmp_s;






    //znajdywanie i zapisywanie połączeń miedzy węzłami do grafu
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] == CITY_SYMBOL)
            {
                if (nmap[i][j] != nullptr)  //inaczej coś jest nie tak
                {
                    //read_all_paths(map, nmap, width, height, i, j, nmap[i][j]);
                    //main_dfs(map, nmap, width, height, i, j, nmap[i][j], 0, 0);
                    //main_bfs(map, nmap, width, height, i, j, nmap[i][j], 0, 0);
                    //main_bfs2(map, nmap, width, height, i, j, nmap[i][j], 0);
                    main_bfs20(map, nmap, width, height, i, j, nmap[i][j], 0, x);
                    //if (nmap[i][j]->arr_index == 0) return 0;
                }
            }
        }
    }

    //read_all_paths(map, nmap, width, height, 0, 0, nmap[0][0]);
    //main_dfs(map, nmap, width, height, 0, 0, nmap[0][0], 0, 0);

   // std::cout << g.nodes_n;

    //dealokacja pomoczniczej mapy
    for (int i = 0; i < height; i++)
    {
        delete[] nmap[i];
    }
    delete[] nmap;

    ////samoloty
    int flights = 0;
    std::cin >> flights;

    flights++;
    while (flights > 0)
    {
        read_flight(g);
        flights--;
    }




    


    //dealokacja mapy
    for (int i = 0; i < height; i++)
    {
        delete[] map[i];
    }
    delete[] map;

    //usuwanie grafu
    //sam się usuwa
    //g.print_graph();
    
    //g.print_nodes();

    //std::cout << "\n\n";
    //for (int i = 0; i < 80; i++)
    //{
    //    std::cout << "#";
    //}
    //std::cout << "\n\n";

    /*
    my_dijkstra2(g, g.get_city_node_i_by_name((char*)"KRAKOW"), g.get_city_node_i_by_name((char*)"GDANSK") );

    std::cout << "\n\n";
    for (int i = 0; i < 80; i++)
    {
        std::cout << "#";
    }
    std::cout << "\n\n";*/

    int q = 0;
    std::cin >> q;

    while (q + 1 > 0)
    {
        do_command(g);
        q--;
    }
     
    //g.nodes[g.get_city_node_i_by_name((char*)"AAA")].print_node();
}


//int count_road_neighbours(char** map, int oi, int oj, int width, int height)
//{
//    int n = 0;
//
//    if (out_of_map(width, height, oi, oj, DIR_UP) == false && map[oi - 1][oj] == ROAD_SYMBOL)
//        n++;
//
//    if (out_of_map(width, height, oi, oj, DIR_DOWN) == false && map[oi + 1][oj] == ROAD_SYMBOL)
//        n++;
//
//    if (out_of_map(width, height, oi, oj, DIR_LEFT) == false && map[oi][oj - 1] == ROAD_SYMBOL)
//        n++;
//
//    if (out_of_map(width, height, oi, oj, DIR_RIGHT) == false && map[oi][oj + 1] == ROAD_SYMBOL)
//        n++;
//
//    return n;
//}
//
////inters - skrzyżowania i miasta - zliczyć przy wczytywaniu mapy
//void sigismundD(char** map, int width, int height, Node*** nmap, int inters)
//{
//    Graph tg(inters);
//
//    for (int i = 0; i < height; i++)
//    {
//        for (int j = 0; j < width; j++)
//        {
//
//        }
//    }
//}
//
//void crawler(char** map, int width, int height, Node*** nmap, int oi, int oj, char parent_dir, int path_length, int k, Graph& g, bool** nodes)
//{
//    if (parent_dir != DIR_UP && out_of_map(width, height, oi, oj, DIR_UP) == false )
//    {
//        if (map[oi - 1][oj] == ROAD_SYMBOL)
//        {
//            //rvis[oi - 1][oj] = true;
//            //read_path(map, nmap, width, height, oi - 1, oj, o_start_node, path_length + 1, DIR_DOWN);
//            stack.add_after(new XY(oi - 1, oj, path_length + 1));
//            //rvis[oi - 1][oj] = false;
//        }
//        else if (map[oi - 1][oj] == CITY_SYMBOL || count_road_neighbours(map, oi - 1, oj, width, height) > 2)
//        {
//            if (nodes[oi - 1][oj] == false)
//            {
//                g.nodes[k].arr_index = k;
//                g.nodes[k].links.add_after(new Link())
//                nodes[oi - 1][oj] = true;
//                k++;
//            }
//
//
//            return;
//        }
//    }
//
//    if (out_of_map(width, height, oi, oj, DIR_DOWN) == false && rvis[oi + 1][oj] == false)
//    {
//
//        if (map[oi + 1][oj] == ROAD_SYMBOL)
//        {
//            //rvis[oi + 1][oj] = true;
//            //read_path(map, nmap, width, height, oi + 1, oj, o_start_node, path_length + 1, DIR_UP);
//            stack.add_after(new XY(oi + 1, oj, path_length + 1));
//            //rvis[oi + 1][oj] = false;
//        }
//        else if (map[oi + 1][oj] == CITY_SYMBOL)
//        {
//            if (nmap[oi + 1][oj] != nullptr)    //w innym wypadku jakiś błąd
//            {
//                o_start_node->links.add_after(new Link(path_length, o_start_node, nmap[oi + 1][oj]));
//                //return;
//
//            }
//        }
//    }
//
//    if (out_of_map(width, height, oi, oj, DIR_LEFT) == false && rvis[oi][oj - 1] == false)
//    {
//        if (map[oi][oj - 1] == ROAD_SYMBOL)
//        {
//            //rvis[oi][oj - 1] = true;
//            //read_path(map, nmap, width, height, oi, oj - 1, o_start_node, path_length + 1, DIR_RIGHT);
//            //rvis[oi][oj - 1] = false;
//            stack.add_after(new XY(oi, oj - 1, path_length + 1));
//        }
//        else if (map[oi][oj - 1] == CITY_SYMBOL)
//        {
//            if (nmap[oi][oj - 1] != nullptr)    //w innym wypadku jakiś błąd
//            {
//                o_start_node->links.add_after(new Link(path_length, o_start_node, nmap[oi][oj - 1]));
//                //return;
//
//            }
//        }
//    }
//
//    if (out_of_map(width, height, oi, oj, DIR_RIGHT) == false && rvis[oi][oj + 1] == false)
//    {
//        if (map[oi][oj + 1] == ROAD_SYMBOL)
//        {
//            //rvis[oi][oj + 1] = true;
//            //read_path(map, nmap, width, height, oi, oj + 1, o_start_node, path_length + 1, DIR_LEFT);
//            stack.add_after(new XY(oi, oj + 1, path_length + 1));
//            //rvis[oi][oj + 1] = false;
//        }
//        else if (map[oi][oj + 1] == CITY_SYMBOL)
//        {
//            if (nmap[oi][oj + 1] != nullptr)    //w innym wypadku jakiś błąd
//            {
//                o_start_node->links.add_after(new Link(path_length, o_start_node, nmap[oi][oj + 1]));
//                //return;
//                //for (int i = 0; i < height; i++)
//                //{
//                //    for (int j = 0; j < width; j++)
//                //    {
//                //        if (rvis[i][j] == true) rvis[i][j] = false;
//                //    }
//                //}
//            }
//        }
//    }
//
//    //rvis[oi][oj] = false;
//}



void bfs(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    rvis[oi][oj] = true;


    if (out_of_map(width, height, oi, oj, DIR_UP) == false && rvis[oi - 1][oj] == false)
    {

        if (map[oi - 1][oj] == ROAD_SYMBOL)
        {

            Q.add_at_end(new XY(oi - 1, oj, path_length + 1));

        }
        else if (map[oi - 1][oj] == CITY_SYMBOL)
        {
            if (nmap[oi - 1][oj] != nullptr)    //w innym wypadku jakiś błąd
            {
                o_start_node->links.add_after(new Link(path_length + 1, o_start_node, nmap[oi - 1][oj]));
                //std::cout << "Found\n";

            }
        }
    }

    if (out_of_map(width, height, oi, oj, DIR_DOWN) == false && rvis[oi + 1][oj] == false)
    {

        if (map[oi + 1][oj] == ROAD_SYMBOL)
        {

            Q.add_at_end(new XY(oi + 1, oj, path_length + 1));

        }
        else if (map[oi + 1][oj] == CITY_SYMBOL)
        {
            if (nmap[oi + 1][oj] != nullptr)    //w innym wypadku jakiś błąd
            {
                o_start_node->links.add_after(new Link(path_length + 1, o_start_node, nmap[oi + 1][oj]));
                //return;
                //std::cout << "Found\n";
            }
        }
    }

    if (out_of_map(width, height, oi, oj, DIR_LEFT) == false && rvis[oi][oj - 1] == false)
    {
        if (map[oi][oj - 1] == ROAD_SYMBOL)
        {

            Q.add_at_end(new XY(oi, oj - 1, path_length + 1));
        }
        else if (map[oi][oj - 1] == CITY_SYMBOL)
        {
            if (nmap[oi][oj - 1] != nullptr)    
            {
                o_start_node->links.add_after(new Link(path_length + 1, o_start_node, nmap[oi][oj - 1]));
                //std::cout << "Found\n";

            }
        }
    }

    if (out_of_map(width, height, oi, oj, DIR_RIGHT) == false && rvis[oi][oj + 1] == false)
    {
        if (map[oi][oj + 1] == ROAD_SYMBOL)
        {

            Q.add_at_end(new XY(oi, oj + 1, path_length + 1));

        }
        else if (map[oi][oj + 1] == CITY_SYMBOL)
        {
            if (nmap[oi][oj + 1] != nullptr)    //w innym wypadku jakiś błąd
            {
                o_start_node->links.add_after(new Link(path_length + 1, o_start_node, nmap[oi][oj + 1]));
                //std::cout << "Found\n";
            }
        }
    }


}


void main_bfs(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    XY* tmp = nullptr;
    int path = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    bfs(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (Q.root->next != nullptr)
    {
        tmp = Q.root->next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            Q.root->next->remove_self();

            bfs(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    Q.delete_list();
}


void bfs2(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length)
{
    rvis[oi][oj] = true;


    if (out_of_map(width, height, oi, oj, DIR_UP) == false && rvis[oi - 1][oj] == false)
    {

        if (map[oi - 1][oj] == ROAD_SYMBOL)
        {

            //Q.add_at_end(new XY(oi - 1, oj, path_length + 1));
            que.push(new XY(oi - 1, oj, path_length + 1));

        }
        else if (map[oi - 1][oj] == CITY_SYMBOL)
        {
            if (nmap[oi - 1][oj] != nullptr)    //w innym wypadku jakiś błąd
            {
                o_start_node->links.add_after(new Link(path_length , o_start_node, nmap[oi - 1][oj]));
                //std::cout << "Found\n";

            }
        }
    }

    if (out_of_map(width, height, oi, oj, DIR_DOWN) == false && rvis[oi + 1][oj] == false)
    {

        if (map[oi + 1][oj] == ROAD_SYMBOL)
        {

            //Q.add_at_end(new XY(oi + 1, oj, path_length + 1));
            que.push(new XY(oi + 1, oj, path_length + 1));

        }
        else if (map[oi + 1][oj] == CITY_SYMBOL)
        {
            if (nmap[oi + 1][oj] != nullptr)    //w innym wypadku jakiś błąd
            {
                o_start_node->links.add_after(new Link(path_length , o_start_node, nmap[oi + 1][oj]));
                //return;
                //std::cout << "Found\n";
            }
        }
    }

    if (out_of_map(width, height, oi, oj, DIR_LEFT) == false && rvis[oi][oj - 1] == false)
    {
        if (map[oi][oj - 1] == ROAD_SYMBOL)
        {

            //Q.add_at_end(new XY(oi, oj - 1, path_length + 1));
            que.push(new XY(oi, oj - 1, path_length + 1));
        }
        else if (map[oi][oj - 1] == CITY_SYMBOL)
        {
            if (nmap[oi][oj - 1] != nullptr)
            {
                o_start_node->links.add_after(new Link(path_length , o_start_node, nmap[oi][oj - 1]));
                //std::cout << "Found\n";

            }
        }
    }

    if (out_of_map(width, height, oi, oj, DIR_RIGHT) == false && rvis[oi][oj + 1] == false)
    {
        if (map[oi][oj + 1] == ROAD_SYMBOL)
        {

            //Q.add_at_end(new XY(oi, oj + 1, path_length + 1));
            que.push(new XY(oi, oj + 1, path_length + 1));

        }
        else if (map[oi][oj + 1] == CITY_SYMBOL)
        {
            if (nmap[oi][oj + 1] != nullptr)    //w innym wypadku jakiś błąd
            {
                o_start_node->links.add_after(new Link(path_length , o_start_node, nmap[oi][oj + 1]));
                //std::cout << "Found\n";
            }
        }
    }


}

void main_bfs2(char** map, Node*** nmap, int width, int height, int ooi, int ooj, Node* o_start_node, int path_length)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }

    //XY* xy = nullptr;
    int oi = 0;
    int oj = 0;
    int l = 0;
    //que.push(new XY(ooi, ooj, 0));
    Q.add_at_end(new XY(ooi, ooj, 0));
    //while (!que.empty()) 
    while(Q.start != nullptr)
    {
        //xy = que.front();
        //bfs2(map, nmap, width, height, xy->y, xy->x, o_start_node, xy->path);
        
        //oi = que.front()->y;
        //oj = que.front()->x;
        //l = que.front()->path;
        //que.pop();

        oi = Q.start->cont->y;
        oj = Q.start->cont->x;
        l = Q.start->cont->path;
        Q.remove_at_start();


        //std::cout << "x: " << oj << ", y: " << oi << " - l: " << l << " = t: " << vist[oi][oj] << " << ";
        //if (rvis[oi][oj] == true) std::cout << "1\n";
        //else std::cout << "0\n";
        //rvis[oi][oj] = true;
        //vist[oi][oj] = vist[oi][oj] + 1;



        if (oi-1 >= 0)
        {

            if (map[oi - 1][oj] == ROAD_SYMBOL && rvis[oi - 1][oj] == false)
            {
                rvis[oi - 1][oj] = true;
                Q.add_at_end(new XY(oi - 1, oj, l + 1));
                //que.push(new XY(oi - 1, oj, l + 1));

            }
            else if (map[oi - 1][oj] == CITY_SYMBOL)
            {
                if (nmap[oi - 1][oj] != nullptr)    //w innym wypadku jakiś błąd
                {
                    o_start_node->links.add_after(new Link(l, o_start_node, nmap[oi - 1][oj]));
                    nmap[oi - 1][oj]->links.add_after(new Link(l, nmap[oi - 1][oj], o_start_node));
                    //std::cout << "Found\n";

                }
            }
        }

        if (oi+1<height )
        {

            if (map[oi + 1][oj] == ROAD_SYMBOL && rvis[oi + 1][oj] == false)
            {
                rvis[oi + 1][oj] = true;
                Q.add_at_end(new XY(oi + 1, oj, l + 1));
                //que.push(new XY(oi + 1, oj, l + 1));

            }
            else if (map[oi + 1][oj] == CITY_SYMBOL)
            {
                if (nmap[oi + 1][oj] != nullptr)    //w innym wypadku jakiś błąd
                {
                    o_start_node->links.add_after(new Link(l, o_start_node, nmap[oi + 1][oj]));
                    nmap[oi + 1][oj]->links.add_after(new Link(l, nmap[oi + 1][oj], o_start_node));
                    //return;
                    //std::cout << "Found\n";
                }
            }
        }

        if (oj-1>=0)
        {
            if (map[oi][oj - 1] == ROAD_SYMBOL && rvis[oi][oj - 1] == false)
            {
                rvis[oi][oj-1] = true;
                Q.add_at_end(new XY(oi, oj - 1, l + 1));
                //que.push(new XY(oi, oj - 1, l + 1));
            }
            else if (map[oi][oj - 1] == CITY_SYMBOL)
            {
                if (nmap[oi][oj - 1] != nullptr)
                {
                    o_start_node->links.add_after(new Link(l, o_start_node, nmap[oi][oj - 1]));
                    nmap[oi][oj-1]->links.add_after(new Link(l, nmap[oi][oj - 1], o_start_node));
                    //std::cout << "Found\n";

                }
            }
        }

        if (oj+1<width)
        {
            if (map[oi][oj + 1] == ROAD_SYMBOL && rvis[oi][oj + 1] == false)
            {
                rvis[oi][oj+1] = true;
                Q.add_at_end(new XY(oi, oj + 1, l + 1));
                //que.push(new XY(oi, oj + 1, l + 1));

            }
            else if (map[oi][oj + 1] == CITY_SYMBOL)
            {
                if (nmap[oi][oj + 1] != nullptr)    //w innym wypadku jakiś błąd
                {
                    o_start_node->links.add_after(new Link(l, o_start_node, nmap[oi][oj + 1]));
                    nmap[oi][oj + 1]->links.add_after(new Link(l, nmap[oi][oj + 1], o_start_node));
                    //std::cout << "Found\n";
                }
            }
        }

    }
}


void setx(XY** x,int oi, int oj, int i, int j, int path)
{
    x[oi][oj].x = j;
    x[oi][oj].y = i;
    x[oi][oj].path = path;
}

void main_bfs20(char** map, Node*** nmap, int width, int height, int ooi, int ooj, Node* o_start_node, int path_length, XY** x)
{
    //for (int i = 0; i < height; i++)
    //{
    //    for (int j = 0; j < width; j++)
    //    {
    //        if (rvis[i][j] == true) rvis[i][j] = false;
    //    }
    //}
    static int visi = 0;
    

    //XY* xy = nullptr;
    int oi = 0;
    int oj = 0;
    int l = 0;
    //que.push(new XY(ooi, ooj, 0));
    //Q.add_at_end(new XY(ooi, ooj, 0));
    setx(x, 0, 0, ooi, ooj, 0);
    int qCi = 0;
    int qCj = 1;
    int qIi = 0;
    int qIj = 0;

    //while (!que.empty()) 
    //while (Q.start != nullptr)
    while (qCi * width + qCj > qIi * width + qIj)
    {
        //xy = que.front();
        //bfs2(map, nmap, width, height, xy->y, xy->x, o_start_node, xy->path);

        //oi = que.front()->y;
        //oj = que.front()->x;
        //l = que.front()->path;
        //que.pop();

        /*oi = Q.start->cont->y;
        oj = Q.start->cont->x;
        l = Q.start->cont->path;*/
        //Q.remove_at_start();

        oi = x[qIi][qIj].y;
        oj = x[qIi][qIj].x;
        l = x[qIi][qIj].path;
        ++qIj;
        if (qIj == width)
        {
            ++qIi;
            qIj = 0;
        }

        //std::cout << "x: " << oj << ", y: " << oi << " - l: " << l << " = t: " << vist[oi][oj] << " << ";
        //if (rvis[oi][oj] == true) std::cout << "1\n";
        //else std::cout << "0\n";
        //rvis[oi][oj] = true;
        //vist[oi][oj] = vist[oi][oj] + 1;



        if (oi - 1 >= 0)
        {

            //if (map[oi - 1][oj] == ROAD_SYMBOL && rvis[oi - 1][oj] == false)
            if (map[oi - 1][oj] == ROAD_SYMBOL && rvis2[oi - 1][oj] != visi)
            {
                rvis[oi - 1][oj] = true;
                rvis2[oi - 1][oj] = visi;
                //Q.add_at_end(new XY(oi - 1, oj, l + 1));
                setx(x, qCi, qCj, oi - 1, oj, l + 1);
                //std::cout << "enq on:" << qCi << ", " << qCj << " # n: " << oi-1 << ", " << oj << " with l: " << l+1 << std::endl;
                qCj++;
                if (qCj == width)
                {
                    qCi++;
                    qCj = 0;
                }
                vist[oi - 1][oj] = vist[oi - 1][oj] + 1;
                
                //que.push(new XY(oi - 1, oj, l + 1));

            }
            else if (map[oi - 1][oj] == CITY_SYMBOL)
            {
                if (nmap[oi - 1][oj] != nullptr)    //w innym wypadku jakiś błąd
                {
                    o_start_node->links.add_after(new Link(l, o_start_node, nmap[oi - 1][oj]));
                    nmap[oi - 1][oj]->links.add_after(new Link(l, nmap[oi - 1][oj], o_start_node));
                    //std::cout << "Found\n";

                }
            }
        }

        if (oi + 1 < height)
        {

            //if (map[oi + 1][oj] == ROAD_SYMBOL && rvis[oi + 1][oj] == false)
            if (map[oi + 1][oj] == ROAD_SYMBOL && rvis2[oi + 1][oj] != visi)
            {
                rvis[oi + 1][oj] = true;
                rvis2[oi + 1][oj] = visi;
                //Q.add_at_end(new XY(oi + 1, oj, l + 1));
                setx(x, qCi, qCj, oi + 1, oj, l + 1);
               // std::cout << "enq on:" << qCi << ", " << qCj << " # n: " << oi + 1 << ", " << oj << " with l: " << l + 1 << std::endl;
                qCj++;
                if (qCj == width)
                {
                    qCi++;
                    qCj = 0;
                }
                vist[oi + 1][oj] = vist[oi + 1][oj] + 1;
                //que.push(new XY(oi + 1, oj, l + 1));

            }
            else if (map[oi + 1][oj] == CITY_SYMBOL)
            {
                if (nmap[oi + 1][oj] != nullptr)    //w innym wypadku jakiś błąd
                {
                    o_start_node->links.add_after(new Link(l, o_start_node, nmap[oi + 1][oj]));
                    nmap[oi + 1][oj]->links.add_after(new Link(l, nmap[oi + 1][oj], o_start_node));
                    //return;
                    //std::cout << "Found\n";
                }
            }
        }

        if (oj - 1 >= 0)
        {
            //if (map[oi][oj - 1] == ROAD_SYMBOL && rvis[oi][oj - 1] == false)
            if (map[oi][oj - 1] == ROAD_SYMBOL && rvis2[oi][oj - 1] != visi)
            {
                rvis[oi][oj - 1] = true;
                rvis2[oi][oj - 1] = visi;
                //Q.add_at_end(new XY(oi, oj - 1, l + 1));
                //que.push(new XY(oi, oj - 1, l + 1));
                setx(x, qCi, qCj, oi, oj-1, l + 1);
                //std::cout << "enq on:" << qCi << ", " << qCj << " # n: " << oi  << ", " << oj - 1<< " with l: " << l + 1 << std::endl;
                qCj++;
                if (qCj == width)
                {
                    qCi++;
                    qCj = 0;
                }
                vist[oi][oj - 1] = vist[oi][oj - 1] + 1;
            }
            else if (map[oi][oj - 1] == CITY_SYMBOL)
            {
                if (nmap[oi][oj - 1] != nullptr)
                {
                    o_start_node->links.add_after(new Link(l, o_start_node, nmap[oi][oj - 1]));
                    nmap[oi][oj - 1]->links.add_after(new Link(l, nmap[oi][oj - 1], o_start_node));
                    //std::cout << "Found\n";

                }
            }
        }

        if (oj + 1 < width)
        {
            //if (map[oi][oj + 1] == ROAD_SYMBOL && rvis[oi][oj + 1] == false)
            if (map[oi][oj + 1] == ROAD_SYMBOL && rvis2[oi][oj + 1] != visi)
            {
                rvis[oi][oj + 1] = true;
                rvis2[oi][oj + 1] = visi;
                //Q.add_at_end(new XY(oi, oj + 1, l + 1));
                //que.push(new XY(oi, oj + 1, l + 1));
                setx(x, qCi, qCj, oi, oj+1, l + 1);
                //std::cout << "enq on:" << qCi << ", " << qCj << " # n: " << oi  << ", " << oj + 1<< " with l: " << l + 1 << std::endl;
                qCj++;
                if (qCj == width)
                {
                    qCi++;
                    qCj = 0;
                }
                vist[oi][oj + 1] = vist[oi][oj - 1] + 1;
            }
            else if (map[oi][oj + 1] == CITY_SYMBOL)
            {
                if (nmap[oi][oj + 1] != nullptr)    //w innym wypadku jakiś błąd
                {
                    o_start_node->links.add_after(new Link(l, o_start_node, nmap[oi][oj + 1]));
                    nmap[oi][oj + 1]->links.add_after(new Link(l, nmap[oi][oj + 1], o_start_node));
                    //std::cout << "Found\n";
                }
            }
        }

    }

    ++visi;
}



void dfs_r(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    {
        rvis[oi][oj] = true;

        if (out_of_map(width, height, oi, oj, DIR_RIGHT) == false && rvis[oi][oj + 1] == false)
        {
            if (map[oi][oj + 1] == ROAD_SYMBOL)
            {
                //rvis[oi][oj + 1] = true;
                //read_path(map, nmap, width, height, oi, oj + 1, o_start_node, path_length + 1, DIR_LEFT);
                stack.add_after(new XY(oi, oj + 1, path_length + 1));
                //rvis[oi][oj + 1] = false;
            }
            else if (map[oi][oj + 1] == CITY_SYMBOL)
            {
                if (nmap[oi][oj + 1] != nullptr)    //w innym wypadku jakiś błąd
                {
                    o_start_node->links.add_after(new Link(path_length, o_start_node, nmap[oi][oj + 1]));
                    nmap[oi][oj + 1]->links.add_after(new Link(path_length, nmap[oi][oj + 1], o_start_node));
                }
            }
        }

    }
}
void dfs_l(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    {
        rvis[oi][oj] = true;

        if (out_of_map(width, height, oi, oj, DIR_LEFT) == false && rvis[oi][oj - 1] == false)
        {
            if (map[oi][oj - 1] == ROAD_SYMBOL)
            {
                //rvis[oi][oj + 1] = true;
                //read_path(map, nmap, width, height, oi, oj + 1, o_start_node, path_length + 1, DIR_LEFT);
                stack.add_after(new XY(oi, oj - 1, path_length + 1));
                //rvis[oi][oj + 1] = false;
            }
            else if (map[oi][oj - 1] == CITY_SYMBOL)
            {
                if (nmap[oi][oj - 1] != nullptr)    //w innym wypadku jakiś błąd
                {
                    o_start_node->links.add_after(new Link(path_length, o_start_node, nmap[oi][oj - 1]));
                    nmap[oi][oj - 1]->links.add_after(new Link(path_length, nmap[oi][oj - 1], o_start_node));
                }
            }
        }

    }
}
void dfs_d(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    {
        rvis[oi][oj] = true;

        if (out_of_map(width, height, oi, oj, DIR_DOWN) == false && rvis[oi + 1][oj] == false)
        {
            if (map[oi + 1][oj] == ROAD_SYMBOL)
            {
                //rvis[oi][oj + 1] = true;
                //read_path(map, nmap, width, height, oi, oj + 1, o_start_node, path_length + 1, DIR_LEFT);
                stack.add_after(new XY(oi + 1, oj, path_length + 1));
                //rvis[oi][oj + 1] = false;
            }
            else if (map[oi + 1][oj] == CITY_SYMBOL)
            {
                if (nmap[oi + 1][oj] != nullptr)    //w innym wypadku jakiś błąd
                {
                    o_start_node->links.add_after(new Link(path_length, o_start_node, nmap[oi + 1][oj]));
                    nmap[oi + 1][oj]->links.add_after(new Link(path_length, nmap[oi + 1][oj], o_start_node));
                }
            }
        }

    }
}
void dfs_u(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    {
        rvis[oi][oj] = true;

        if (out_of_map(width, height, oi, oj, DIR_UP) == false && rvis[oi - 1][oj] == false)
        {
            if (map[oi - 1][oj] == ROAD_SYMBOL)
            {
                //rvis[oi][oj + 1] = true;
                //read_path(map, nmap, width, height, oi, oj + 1, o_start_node, path_length + 1, DIR_LEFT);
                stack.add_after(new XY(oi - 1, oj, path_length + 1));
                //rvis[oi][oj + 1] = false;
            }
            else if (map[oi - 1][oj] == CITY_SYMBOL)
            {
                if (nmap[oi - 1][oj] != nullptr)    //w innym wypadku jakiś błąd
                {
                    o_start_node->links.add_after(new Link(path_length, o_start_node, nmap[oi - 1][oj]));
                    nmap[oi - 1][oj]->links.add_after(new Link(path_length, nmap[oi - 1][oj], o_start_node));
                }
            }
        }

    }
}

void dfs_udlr(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_udrl(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_urdl(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);

    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_urld(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);


}
void dfs_uldr(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_ulrd(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}

void dfs_durl(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_dulr(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_drul(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_drlu(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_dlur(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_dlru(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}

void dfs_rudl(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_ruld(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_rdul(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_rdlu(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_rlud(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_rldu(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}

void dfs_ludr(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_lurd(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_ldur(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_ldru(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_lrud(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}
void dfs_lrdu(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    dfs_l(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    dfs_u(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
}


int dfs_drr(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, int inters, char parent_direction)
{
    int n = 0;
    if (out_of_map(width, height, oi, oj, DIR_UP) == false && rvis[oi - 1][oj] == false) ++n;
    if (out_of_map(width, height, oi, oj, DIR_DOWN) == false && rvis[oi + 1][oj] == false) ++n;
    if (out_of_map(width, height, oi, oj, DIR_RIGHT) == false && rvis[oi][oj + 1] == false) ++n;
    if (out_of_map(width, height, oi, oj, DIR_LEFT) == false && rvis[oi][oj - 1] == false) ++n;


    if (parent_direction == DIR_UP)
        dfs_d(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);
    else if (parent_direction == DIR_RIGHT)
        dfs_r(map, nmap, width, height, oi, oj, o_start_node, path_length, 0);

    if (n > 1)
        return inters + 1;
    else
        return inters;
    
}

void multi_dfs()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                for (int l = 0; l < 4; l++)
                {

                }
            }
        }
    }



}


void main_dfs(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    XY* tmp = nullptr;
    int path = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_udlr(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_udlr(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_udrl(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_udrl(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_urdl(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_urdl(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_urld(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_urld(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_uldr(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_uldr(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_ulrd(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_ulrd(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_durl(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_durl(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_dulr(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_dulr(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_drul(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_drul(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_drlu(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_drlu(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_dlur(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_dlur(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_dlru(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_dlru(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_rudl(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_rudl(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_ruld(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_ruld(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_rdul(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_rdul(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_rdlu(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_rdlu(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_rlud(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_rlud(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_rldu(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_rldu(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_ludr(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_ludr(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_lurd(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_lurd(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_ldur(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_ldur(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_ldru(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_ldru(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_lrud(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_lrud(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }
    dfs_lrdu(map, nmap, width, height, oi, oj, o_start_node, 0, parent_direction);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();
            dfs_lrdu(map, nmap, width, height, b, a, o_start_node, c, parent_direction);
        }
    }
    stack.root_delete_list();

    //(drr)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (rvis[i][j] == true) rvis[i][j] = false;
        }
    }

    int inters = 0;
    char nxdir = DIR_DOWN;
    inters = dfs_drr(map, nmap, width, height, oi, oj, o_start_node, 0, inters, nxdir);
    while (stack.next != nullptr)
    {
        tmp = stack.next->cont;
        if (tmp != nullptr)
        {
            int a = tmp->x;
            int b = tmp->y;
            int c = tmp->path;
            stack.next->remove_self();

            inters = dfs_drr(map, nmap, width, height, b, a, o_start_node, c, inters, nxdir);
            if (inters == 1)
                nxdir = DIR_RIGHT;
            else if (inters == 3) {
                inters = 0;
                nxdir = DIR_DOWN;
            }

        }
    }
    stack.root_delete_list();

}

void dfs(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
{
    rvis[oi][oj] = true;


    if (out_of_map(width, height, oi, oj, DIR_UP) == false && rvis[oi - 1][oj] == false)
    {

        if (map[oi - 1][oj] == ROAD_SYMBOL)
        {
            //rvis[oi - 1][oj] = true;
            //read_path(map, nmap, width, height, oi - 1, oj, o_start_node, path_length + 1, DIR_DOWN);
            stack.add_after(new XY(oi - 1, oj, path_length + 1));
            //rvis[oi - 1][oj] = false;
        }
        else if (map[oi - 1][oj] == CITY_SYMBOL)
        {
            if (nmap[oi - 1][oj] != nullptr)    //w innym wypadku jakiś błąd
            {
                o_start_node->links.add_after(new Link(path_length, o_start_node, nmap[oi - 1][oj]));
                //return;

            }
        }
    }

    if (out_of_map(width, height, oi, oj, DIR_DOWN) == false && rvis[oi + 1][oj] == false)
    {

        if (map[oi + 1][oj] == ROAD_SYMBOL)
        {
            //rvis[oi + 1][oj] = true;
            //read_path(map, nmap, width, height, oi + 1, oj, o_start_node, path_length + 1, DIR_UP);
            stack.add_after(new XY(oi + 1, oj, path_length + 1));
            //rvis[oi + 1][oj] = false;
        }
        else if (map[oi + 1][oj] == CITY_SYMBOL)
        {
            if (nmap[oi + 1][oj] != nullptr)    //w innym wypadku jakiś błąd
            {
                o_start_node->links.add_after(new Link(path_length, o_start_node, nmap[oi + 1][oj]));
                //return;

            }
        }
    }

    if (out_of_map(width, height, oi, oj, DIR_LEFT) == false && rvis[oi][oj - 1] == false)
    {
        if (map[oi][oj - 1] == ROAD_SYMBOL)
        {
            //rvis[oi][oj - 1] = true;
            //read_path(map, nmap, width, height, oi, oj - 1, o_start_node, path_length + 1, DIR_RIGHT);
            //rvis[oi][oj - 1] = false;
            stack.add_after(new XY(oi, oj - 1, path_length + 1));
        }
        else if (map[oi][oj - 1] == CITY_SYMBOL)
        {
            if (nmap[oi][oj - 1] != nullptr)    //w innym wypadku jakiś błąd
            {
                o_start_node->links.add_after(new Link(path_length, o_start_node, nmap[oi][oj - 1]));
                //return;

            }
        }
    }

    if (out_of_map(width, height, oi, oj, DIR_RIGHT) == false && rvis[oi][oj + 1] == false)
    {
        if (map[oi][oj + 1] == ROAD_SYMBOL)
        {
            //rvis[oi][oj + 1] = true;
            //read_path(map, nmap, width, height, oi, oj + 1, o_start_node, path_length + 1, DIR_LEFT);
            stack.add_after(new XY(oi, oj + 1, path_length + 1));
            //rvis[oi][oj + 1] = false;
        }
        else if (map[oi][oj + 1] == CITY_SYMBOL)
        {
            if (nmap[oi][oj + 1] != nullptr)    //w innym wypadku jakiś błąd
            {
                o_start_node->links.add_after(new Link(path_length, o_start_node, nmap[oi][oj + 1]));
                //return;
                //for (int i = 0; i < height; i++)
                //{
                //    for (int j = 0; j < width; j++)
                //    {
                //        if (rvis[i][j] == true) rvis[i][j] = false;
                //    }
                //}
            }
        }
    }

    //rvis[oi][oj] = false;
}