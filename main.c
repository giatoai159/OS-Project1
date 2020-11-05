#include "libraries.h"

int main()
{   
    
    int should_run = 1;
    char line[MAX_LENGTH];
    char** cmdHistory = NULL;
    int numHistory = 0;
    // char* args[MAX_LENGTH];
    char currentWorkingDirectory[200];
    while(should_run)
    {
        fflush(stdout);
        getcwd(currentWorkingDirectory,200);
        printf("%s$ osh>", currentWorkingDirectory);
        readLine(line);
        if (line[0] == '!' && line[1] == '!')
        {
            if (char2int(line) >= numHistory - 1)
            {
                printf("No command available.\n");
                fflush(stdout);
                continue;
            }
            char* last_cmd = cmdHistory[numHistory-1];
            if (last_cmd != NULL)
            {
                strcpy(line, last_cmd);
                // printf("%s\n", last_cmd);
                fflush(stdout);
            }
        }
        cmdHistory = appendHistory(line, &numHistory);
        if(strcmp(line,"")==0) continue;
        should_run = launch(line, cmdHistory, numHistory);
    }
    freeHistory(cmdHistory, numHistory);

    printf("\n");
}