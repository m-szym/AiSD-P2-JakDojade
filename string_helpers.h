#pragma once

#include <cstring>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Constants.h"

bool isNumber(char* string);

char* readString();

char** tokenizeString(char* string, char* delimiter, int& tokens);

