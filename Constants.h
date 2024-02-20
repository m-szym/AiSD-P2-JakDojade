#pragma once

const char CITY_SYMBOL = '*';
const char ROAD_SYMBOL = '#';
const char EMPTY_SYMBOL = '.';

const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';

const int BASE_STRING_BUFFER_SIZE = 64;

#include <cmath>
const int STRING_HASH_MAX_KEY_SIZE = 20;
const int STRING_HASH_PRIME_LIMITER = 15485863;
const int STRING_HASH_BASE_PRIME = 67;
const char STRING_HASH_FLOOR_CHAR = '0';

const double HASH_PRIME = (sqrt(5) - 1) / 2;
