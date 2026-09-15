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
#include "lexer.h"      // Lexical analysis header file
#include "grammar.h"    // Language grammar / available syntax header file

struct ParsedAssignments
{
    struct AnalyzedInstructions* InvididualAssignments;
    int count;
};
struct CallbackReturn
{
    int currentInstructionIndex;
    struct AnalyzedInstructions Assignment;
    struct Token currentToken;
};

struct CallbackReturn printCallback
(
    struct Token currentToken,
    int currentInstructionIndex,
    struct AnalyzedInstructions LexerInstructions,
    struct AnalyzedInstructions Assignment
)
{
    currentToken = LexerInstructions.Tokens[currentInstructionIndex]; currentInstructionIndex++;
    Assignment.Tokens[Assignment.count] = currentToken; Assignment.count++;
    if (strcmp(currentToken.value, "(") != 0)
    {
        printf("Must initialize print with the left parenthesis delimiter.\n");
        return (struct CallbackReturn){0};
    }
    // Initialized print with delimiter.

    while (true)
    {
        currentToken = LexerInstructions.Tokens[currentInstructionIndex]; currentInstructionIndex++;
        Assignment.Tokens[Assignment.count] = currentToken; Assignment.count++;
        if (strcmp(currentToken.type, "Keyword") == 0)
        {
            printf("Cannot print a keyword.\n");
            return (struct CallbackReturn){0};
        }
        else if (strcmp(currentToken.type, "Operator") == 0)
        {
            printf("Cannot print an operator.\n");
            return (struct CallbackReturn){0};
        }
        else if (strcmp(currentToken.type, "Delimiter") == 0)
        {
            printf("Cannot print an delimiter.\n");
            return (struct CallbackReturn){0};
        }
        // Ensure wrong types cannot be printed.

        currentToken = LexerInstructions.Tokens[currentInstructionIndex]; currentInstructionIndex++;
        Assignment.Tokens[Assignment.count] = currentToken; Assignment.count++;
        if (strcmp(currentToken.value, ",") == 0) { continue; }
        else if (strcmp(currentToken.value, ")") == 0) { break; }
        else
        {
            printf("Expected a comma or right parenthesis after print value.\n");
            return (struct CallbackReturn){0};
        }
        // Repeat if there are more tokens to read, elseif the current token is a delimiter then break.
    }
    return (struct CallbackReturn){
        .Assignment = Assignment,
        .currentInstructionIndex = currentInstructionIndex,
        .currentToken = currentToken
    };
}
// Keyword callbacks.

struct ParsedAssignments ParseInstructionsIntoAssignments(char* input)
{
    struct ParsedAssignments Assignments = {
        .InvididualAssignments = calloc(256, sizeof(struct AnalyzedInstructions)),
        .count = 0
    };
    int currentAssignmentIndex = 0;

    struct AnalyzedInstructions LexerInstructions = lexicalAnalysis(input);
    int currentInstructionIndex = 0;

    while (currentInstructionIndex < LexerInstructions.count)
    {
        struct AnalyzedInstructions Assignment = {
            .Tokens = calloc(256, sizeof(struct Token)),
            .count = 0
        };

        struct Token currentToken = LexerInstructions.Tokens[currentInstructionIndex]; currentInstructionIndex++;
        Assignment.Tokens[0] = currentToken; Assignment.count++;
        if (strcmp(currentToken.type, "Identifier") == 0)
        {
            currentToken = LexerInstructions.Tokens[currentInstructionIndex]; currentInstructionIndex++;
            Assignment.Tokens[Assignment.count] = currentToken; Assignment.count++;
            if (strcmp(currentToken.type, "Operator") != 0)
            {
                printf("Identifier used as first instruction without an operator after.\n");
                break;
            }
            // Operator assured after identifier & added to assignment instructions.

            currentToken = LexerInstructions.Tokens[currentInstructionIndex]; currentInstructionIndex++;
            Assignment.Tokens[Assignment.count] = currentToken; Assignment.count++;
            if
            (
                strstr(currentToken.value, "+")
                || strstr(currentToken.value, "-")
                || strstr(currentToken.value, "*")
                || strstr(currentToken.value, "/")
                || strstr(currentToken.value, "%")
                || strstr(currentToken.value, "<")
                || strstr(currentToken.value, ">")
            )
            {
                currentToken = LexerInstructions.Tokens[currentInstructionIndex]; currentInstructionIndex++;
                Assignment.Tokens[Assignment.count] = currentToken; Assignment.count++;
                if (strcmp(currentToken.type, "Integer") != 0 && strcmp(currentToken.type, "Identifer") != 0)
                {
                    printf("Must use an integer or identifier after a number type operator.\n");
                    break;
                }
            }
            // Assure integer or identifier after a number type operator.
        }
        else if (strcmp(currentToken.type, "Keyword") == 0)
        {
            if (strcmp(currentToken.value, "print") == 0)
            {
                struct CallbackReturn CallbackReturn = printCallback(
                    currentToken,
                    currentInstructionIndex,
                    LexerInstructions,
                    Assignment
                );
                currentInstructionIndex = CallbackReturn.currentInstructionIndex;
                Assignment = CallbackReturn.Assignment; currentToken = CallbackReturn.currentToken;
            }
            // Handle different keywords.
        }

        Assignments.InvididualAssignments[currentAssignmentIndex] = Assignment; currentAssignmentIndex++; Assignments.count++;
    }
    return Assignments;
}
// Token-grouping parser.