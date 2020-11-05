#include "libraries.h"

bool normalHandling(char* line)
{
    char** argv = splitCommand(line);
    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Can't create child process");
        return 1;
    }
    else if (pid == 0)
    {
        if (execvp(argv[0], argv) < 0)
        {
            fprintf(stderr, "This command doesn't exist.\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(NULL);
        free(argv);
        return 1;
    }
    return 0;
}

bool cdHandling(char *path)
{
    if (path == NULL)
        fprintf(stderr, "Invalid Path.\n");
    else
    {
        path = clearWhiteSpaces(path);
        char** argv = splitPath(path);
        int position = 0;
        while(argv[position] != NULL)
        {
            if (chdir(argv[position]) != NULL)
            {
                fprintf(stderr, "Can't find the path to %s.\n", argv[position]);
                return 1;
            }
            position++;
        }
    }
    return 1;
}