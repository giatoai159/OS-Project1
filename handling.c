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
            if (chdir(argv[position]) != 0)
            {
                fprintf(stderr, "Can't find the path to %s.\n", argv[position]);
                return 1;
            }
            position++;
        }
    }
    return 1;
}
/*
void childSignalHandler(int signum)
{
		int childPid, childStatus;
    	childPid = waitpid(-1,&childStatus,WNOHANG);
}

bool ampersandHandling(char* line)
{
	line[strlen(line) - 1] = '\0';
    char** argv = splitCommand(line);
	signal(SIGCHLD,childSignalHandler);
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
        else
        {
            printf("DONE\n");
            exit(EXIT_SUCCESS);
        }
	}
	else
	{
        free(line);
		free(argv);
		return 1;
	}
}
*/
bool handlingRedirectionOutput(char* line)
{
	char* command = strtok_r(line,">",&line);
	int appendFlag = 0;
	if (line[0] == '>')
	{
		appendFlag = 1;
		line[0] = ' ';
	}
	char* fileName = clearWhiteSpaces(line);
	char* duplicateCommand = strdup((const char *)command);
	int save_stdout = dup(STDOUT_FILENO);
	pid_t pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "Can't create child process");
        return 1;
	}
	else if (pid == 0)
	{
		int fileDescriptor;
		if (appendFlag == 0)
			fileDescriptor = open(fileName,O_WRONLY | O_CREAT);
		else
			fileDescriptor = open(fileName,O_WRONLY | O_CREAT | O_APPEND);
		if (fileDescriptor < 0)
		{
			fprintf(stderr, "Can't create/open the file.\n");
			exit(EXIT_FAILURE);
		}
		dup2(fileDescriptor,STDOUT_FILENO);
		close(fileDescriptor);
		exec(command);
		exit(EXIT_SUCCESS);
	}
	else
	{
		dup2(save_stdout,STDOUT_FILENO);
		wait(NULL);
		return 1;
	}
	return 1;
}
bool handlingRedirectionInput(char* line)
{
	char* command = strtok_r(line,"<", &line);
	char* file_name = strtok_r(line," ", &line);
	char **argvs = splitLine(command);
	int save_stdin = dup(STDIN_FILENO);
	pid_t pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "Can't create child process");
		return 1;
	}
	else if (pid == 0)
	{
		int file_des = open(file_name,O_RDONLY);
		if (file_des < 0)
		{
			fprintf(stderr, "Can't create/open the file.\n");
			exit(EXIT_FAILURE);
		}
		dup2(file_des,STDIN_FILENO);
		execvp(argvs[0],argvs);
	}
	else
	{
		dup2(save_stdin,STDIN_FILENO);
		wait(NULL);
		free(argvs);
		return 1;
	}
	return 1;
}