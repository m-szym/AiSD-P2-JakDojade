#pragma once

#include <cstring>
#include <cctype>
#include <cstdio>
#include <cstdlib>

const int BASE_STRING_BUFFER_SIZE = 32;

bool isNumber(char* string);

char* readString();

char** tokenizeString(char* string, char* delimiter, int& tokens);

