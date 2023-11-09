#include "other.h"


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