#include "other.h"


char* find_name(char** map, int width, int height, int oi, int oj)
{


    return nullptr;
}

char* read_name(char** map, int width, int height, int oi, int oj)
{
    int letters = count_letters(map, width, height, oi, oj, DIR_RIGHT, 0) + 1;
    if (letters > 0)
    {
        char* name = new char[letters + 1];
        name[letters] = '\0';

        for (int i = 0; i < letters; i++)
        {
            //if (map[oi][oj + 1] != ROAD_SYMBOL && map[oi][oj + 1] != EMPTY_SYMBOL && map[oi][oj + 1] != CITY_SYMBOL)    //teoretycnie niepotrzebne
            //{
            name[i] = map[oi][oj + i];
            //}
        }
        return name;
    }

    return nullptr;
}


int count_letters(char** map, int width, int height, int oi, int oj, char direction, int count)
{
    if (direction == DIR_LEFT)
    {
        if (oj - 1 >= 0)
        {
            if (map[oi][oj - 1] != ROAD_SYMBOL && map[oi][oj - 1] != EMPTY_SYMBOL && map[oi][oj - 1] != CITY_SYMBOL)
            {
                return count_letters(map, width, height, oi, oj - 1, direction, count) + 1;
            }
            else
                return 0;
        }
    }
    else if (direction == DIR_RIGHT)
    {
        if (oj + 1 < width)
        {
            if (map[oi][oj + 1] != ROAD_SYMBOL && map[oi][oj + 1] != EMPTY_SYMBOL && map[oi][oj + 1] != CITY_SYMBOL)
            {
                return count_letters(map, width, height, oi, oj + 1, direction, count) + 1;
            }
            else
                return 0;
        }
    }

    return 0;
}


bool out_of_map(int width, int height, int i, int j, char direction)
{
    if (direction == DIR_UP)
    {
        if (i - 1 < 0) return true;
        else return false;
    }
    else if (direction == DIR_DOWN)
    {
        if (i + 1 >= height) return true;
        else return false;
    }
    else if (direction == DIR_LEFT)
    {
        if (j - 1 < 0) return true;
        else return false;
    }
    else if (direction == DIR_RIGHT)
    {
        if (j + 1 >= width) return true;
        else return false;
    }

    return true;    //b³¹d jakiœ
}

bool out_of_map_coords(int width, int height, int i, int j, char direction)
{
    //if (direction == DIR_UP)
    //{
        if (i < 0) return true;
        //else return false;
    //}
    //if (direction == DIR_DOWN)
    //{
        if (i >= height) return true;
        //else return false;
    //}

    //if (direction == DIR_LEFT)
    //{
        if (j < 0) return true;
        //else return false;
    //}
    //if (direction == DIR_RIGHT)
    //{
        if (j >= width) return true;
        else return false;
    //}

    return true;    //b³¹d jakiœ
}






//void read_path2(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
//{
//    rvis[oi][oj] = true;
//    //std::cout << oi << ", " << oj << "\n";
//
//
//
//
//    if (out_of_map(width, height, oi, oj, DIR_UP) == false && rvis[oi - 1][oj] == false)
//    {
//
//        if (map[oi - 1][oj] == ROAD_SYMBOL)
//        {
//            //rvis[oi - 1][oj] = true;
//            read_path2(map, nmap, width, height, oi - 1, oj, o_start_node, path_length + 1, DIR_DOWN);
//            //rvis[oi - 1][oj] = false;
//        }
//        else if (map[oi - 1][oj] == CITY_SYMBOL)
//        {
//            if (nmap[oi - 1][oj] != nullptr)    //w innym wypadku jakiœ b³¹d
//            {
//                o_start_node->links.add_after(new Link(path_length + 1, o_start_node, nmap[oi - 1][oj]));
//                //return;
//
//            }
//        }
//    }
//
//    if (out_of_map(width, height, oi, oj, DIR_DOWN) == false && rvis[oi + 1][oj] == false)
//    {
//
//        if (map[oi + 1][oj] == ROAD_SYMBOL)
//        {
//            //rvis[oi + 1][oj] = true;
//            read_path2(map, nmap, width, height, oi + 1, oj, o_start_node, path_length + 1, DIR_UP);
//            //rvis[oi + 1][oj] = false;
//        }
//        else if (map[oi + 1][oj] == CITY_SYMBOL)
//        {
//            if (nmap[oi + 1][oj] != nullptr)    //w innym wypadku jakiœ b³¹d
//            {
//                o_start_node->links.add_after(new Link(path_length + 1, o_start_node, nmap[oi + 1][oj]));
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
//            read_path2(map, nmap, width, height, oi, oj - 1, o_start_node, path_length + 1, DIR_RIGHT);
//            //rvis[oi][oj - 1] = false;
//        }
//        else if (map[oi][oj - 1] == CITY_SYMBOL)
//        {
//            if (nmap[oi][oj - 1] != nullptr)    //w innym wypadku jakiœ b³¹d
//            {
//                o_start_node->links.add_after(new Link(path_length + 1, o_start_node, nmap[oi][oj - 1]));
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
//            read_path2(map, nmap, width, height, oi, oj + 1, o_start_node, path_length + 1, DIR_LEFT);
//            //rvis[oi][oj + 1] = false;
//        }
//        else if (map[oi][oj + 1] == CITY_SYMBOL)
//        {
//            if (nmap[oi][oj + 1] != nullptr)    //w innym wypadku jakiœ b³¹d
//            {
//                o_start_node->links.add_after(new Link(path_length + 1, o_start_node, nmap[oi][oj + 1]));
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
//
//    rvis[oi][oj] = false;
//}
//
//void read_path(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int path_length, char parent_direction)
//{
//    rvis[oi][oj] = true;
//
//    if (parent_direction != DIR_UP)
//    {
//        if (out_of_map(width, height, oi, oj, DIR_UP) == false && rvis[oi - 1][oj] == false)
//        {
//
//            if (map[oi - 1][oj] == ROAD_SYMBOL)
//            {
//                //rvis[oi - 1][oj] = true;
//                read_path(map, nmap, width, height, oi - 1, oj, o_start_node, path_length + 1, DIR_DOWN);
//                //rvis[oi - 1][oj] = false;
//            }
//            else if (map[oi - 1][oj] == CITY_SYMBOL)
//            {
//                if (nmap[oi - 1][oj] != nullptr)    //w innym wypadku jakiœ b³¹d
//                {
//                    o_start_node->links.add_after(new Link(path_length + 1, o_start_node, nmap[oi - 1][oj]));
//                    //return;
//
//                }
//            }
//        }
//    }
//
//    if (parent_direction != DIR_DOWN)
//    {
//        if (out_of_map(width, height, oi, oj, DIR_DOWN) == false && rvis[oi + 1][oj] == false)
//        {
//
//            if (map[oi + 1][oj] == ROAD_SYMBOL)
//            {
//                //rvis[oi + 1][oj] = true;
//                read_path(map, nmap, width, height, oi + 1, oj, o_start_node, path_length + 1, DIR_UP);
//                //rvis[oi + 1][oj] = false;
//            }
//            else if (map[oi + 1][oj] == CITY_SYMBOL)
//            {
//                if (nmap[oi + 1][oj] != nullptr)    //w innym wypadku jakiœ b³¹d
//                {
//                    o_start_node->links.add_after(new Link(path_length + 1, o_start_node, nmap[oi + 1][oj]));
//                    //return;
//
//                }
//            }
//        }
//    }
//
//    if (parent_direction != DIR_LEFT)
//    {
//        if (out_of_map(width, height, oi, oj, DIR_LEFT) == false && rvis[oi][oj - 1] == false)
//        {
//            if (map[oi][oj - 1] == ROAD_SYMBOL)
//            {
//                //rvis[oi][oj - 1] = true;
//                read_path(map, nmap, width, height, oi, oj - 1, o_start_node, path_length + 1, DIR_RIGHT);
//                //rvis[oi][oj - 1] = false;
//            }
//            else if (map[oi][oj - 1] == CITY_SYMBOL)
//            {
//                if (nmap[oi][oj - 1] != nullptr)    //w innym wypadku jakiœ b³¹d
//                {
//                    o_start_node->links.add_after(new Link(path_length + 1, o_start_node, nmap[oi][oj - 1]));
//                    //return;
//
//                }
//            }
//        }
//    }
//
//    if (parent_direction != DIR_RIGHT)
//    {
//        if (out_of_map(width, height, oi, oj, DIR_RIGHT) == false && rvis[oi][oj + 1] == false)
//        {
//            if (map[oi][oj + 1] == ROAD_SYMBOL)
//            {
//                //rvis[oi][oj + 1] = true;
//                read_path(map, nmap, width, height, oi, oj + 1, o_start_node, path_length + 1, DIR_LEFT);
//                //rvis[oi][oj + 1] = false;
//            }
//            else if (map[oi][oj + 1] == CITY_SYMBOL)
//            {
//                if (nmap[oi][oj + 1] != nullptr)    //w innym wypadku jakiœ b³¹d
//                {
//                    o_start_node->links.add_after(new Link(path_length + 1, o_start_node, nmap[oi][oj + 1]));
//                    //return;
//                    //for (int i = 0; i < height; i++)
//                    //{
//                    //    for (int j = 0; j < width; j++)
//                    //    {
//                    //        if (rvis[i][j] == true) rvis[i][j] = false;
//                    //    }
//                    //}
//                }
//            }
//        }
//    }
//
//    rvis[oi][oj] = false;
//}
//
//void read_all_paths(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node)
//{
//    for (int i = 0; i < height; i++)
//    {
//        for (int j = 0; j < width; j++)
//        {
//            if (rvis[i][j] == true) rvis[i][j] = false;
//        }
//    }
//
//    if (out_of_map(width, height, oi, oj, DIR_UP) == false)
//    {
//        if (map[oi - 1][oj] == ROAD_SYMBOL)
//        {
//            //rvis[oi - 1][oj] = true;
//            read_path2(map, nmap, width, height, oi - 1, oj, o_start_node, 0, DIR_DOWN);
//        }
//        else if (map[oi - 1][oj] == CITY_SYMBOL)
//        {
//            o_start_node->links.add_after(new Link(0, o_start_node, nmap[oi - 1][oj]));
//        }
//
//    }
//
//
//
//    if (out_of_map(width, height, oi, oj, DIR_DOWN) == false)
//    {
//        if (map[oi + 1][oj] == ROAD_SYMBOL)
//        {
//            //rvis[oi + 1][oj] = true;
//            read_path2(map, nmap, width, height, oi + 1, oj, o_start_node, 0, DIR_UP);
//        }
//        else if (map[oi + 1][oj] == CITY_SYMBOL)
//        {
//            o_start_node->links.add_after(new Link(0, o_start_node, nmap[oi + 1][oj]));
//        }
//    }
//
//
//    if (out_of_map(width, height, oi, oj, DIR_LEFT) == false)
//    {
//        if (map[oi][oj - 1] == ROAD_SYMBOL)
//        {
//            //rvis[oi][oj - 1] = true;
//            read_path2(map, nmap, width, height, oi, oj - 1, o_start_node, 0, DIR_RIGHT);
//        }
//        else if (map[oi][oj - 1] == CITY_SYMBOL)
//        {
//            o_start_node->links.add_after(new Link(0, o_start_node, nmap[oi][oj - 1]));
//        }
//    }
//
//
//    if (out_of_map(width, height, oi, oj, DIR_RIGHT) == false)
//    {
//        if (map[oi][oj + 1] == ROAD_SYMBOL)
//        {
//            //rvis[oi][oj + 1] = true;
//            read_path2(map, nmap, width, height, oi, oj + 1, o_start_node, 0, DIR_LEFT);
//        }
//        else if (map[oi][oj + 1] == CITY_SYMBOL)
//        {
//            o_start_node->links.add_after(new Link(0, o_start_node, nmap[oi][oj + 1]));
//        }
//    }
//
//
//}


void register_star(char** map, Node*** nmap, int width, int height, int oi, int oj, Node* o_start_node, int strlen)
{
    for (int k = 0; k < strlen; k += strlen - 1)
    {
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (i == 0 && j == 0) continue;

                if (out_of_map_coords(width, height, oi + i, oj + k + j, DIR_UP) == false)
                {
                    if (map[oi + i][oj + k + j] == CITY_SYMBOL)
                    {
                        nmap[oi + i][oj + k + j] = o_start_node;
                        return;
                    }
                }
            }
        }
    }
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
        {
            if (not_EOF_chars_read == 0)
                break;
        }
        else not_EOF_chars_read++;

        if (!(current_char == '\n' || current_char == NULL || current_char == '\x00' || current_char == '\t' || current_char < ' '))
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
    };

    if (flight_declaration != NULL) flight_declaration[number_of_chars_read] = '\0';
    return flight_declaration;
}

bool is_number(char* string)
{
    int number_characters = 0;

    for (int i = 0; i < strlen(string); ++i)
    {
        if (isdigit(string[i]) != 0) number_characters++;
    }

    if (number_characters == strlen(string)) return true;
    else return false;
}

void read_flight(Graph& g)
{
    char* raw_string = read_flight_declaration();
    char* start_city_substring = NULL;
    char* end_city_substring = NULL;
    char* flight_time_substring = NULL;

    List2d<Node>* start_city = nullptr;
    List2d<Node>* end_city = nullptr;

    Node* hstart_city = nullptr;
    Node* hend_city = nullptr;

    int si = 0;
    int ei = 0;
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

                //start_city = g.get_city_by_name(start_city_substring);
                //end_city = g.get_city_by_name(end_city_substring);

                //si = g.get_city_node_i_by_name(start_city_substring);
                //ei = g.get_city_node_i_by_name(end_city_substring);


                if (hstart_city != nullptr)
                {
                    if (hend_city != nullptr)
                    {
                        if (flight_time > 0)
                        {
                            //start_city->cont->links.add_after(new Link(flight_time, g., end_city->cont, true));
                            //g.nodes[si].links.add_after(new Link(flight_time, &(g.nodes[si]), &(g.nodes[ei]), true));
                            hstart_city->links.add_after(new Link(flight_time, hstart_city, hend_city, true));
                        }
                        else
                            std::cout << "lot wrong time" << flight_time;
                    }
                    else
                        std::cout << "lot null end";
                }
                else
                    std::cout << "lot null start";
                
            }
        }

    }

    free(raw_string);
}


char* read_command()
{
    int current_char = '\0';
    char* raw_command = (char*)malloc(BASE_STRING_BUFFER_SIZE * sizeof(char));
    char* string_buffer = NULL;

    int number_of_chars_read = 0;
    int char_array_size = BASE_STRING_BUFFER_SIZE;
    int not_EOF_chars_read = 0;


    while (current_char != '\n')
    {
        current_char = getchar();

        if (current_char == EOF)
        {
            if (not_EOF_chars_read == 0)
                break;
        }
        else not_EOF_chars_read++;

        if (!(current_char == '\n' || current_char == NULL || current_char == '\x00' || current_char == '\t' || current_char < ' '))
        {

            if (current_char) {
                number_of_chars_read++;

                if (number_of_chars_read >= char_array_size)
                {
                    string_buffer = (char*)realloc(raw_command, 2 * char_array_size * sizeof(char));
                    char_array_size = 2 * char_array_size;

                    if (string_buffer != NULL)
                    {
                        raw_command = string_buffer;
                        raw_command[number_of_chars_read - 1] = (char)current_char;
                    }
                }
                else
                {
                    if (raw_command != NULL)
                    {
                        raw_command[number_of_chars_read - 1] = (char)current_char;
                    }
                }
            }
        }
    };

    if (raw_command != NULL) raw_command[number_of_chars_read] = '\0';
    return raw_command;
}


void do_command(Graph& g)
{
    char* raw_string = read_command();
    //std::cout << raw_string << "\n";

    char* start_city_substring = NULL;
    char* end_city_substring = NULL;
    char* mode = NULL;

    List2d<Node>* start_city = nullptr;
    List2d<Node>* end_city = nullptr;
    int mode_i = 0;

    Node* hstart_city = nullptr;
    Node* hend_city = nullptr;

    if (raw_string != nullptr)
    {
        start_city_substring = strtok(raw_string, " ");
        end_city_substring = strtok(NULL, " ");
        mode = strtok(NULL, " ");
        if (start_city_substring != NULL && end_city_substring != NULL && mode != NULL)
        {
            if (is_number(mode) == true)
            {
                mode_i = atoi(mode);

                //int s = g.get_city_node_i_by_name(start_city_substring);
                //int e = g.get_city_node_i_by_name(end_city_substring);
                //if (s >= 0 && e >= 0)
                //    my_dijkstra3(g, s, e, mode_i);

                hstart_city = g.get_from_hash(start_city_substring);
                hend_city = g.get_from_hash(end_city_substring);

                if (hstart_city != nullptr && hend_city != nullptr)
                    my_dijkstra5(g, hstart_city, hend_city, mode_i);

            }
        }

    }

    free(raw_string);
}