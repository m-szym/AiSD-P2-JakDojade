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



struct XYZ
{
    int x, y, z;
};

XYZ xyz_pack(int x, int y, int z)
{
    XYZ xyz;
    xyz.x = x;
    xyz.y = y;
    xyz.z = z;
    return xyz;
}

void xyz_unpack(const XYZ& xyz, int& x, int& y, int& z)
{
    x = xyz.x;
    y = xyz.y;
    z = xyz.z;
}

void bfs30(MapData& m, Node* startNode, XYZ* queue, XYZ start)
{
    static int searchCycleNr = 0;

    int y = 0;
    int x = 0;
    int distance = 0;

    
    queue[0] = start;                            
    int queueHead = 0;
    int queueTail = 1;


    while (queueHead < queueTail)
    {
        xyz_unpack(queue[queueHead], x, y, distance);
        queueHead++;

        if (y - 1 >= 0)
        {
            if (m.map[y - 1][x] == ROAD_SYMBOL && m.lastVisitCycleNr[y - 1][x] != searchCycleNr)
            {
                m.lastVisitCycleNr[y - 1][x] = searchCycleNr;        
                queue[queueTail] = xyz_pack(x, y - 1, distance + 1);
                queueTail++;
            }
            else if (m.map[y - 1][x] == CITY_SYMBOL && m.cityNodesMask[y - 1][x] != nullptr)
            {
                startNode->addLink(new Link(distance, startNode, m.cityNodesMask[y - 1][x]));
                m.cityNodesMask[y - 1][x]->addLink(new Link(distance, m.cityNodesMask[y - 1][x], startNode));
            }
        }

        if (y + 1 < m.height)
        {
            if (m.map[y + 1][x] == ROAD_SYMBOL && m.lastVisitCycleNr[y + 1][x] != searchCycleNr)
            {
                m.lastVisitCycleNr[y + 1][x] = searchCycleNr;
                queue[queueTail] = xyz_pack(x, y + 1, distance + 1);
                queueTail++;
            }
            else if (m.map[y + 1][x] == CITY_SYMBOL)
            {
                if (m.cityNodesMask[y + 1][x] != nullptr)    
                {
                    startNode->addLink(new Link(distance, startNode, m.cityNodesMask[y + 1][x]));
                    m.cityNodesMask[y + 1][x]->addLink(new Link(distance, m.cityNodesMask[y + 1][x], startNode));
                }
            }
        }

        if (x - 1 >= 0)
        {
            if (m.map[y][x - 1] == ROAD_SYMBOL && m.lastVisitCycleNr[y][x - 1] != searchCycleNr)
            {
                m.lastVisitCycleNr[y][x - 1] = searchCycleNr;
                queue[queueTail] = xyz_pack(x - 1, y, distance + 1);
                queueTail++;
            }
            else if (m.map[y][x - 1] == CITY_SYMBOL)
            {
                if (m.cityNodesMask[y][x - 1] != nullptr)
                {
                    startNode->addLink(new Link(distance, startNode, m.cityNodesMask[y][x - 1]));
                    m.cityNodesMask[y][x - 1]->addLink(new Link(distance, m.cityNodesMask[y][x - 1], startNode));
                }
            }
        }

        if (x + 1 < m.width)
        {
            if (m.map[y][x + 1] == ROAD_SYMBOL && m.lastVisitCycleNr[y][x + 1] != searchCycleNr)
            {
                m.lastVisitCycleNr[y][x + 1] = searchCycleNr;
                queue[queueTail] = xyz_pack(x + 1, y, distance + 1);
                queueTail++;
            
            }
            else if (m.map[y][x + 1] == CITY_SYMBOL)
            {
                if (m.cityNodesMask[y][x + 1] != nullptr)    
                {
                    startNode->addLink(new Link(distance, startNode, m.cityNodesMask[y][x + 1]));
                    m.cityNodesMask[y][x + 1]->addLink(new Link(distance, m.cityNodesMask[y][x + 1], startNode));
                }     
            }    
        }
    }

    ++searchCycleNr;
}
// Classic BFS, but written iteratively and without real queue, using array instead.
// The function is used to find all the cities that are directly connected to the starting city and save the data in the graph.
// Although the function is quite convoluted recursion was unacceptable as the amount of data caused stack overflows with recurive variant,
// and the iterative version was faster and more memory efficient. 
// Array is used in place of queue due to the project requirements and to ensure fastest possible performance.
// Without tuples a struct was used to quickly store and read triplets of integers.

void findDirectCityConnections(MapData& m, Graph& g)
{
    XYZ queue[m.width * m.height];

    for (int i = 0; i < m.height; i++)
    {
        for (int j = 0; j < m.width; j++)
        {
            if (m.map[i][j] == CITY_SYMBOL && m.cityNodesMask[i][j] != nullptr)
            {
                bfs30(m, m.cityNodesMask[i][j], queue, xyz_pack(j, i, 0));
            }    
        }
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