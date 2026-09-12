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

bool isEquals(char* token) { if (strcmp(token, "=") == 0) { return true; } return false; }
bool isPlus(char* token) { if (strcmp(token, "+") == 0) { return true; } return false; }
bool isPlusEquals(char* token) { if (strcmp(token, "+=") == 0) { return true; } return false; }
bool isNegative(char* token) { if (strcmp(token, "-") == 0) { return true; } return false; }
bool isNegativeEquals(char* token) { if (strcmp(token, "-=") == 0) { return true; } return false; }
bool isLessThan(char* token) { if (strcmp(token, "<") == 0) { return true; } return false; }
bool isLessThanAndEquals(char* token) { if (strcmp(token, "<=") == 0) { return true; } return false; }
bool isMoreThan(char* token) { if (strcmp(token, ">") == 0) { return true; } return false; }
bool isMoreThanAndEquals(char* token) { if (strcmp(token, ">=") == 0) { return true; } return false; }
bool isTimes(char* token) { if (strcmp(token, "*") == 0) { return true; } return false; }
bool isTimesEquals(char* token) { if (strcmp(token, "*=") == 0) { return true; } return false; }
bool isDivide(char* token) { if (strcmp(token, "/") == 0) { return true; } return false; }
bool isDivideEquals(char* token) { if (strcmp(token, "/=") == 0) { return true; } return false; }
bool isEqualEqual(char* token) { if (strcmp(token, "==") == 0) { return true; } return false; }
bool isNotEqual(char* token) { if (strcmp(token, "!=") == 0) { return true; } return false; }
bool isAnd(char* token) { if (strcmp(token, "&") == 0) { return true; } return false; }
bool isNot(char* token) { if (strcmp(token, "!") == 0) { return true; } return false; }
bool isOr(char* token) { if (strcmp(token, "|") == 0) { return true; } return false; }
// Identify operators.

bool isLeftParenthesis(char* token) { if (strcmp(token, "(") == 0) { return true; } return false; }
bool isRightParenthesis(char* token) { if (strcmp(token, ")") == 0) { return true; } return false; }
bool isLeftCurlyBracket(char* token) { if (strcmp(token, "{") == 0) { return true; } return false; }
bool isRightCurlyBracket(char* token) { if (strcmp(token, "}") == 0) { return true; } return false; }
bool isLeftSquareBracket(char* token) { if (strcmp(token, "[") == 0) { return true; } return false; }
bool isRightSquareBracket(char* token) { if (strcmp(token, "]") == 0) { return true; } return false; }
bool isComma(char* token) { if (strcmp(token, ",") == 0) { return true; } return false; }
bool isSemicolon(char* token) { if (strcmp(token, ";") == 0) { return true; } return false; }
bool isPeriod(char* token) { if (strcmp(token, ".") == 0) { return true; } return false; }
bool isColon(char* token) { if (strcmp(token, ":") == 0) { return true; } return false; }
// Identify delimiters.

bool isString(char* token)
{
    if (token[0] == '"' && token[strlen(token) - 1] == '"') { return true; } return false;
}
bool isInt(char* token)
{
    for (int i = 0; i < strlen(token); i++) { if (!isdigit(token[i])) { return false; } } return true;
}
bool isBoolean(char* token)
{
    if (strcmp(token, "true") == 0 || strcmp(token, "false") == 0) { return true; } return false;
}
// Identify strings, numbers, and booleans.

bool nextCharMatchesTypeofToken(char* token, int currentTokenIndex, char* lexingString, int currentReadingIndex)
{
    char* tempQueryString = ("%s", token);
    tempQueryString[currentTokenIndex] = lexingString[currentReadingIndex];

    if (isOperator(token)) { if (isOperator(tempQueryString)) { return true; } }
    else if (isInt(token)) { if (isOperator(tempQueryString)) { return true; } }
    else { return false; }
}
// Check if extending operator & integer token values is possible.

void lexicalAnalysis(char* lexingString)
{
    int currentReadingIndex = 0;

    while (currentReadingIndex < strlen(lexingString))
    {
        char* token = ""; int currentTokenIndex = 0;
        token[currentTokenIndex] = lexingString[currentReadingIndex];


    }
}
// Lexical analysis for an inputted string.