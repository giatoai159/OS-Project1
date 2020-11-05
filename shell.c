#include "libraries.h"

bool exec(char* line,char** cmdHistory, int numHistory)
{
    int state = checkState(line);
    if (state == 0)
        return normalHandling(line);
    //else if (state == 2)
        //return ampersand_handling(line);
    //else if (state == 3)
        //return pipe_handling(line);
    //else if (state == 4)
        //return handling_redirection_output(line);
    //else return handling_redirection_input(line);
    return 1;
}

bool launch(char* line, char** cmdHistory, int numHistory)
{
    char* buildin_commands[] = {"cd","exit","history","help"};
    char* duplicate = strdup((const char*)line);
    char* temp = strtok_r(duplicate, " ", &duplicate);
    if(strcmp(temp,buildin_commands[0]) == 0) // cd handling
    {
        //char* first = temp;
        char* path = duplicate;
        return cdHandling(path);
    }
    else if(strcmp(temp,buildin_commands[1]) == 0) // exit handling
        {
            printf("Exiting shell...");
            return 0;
        }
    else if(strcmp(temp,buildin_commands[2]) == 0) // history handling
        {
            showHistory(cmdHistory, numHistory);
            return 1;
        }
    else return exec(line, cmdHistory, numHistory);
}