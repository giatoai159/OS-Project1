#include "libraries.h"

void showHistory(char** cmdHistory, int numHistory)
{
    for (int i = 0; i < numHistory; i++)
    {
        printf("%d. %s", i, cmdHistory[i]);
        printf("\n");
    }
}

char** appendHistory(char* line, int* numHistory)
{
    char** cmdHistory;
    char* duplicate = strdup((const char*)line);
    if (cmdHistory == NULL)
        cmdHistory = (char**)malloc(HISTORY_SIZE * sizeof(char*));
    else if (*numHistory == HISTORY_SIZE)
    {
        free(cmdHistory);
        printf("RESETTING HISTORY...\n");
        cmdHistory = (char**)malloc(HISTORY_SIZE * sizeof(char*));
        *numHistory = 0;
    }
    if (cmdHistory == NULL)
        fprintf(stderr, "Allocation error :HISTORY");
    cmdHistory[*numHistory] = duplicate;
    (*numHistory)++;
    return cmdHistory;
}

void freeHistory(char** cmdHistory, int numHistory)
{
    for (int i = 0; i < numHistory; i++)
        free(cmdHistory[i]);
    //free(cmdHistory);
}
