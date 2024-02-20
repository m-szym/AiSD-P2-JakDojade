#include "data_reading_and_manip.h"

bool isCityNameSymbol(char c)
{
    return (c != ROAD_SYMBOL && 
            c != EMPTY_SYMBOL && 
            c != CITY_SYMBOL);
}

int countSymbolsOnMap(const MapData& m, int x, int y, int count)
{
    if (x + 1 < m.width)
    {
        if (isCityNameSymbol(m.map[y][x + 1]))
        {
            return countSymbolsOnMap(m, x + 1, y, count) + 1;
        }
    }
    return 0;
}

char* readNameFromMap(const MapData& m, int x, int y)
{
    int letters = countSymbolsOnMap(m, x, y, 0) + 1;

    if (letters > 0)
    {
        char* name = new char[letters + 1];
        name[letters] = '\0';

        for (int i = 0; i < letters; i++)
        {
            if (isCityNameSymbol(m.map[y][x + i]))  
            {
                name[i] = m.map[y][x + i];
            }     
        }
        return name;
    }
    return nullptr;
}

void markCity(MapData& m, Node* node, int nameStartX, int nameStartY, int nameLen)
{
    for (int c = 0; c < nameLen; c += nameLen - 1)
    {
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (i == 0 && j == 0) 
                    continue;

                if (!m.out_of_map(nameStartY + i, nameStartX + c + j))
                {
                    if (m.map[nameStartY + i][nameStartX + c + j] == CITY_SYMBOL)
                    {
                        m.cityNodesMask[nameStartY + i][nameStartX + c + j] = node;
                        return;
                    }
                                
                }
                        
            }
                
        }
        
    }
}

void load_cities(MapData& m, Graph& g)
{
    int nodeNr = 0;
    char* nodeName = nullptr;
    int lettersToSkip = 0;
    Node* newNode = nullptr;

    for (int i = 0; i < m.height; i++)
    {
        for (int j = 0; j < m.width; j++)
        {
            if (isCityNameSymbol(m.map[i][j]))
            {
                if (lettersToSkip == 0)
                {
                    nodeName = readNameFromMap(m, j, i);
                    if (nodeName != nullptr)
                    {
                        lettersToSkip = strlen(nodeName) - 1;

                        newNode = new Node(nodeName, nodeNr); 
                        g.insertNode(newNode);
                        markCity(m, newNode, j, i, strlen(nodeName));

                        delete[] nodeName;
                    }
                    nodeNr++;             
                }
                else
                    lettersToSkip--;            
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
            if (m.map[i][j] == CITY_SYMBOL && m.cityNodesMask[i][j] != nullptr)
            {
                main_bfs20(m, m.cityNodesMask[i][j], i, j);
            
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
            else if (m.map[oi - 1][oj] == CITY_SYMBOL && m.cityNodesMask[oi - 1][oj] != nullptr)
            {
                o_start_node->addLink(new Link(l, o_start_node, m.cityNodesMask[oi - 1][oj]));
                m.cityNodesMask[oi - 1][oj]->addLink(new Link(l, m.cityNodesMask[oi - 1][oj], o_start_node));
            
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
                if (m.cityNodesMask[oi + 1][oj] != nullptr)    
                {
                    o_start_node->addLink(new Link(l, o_start_node, m.cityNodesMask[oi + 1][oj]));
                    m.cityNodesMask[oi + 1][oj]->addLink(new Link(l, m.cityNodesMask[oi + 1][oj], o_start_node));

                
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
                if (m.cityNodesMask[oi][oj - 1] != nullptr)
                {
                    o_start_node->addLink(new Link(l, o_start_node, m.cityNodesMask[oi][oj - 1]));
                    m.cityNodesMask[oi][oj - 1]->addLink(new Link(l, m.cityNodesMask[oi][oj - 1], o_start_node));
                
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
                if (m.cityNodesMask[oi][oj + 1] != nullptr)    
                {
                    o_start_node->addLink(new Link(l, o_start_node, m.cityNodesMask[oi][oj + 1]));
                    m.cityNodesMask[oi][oj + 1]->addLink(new Link(l, m.cityNodesMask[oi][oj + 1], o_start_node));
                
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

                hstart_city = g.getNode(start_city_substring);
                hend_city = g.getNode(end_city_substring);

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