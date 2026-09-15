#include <stdio.h>      // printf, scanf, FILE, fopen, etc.
#include <stdlib.h>     // malloc, free, rand, exit, system, etc.
#include <string.h>     // strcpy, strlen, strcmp, memcpy, etc.
#include <stdbool.h>    // bool, true, false
#include <stdint.h>     // uint8_t, int32_t, uint64_t, etc.
#include <stddef.h>     // size_t, NULL, ptrdiff_t
#include <ctype.h>      // isalpha, isdigit, toupper, tolower, etc.
#include <math.h>       // sqrt, pow, sin, cos, etc.
#include <time.h>       // time, clock, srand, etc.
#include <assert.h>     // assert()
#include <limits.h>     // INT_MAX, INT_MIN, etc.
#include <float.h>      // FLT_MAX, DBL_MAX, etc.
#include <errno.h>      // errno
#include <windows.h>    // Windows API
#include <conio.h>      // _getch(), _kbhit(), etc.
#include "grammar.h"    // Language grammar / available syntax header file.

struct Token
{
    char* value;
    char* type;
};
struct AnalyzedInstructions
{
    struct Token *Tokens;
    int count;
};

bool isOperator(char* input)
{
    for (int i = 0; i < sizeof(Operators) / sizeof(Operators[0]); i++)
    {
        if (strcmp(input, Operators[i]) == 0) { return true; }
    }
    return false;
}
bool isDelimiter(char* input)
{
    for (int i = 0; i < sizeof(Delimiters) / sizeof(Delimiters[0]); i++)
    {
        if (strcmp(input, Delimiters[i]) == 0) { return true; }
    }
    return false;
}
bool isKeyword(char* input)
{
    for (int i = 0; i < sizeof(Keywords) / sizeof(Keywords[0]); i++)
    {
        if (strcmp(input, Keywords[i]) == 0) { return true; }
    }
    return false;
}
// Identify keywords, operators, and delimiters.

bool isString(char* input)
{
    if (strlen(input) < 2) { return false; }
    if (input[0] == '"' && input[strlen(input) - 1] == '"') { return true; }
    return false;
}
bool isInt(char* input)
{
    if (strlen(input) == 0) { return false; }
    for (int i = 0; i < strlen(input); i++) { if (!isdigit(input[i])) { return false; } }
    return true;
}
bool isBoolean(char* input)
{
    if (strcmp(input, "true") == 0 || strcmp(input, "false") == 0) { return true; }
    return false;
}
bool isIdentifier(char* input)
{
    if (!isalpha(input[0]) && input[0] != '_') { return false; }
    for (int i = 1; i < strlen(input); i++) { if (!isalnum(input[i]) && input[i] != '_') { return false; } }
    return true;
}
// Identify strings, numbers, and booleans.

bool nextCharMatchesTypeofToken(char* input, int currentTokenIndex, char* lexingString, int currentReadingIndex )
{
    if (lexingString[currentReadingIndex] == '\0') { return false; }
    char queryString[256]; strcpy(queryString, input);
    queryString[currentTokenIndex] = lexingString[currentReadingIndex];
    queryString[currentTokenIndex + 1] = '\0';
    if (isOperator(input)) { if (isOperator(queryString)) { return true; } }
    else if (isInt(input)) { if (isInt(queryString)) { return true; } }
    else if (isIdentifier(input)) { if (isIdentifier(queryString)) { return true; } }
    return false;
}
// Check if extending operator & integer token values is possible.

struct AnalyzedInstructions lexicalAnalysis(char* input)
{
    int analyzingLength = strlen(input);
    int currentReadingIndex = 0;

    struct AnalyzedInstructions AnalyzedInstructions = {
        .Tokens = calloc(256, sizeof(*AnalyzedInstructions.Tokens)),
        .count = 0
    };
    int currentAnalyzingIndex = 0;

    while (currentReadingIndex < analyzingLength)
    {
        char* token = malloc(sizeof(char) * 256);
        int currentTokenIndex = 0; token[0] = '\0';

        while
        (
            !isOperator(token)
            && !isDelimiter(token)
            && !isKeyword(token)
            && !isString(token)
            && !isBoolean(token)
            && !isInt(token)
            && !isIdentifier(token)
            && currentReadingIndex < analyzingLength
            && currentTokenIndex < 256
        )
        {
            token[currentTokenIndex] = input[currentReadingIndex];
            currentReadingIndex++; currentTokenIndex++; token[currentTokenIndex] = '\0';
            while (nextCharMatchesTypeofToken(token, currentTokenIndex, input, currentReadingIndex))
            {
                token[currentTokenIndex] = input[currentReadingIndex];
                currentReadingIndex++; currentTokenIndex++; token[currentTokenIndex] = '\0';
            }
            while (input[currentReadingIndex] == ' ' || input[currentReadingIndex] == '\n' || input[currentReadingIndex] == '\r') { currentReadingIndex++; }
        }
        // Read tokens fully.

        bool addToInstructions = false;
        char* tokenType = NULL;
        if (isOperator(token))
        {
            addToInstructions = true;
            tokenType = "Operator";
        }
        else if (isDelimiter(token))
        {
            addToInstructions = true;
            tokenType = "Delimiter";
        }
        else if (isKeyword(token))
        {
            addToInstructions = true;
            tokenType = "Keyword";
        }
        else if (isInt(token))
        {
            addToInstructions = true;
            tokenType = "Integer";
        }
        else if (isString(token))
        {
            addToInstructions = true;
            tokenType = "String";
        }
        else if (isBoolean(token))
        {
            addToInstructions = true;
            tokenType = "Boolean";
        }
        else if (isIdentifier(token))
        {
            addToInstructions = true;
            tokenType = "Identifier";
        }
        // Verify the token is a valid token & should be added to analyzed instructions.

        if (addToInstructions)
        {
            AnalyzedInstructions.Tokens[currentAnalyzingIndex].type = tokenType;
            AnalyzedInstructions.Tokens[currentAnalyzingIndex].value = token;
            currentAnalyzingIndex++; AnalyzedInstructions.count++;
        }
        // Add token & token type to analyzed instructions.
    }
    return AnalyzedInstructions;
}
// Lexical analysis for an inputted string.