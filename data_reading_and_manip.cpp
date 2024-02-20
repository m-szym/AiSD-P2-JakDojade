#include "data_reading_and_manip.h"

void load_cities(MapData& m, Graph& g)
{
    int k = 0;
    char* tmp_s = nullptr;
    int stop_i = 0;
    Node* curn = nullptr;
    for (int i = 0; i < m.height; i++)
    {
        for (int j = 0; j < m.width; j++)
        {
            if (m.map[i][j] != ROAD_SYMBOL && m.map[i][j] != EMPTY_SYMBOL && m.map[i][j] != CITY_SYMBOL)
            {
                if (stop_i == 0)
                {
                    tmp_s = read_name(m, g, i, j);
                    if (tmp_s != nullptr)
                    {
                        stop_i = strlen(tmp_s) - 1;

                        curn = g.insert_to_hash(new Node(tmp_s, k));
                        register_star(m, g, curn, i, j, strlen(tmp_s));

                        delete[] tmp_s;
                    }
                    k++;             
                }
                else
                    stop_i--;            
            }   
        }
    }
}

char* read_name(MapData& m, Graph& g, int oi, int oj)
{
    int letters = count_letters(m, g, oi, oj, DIR_RIGHT, 0) + 1;

    if (letters > 0)
    {
        char* name = new char[letters + 1];
        name[letters] = '\0';

        for (int i = 0; i < letters; i++)
        {
            if (m.map[oi][oj + i] != ROAD_SYMBOL && 
                m.map[oi][oj + i] != EMPTY_SYMBOL && 
                m.map[oi][oj + i] != CITY_SYMBOL)    
            {
                name[i] = m.map[oi][oj + i];
            }     
        }
        return name;
    }
    return nullptr;
}

int count_letters(MapData& m, Graph& g, int oi, int oj, char direction, int count)
{
    if (direction == DIR_LEFT)
    {
        if (oj - 1 >= 0)
        {
            if (m.map[oi][oj - 1] != ROAD_SYMBOL && 
                m.map[oi][oj - 1] != EMPTY_SYMBOL && 
                m.map[oi][oj - 1] != CITY_SYMBOL)
            {
                return count_letters(m, g, oi, oj - 1, direction, count) + 1;
            }
            else
                return 0;
        }
    
    }
    else if (direction == DIR_RIGHT)
    {
        if (oj + 1 < m.width)
        {
            if (m.map[oi][oj + 1] != ROAD_SYMBOL 
                && m.map[oi][oj + 1] != EMPTY_SYMBOL 
                && m.map[oi][oj + 1] != CITY_SYMBOL)
            {
                return count_letters(m, g, oi, oj + 1, direction, count) + 1;
            
            }
            else
                return 0;
        
        }
    
    }

    return 0;
}

void register_star(MapData& m, Graph& g, Node* o_start_node, int oi, int oj, int strlen)
{
    for (int c = 0; c < strlen; c += strlen - 1)
    {
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (i == 0 && j == 0) continue;

                if (m.out_of_map_coords(oi + i, oj + c + j, DIR_UP) == false)
                {
                    if (m.map[oi + i][oj + c + j] == CITY_SYMBOL)
                    {
                        m.nmap[oi + i][oj + c + j] = o_start_node;
                        return;
                    
                    }
                                
                }
                        
            }
                
        }
        
    }
}



void find_first_level_connections(MapData& m, Graph& g)
{
    for (int i = 0; i < m.height; i++)
    {
        for (int j = 0; j < m.width; j++)
        {
            if (m.map[i][j] == CITY_SYMBOL && m.nmap[i][j] != nullptr)
            {
                main_bfs20(m, m.nmap[i][j], i, j);
            
            }
                
        }
        
    }
}

void main_bfs20(MapData& m, Node* o_start_node, int start_node_i, int start_node_j)
{
    static int visi = 0;

    int oi = 0;
    int oj = 0;
    int l = 0;

    set_road_tile(m.x, 0, 0, start_node_i, start_node_j, 0);
    int qCi = 0;
    int qCj = 1;
    int qIi = 0;
    int qIj = 0;


    while (qCi * m.width + qCj > qIi * m.width + qIj)
    {
        m.x[qIi][qIj].unload(oj, oi, l);
        update_skipper(m.width, qIi, qIj);


        if (oi - 1 >= 0)
        {
            if (m.map[oi - 1][oj] == ROAD_SYMBOL && m.rvis2[oi - 1][oj] != visi)
            {
                m.rvis2[oi - 1][oj] = visi;
                set_road_tile(m.x, qCi, qCj, oi - 1, oj, l + 1);
                update_skipper(m.width, qCi, qCj);
            
            }
            else if (m.map[oi - 1][oj] == CITY_SYMBOL && m.nmap[oi - 1][oj] != nullptr)
            {
                o_start_node->addLink(new Link(l, o_start_node, m.nmap[oi - 1][oj]));
                m.nmap[oi - 1][oj]->addLink(new Link(l, m.nmap[oi - 1][oj], o_start_node));
            
            }
        
        }

        if (oi + 1 < m.height)
        {
            if (m.map[oi + 1][oj] == ROAD_SYMBOL && m.rvis2[oi + 1][oj] != visi)
            {
                m.rvis2[oi + 1][oj] = visi;

                set_road_tile(m.x, qCi, qCj, oi + 1, oj, l + 1);
                update_skipper(m.width, qCi, qCj);

            
            }
            else if (m.map[oi + 1][oj] == CITY_SYMBOL)
            {
                if (m.nmap[oi + 1][oj] != nullptr)    
                {
                    o_start_node->addLink(new Link(l, o_start_node, m.nmap[oi + 1][oj]));
                    m.nmap[oi + 1][oj]->addLink(new Link(l, m.nmap[oi + 1][oj], o_start_node));

                
                }
            
            }
                
        }

        if (oj - 1 >= 0)
        {
            if (m.map[oi][oj - 1] == ROAD_SYMBOL && m.rvis2[oi][oj - 1] != visi)
            {
                m.rvis2[oi][oj - 1] = visi;
                set_road_tile(m.x, qCi, qCj, oi, oj - 1, l + 1);
                update_skipper(m.width, qCi, qCj);
            
            }
            else if (m.map[oi][oj - 1] == CITY_SYMBOL)
            {
                if (m.nmap[oi][oj - 1] != nullptr)
                {
                    o_start_node->addLink(new Link(l, o_start_node, m.nmap[oi][oj - 1]));
                    m.nmap[oi][oj - 1]->addLink(new Link(l, m.nmap[oi][oj - 1], o_start_node));
                
                }
                        
            }
                
        }

        if (oj + 1 < m.width)
        {
            if (m.map[oi][oj + 1] == ROAD_SYMBOL && m.rvis2[oi][oj + 1] != visi)
            {
                m.rvis2[oi][oj + 1] = visi;
                set_road_tile(m.x, qCi, qCj, oi, oj + 1, l + 1);
                update_skipper(m.width, qCi, qCj);
            
            }
            else if (m.map[oi][oj + 1] == CITY_SYMBOL)
            {
                if (m.nmap[oi][oj + 1] != nullptr)    
                {
                    o_start_node->addLink(new Link(l, o_start_node, m.nmap[oi][oj + 1]));
                    m.nmap[oi][oj + 1]->addLink(new Link(l, m.nmap[oi][oj + 1], o_start_node));
                
                }
                        
            }
                
        }
        
    }

    ++visi;
}

void update_skipper(int inner_limit, int& outer, int& inner)
{
    ++inner;
    if (inner == inner_limit)
    {
        ++outer;
        inner = 0;
    
    }
}



void read_flights(Graph& g)
{
    int flights = 0;
    std::cin >> flights;
    while (flights >= 0)
    {
        read_flight(g);
        flights--;
    
    }
}

void read_flight(Graph& g)
{
    //char* raw_string = read_flight_declaration();
    char* buff = new char[BASE_STRING_BUFFER_SIZE];
    for (int i = 0; i < BASE_STRING_BUFFER_SIZE; i++)
    {
        buff[i] = '\0';
    
    }

    char* raw_string = fgets(buff, BASE_STRING_BUFFER_SIZE, stdin);

    char* start_city_substring = NULL;
    char* end_city_substring = NULL;
    char* flight_time_substring = NULL;

    Node* hstart_city = nullptr;
    Node* hend_city = nullptr;
    int flight_time = 0;

    if (raw_string != nullptr)
    {
        start_city_substring = strtok(raw_string, " ");
        end_city_substring = strtok(NULL, " ");
        flight_time_substring = strtok(NULL, " ");

        if (start_city_substring != NULL && end_city_substring != NULL && flight_time_substring != NULL)
        {
            if (is_number(flight_time_substring) == true)
            {
                flight_time = atoi(flight_time_substring);              

                hstart_city = g.get_from_hash(start_city_substring);
                hend_city = g.get_from_hash(end_city_substring);

                if (hstart_city != nullptr && hend_city != nullptr && flight_time > 0)
                {
                    hstart_city->addLink(new Link(flight_time, hstart_city, hend_city, true));
                
                }
                        
            }
                
        }
        
    }

    delete buff;
}


char* read_flight_declaration()
{
    int current_char = '\0';
    char* flight_declaration = (char*)malloc(BASE_STRING_BUFFER_SIZE * sizeof(char));

    char* string_buffer = NULL;

    int number_of_chars_read = 0;
    int char_array_size = BASE_STRING_BUFFER_SIZE;
    int not_EOF_chars_read = 0;


    while (current_char != '\n')
    {
        current_char = getchar();

        if (current_char == EOF)
            break;

        if (!( current_char < ' '))
        {

            if (current_char) {
                number_of_chars_read++;

                if (number_of_chars_read >= char_array_size)
                {
                    string_buffer = (char*)realloc(flight_declaration, 2 * char_array_size * sizeof(char));
                    char_array_size = 2 * char_array_size;

                    if (string_buffer != NULL)
                    {
                        flight_declaration = string_buffer;
                        flight_declaration[number_of_chars_read - 1] = (char)current_char;
                    
                    }
                                
                }
                else
                {
                    if (flight_declaration != NULL)
                    {
                        flight_declaration[number_of_chars_read - 1] = (char)current_char;
                        
                    }
                                
                }
                        
            }
                
        }
        
    }

    if (flight_declaration != NULL) flight_declaration[number_of_chars_read] = '\0';
    return flight_declaration;
}