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
#include "console_setup.h"    // Console setup header file
#include "lexer.h"            // Lexical Analysis header file

int main(void)
{
    setupConsoleWindow(1366/2.5, 768/2.5, 800, 500);

    //struct AnalyzedInstructions AnalyzedInstructions = lexicalAnalysis("122 + 2 * (3 - 4) / 5");
    //for (int i = 0; i < AnalyzedInstructions.count; i++)
    //{
       //printf("token type: %s, token: %s\n", AnalyzedInstructions.Tokens[i].type, AnalyzedInstructions.Tokens[i].value);
    //}

    while (1) {}; return 0;
}
// Initialization.