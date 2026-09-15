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
#include "console_setup.h"    // Console setup header file.
#include "parser.h"           // Parser header file for turning instructions into mapped assignments.

char* readFile(char* path)
{
    FILE* file = fopen(path, "rb"); if (file == NULL) { return NULL; }
    fseek(file, 0, SEEK_END); long size = ftell(file); rewind(file);
    char* input = malloc(size + 1); fread(input, 1, size, file); input[size] = '\0';
    fclose(file);
    return input;
}
// Read a files contents by inputted path. Outputs what's in the file as a string.

int main(void)
{
    setupConsoleWindow(1366/2.5, 768/2.5, 800, 500);

    char path[256]; printf("File path: "); fgets(path, sizeof(path), stdin); path[strcspn(path, "\n")] = '\0';
    char* input = readFile(path);
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // Input source file location to interpret.

    struct ParsedAssignments Assignments = ParseInstructionsIntoAssignments(input);
    for (int i = 0; i < Assignments.count; i++)
    {
        printf("Assignment %d:\n", i);
        for (int i2 = 0; i2 < Assignments.InvididualAssignments[i].count; i2++)
        {
            printf("    %s: %s\n", Assignments.InvididualAssignments[i].Tokens[i2].type, Assignments.InvididualAssignments[i].Tokens[i2].value);
        }
    }
    // Parse source file contents.

    while (1) {}; return 0;
}
// Initialization.