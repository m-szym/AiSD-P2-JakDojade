#include "string_helpers.h"

bool is_number(char* string)
{
    int number_characters = 0;

    for (int i = 0; i < strlen(string); ++i)
    {
        if (isdigit(string[i]) != 0 || string[i] == '\n') number_characters++;
    
}

    if (number_characters == strlen(string)) return true;
    else return false;
}

long long hash_string(char* key)
{
        int i = 0;
        int powered_prime = STRING_HASH_BASE_PRIME;
        long long hash = 0;     

        while (i < STRING_HASH_MAX_KEY_SIZE)
        {
                if (key[i] == '\0') return hash;

                hash = (hash + (key[i] - STRING_HASH_FLOOR_CHAR + 1) * powered_prime) % STRING_HASH_PRIME_LIMITER;
                powered_prime = (powered_prime * STRING_HASH_BASE_PRIME) % STRING_HASH_PRIME_LIMITER;
                ++i;
        
}

        return hash;
}