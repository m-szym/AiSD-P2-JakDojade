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

void loadCities(MapData& m, Graph& g)
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


void read_flight(Graph &g)
{
    int tokens;
    char* flightDeclaration = readString();
    char** flightData = tokenizeString(flightDeclaration, " ", tokens);


    if (flightDeclaration != NULL && flightData != NULL)
    {
        if (tokens == 3)
        {
            if (isNumber(flightData[2]))
            {
                Node* startCity = g.getNode(flightData[0]);
                Node* endCity   = g.getNode(flightData[1]);
                int flightTime  = atoi(flightData[2]);

                if (startCity != nullptr && 
                    endCity != nullptr   && 
                    flightTime > 0)
                {
                    startCity->addLink(new Link(flightTime, startCity, endCity, true));
                }
            }
        }
    }

    free(flightDeclaration);
    free(flightData);
}

void loadFlights(Graph& g)
{
    int flights = 0;
    std::cin >> flights;
    while (flights >= 0)
    {
        read_flight(g);
        flights--;
    }
}


void runCommand(Graph& g)
{
    int tokens;
    char* commandDeclaration = readString();
    char** commandData = tokenizeString(commandDeclaration, " ", tokens);

    if (commandDeclaration != NULL && commandData != NULL)
    {
        if (tokens == 3)
        {
            if (isNumber(commandData[2]))
            {
                Node* startCity = g.getNode(commandData[0]);
                Node* endCity   = g.getNode(commandData[1]);
                int mode        = atoi(commandData[2]);

                if (startCity != nullptr && 
                    endCity   != nullptr && 
                    mode > 0)
                {
                    g.dijkstra(startCity, endCity, mode);
                }
            }
        }
    }

    free(commandDeclaration);
    free(commandData);
}

void run(Graph& g)
{
    int q = 0;
    std::cin >> q;
    while (q >= 0)
    {
        runCommand(g);
        q--;  
    }
}