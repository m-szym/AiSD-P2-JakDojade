#include "string_helpers.h"

bool isNumber(char* string)
{
    int number_characters = 0;

    for (int i = 0; i < strlen(string); ++i)
    {
        if (isdigit(string[i]) != 0 || string[i] == '\n') number_characters++;
    
}

    if (number_characters == strlen(string)) return true;
    else return false;
}


bool isLegalChar(char c)
{
    if (c == '\n' || c == NULL || c == '\x00' || c == '\t' || c < ' ')
        return false;
    else
        return true;
}

bool reachedEOF(char currentChar, int& notEOF)
{
    if (currentChar == EOF)
    {
        if (notEOF == 0)
            return true;
    }
    else 
    {
        notEOF++;
        return false;
    }
}

char* resizeCString(char* string, int newSize)
{
    char* newString = (char*)realloc(string, newSize * sizeof(char));
    
    if (newString == NULL)
    {
        free(string);
        return NULL;
    }
    else
        return newString;
}

char* readString()
{
    char currentChar = '\0';
    char* buffer = (char*)malloc(BASE_STRING_BUFFER_SIZE * sizeof(char));

    int charsRead = 0;
    int bufferSize = BASE_STRING_BUFFER_SIZE;
    int notEOFChars = 0;

    while (currentChar != '\n')
    {
        currentChar = getchar();

        if (reachedEOF(currentChar, notEOFChars))
            break;

        if (isLegalChar(currentChar))
        {
            charsRead++;
            if (charsRead >= bufferSize)
            {
                bufferSize = 2 * bufferSize;
                buffer = resizeCString(buffer, bufferSize);
            }

            if (buffer != NULL)
                buffer[charsRead - 1] = (char)currentChar;
            else
                break;   
        }
    }

    if (buffer != NULL) 
        buffer[charsRead] = '\0';

    return buffer;
}

char** tokenizeString(char* string, char* delimiter, int& tokens)
{
    char** tokenArray = (char**)malloc(tokens * sizeof(char*));
    char* token = strtok(string, delimiter);
    tokens = 0;

    while (token != NULL)
    {
        tokenArray[tokens] = token;
        token = strtok(NULL, delimiter);
        tokens++;
    }

    return tokenArray;
}


