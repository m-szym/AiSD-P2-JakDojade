#pragma once

const char CITY_SYMBOL = '*';
const char ROAD_SYMBOL = '#';
const char EMPTY_SYMBOL = '.';

const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';

const int BASE_STRING_BUFFER_SIZE = 32;

#include <cmath>
const int MAX_KEY_SIZE = 20;
const double HASH_PRIME = (sqrt(5) - 1) / 2;