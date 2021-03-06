#include "libraries.h"

char* clearWhiteSpaces(char* str)
{
    while(str[0]== ' ' && str[0]!= '\0')
        str++;
    return str;
}

void readLine(char* line)
{
    while (fgets(line, MAX_LENGTH, stdin) == NULL)
        fflush(stdin);
    line[strcspn(line, "\n")] = '\0';
}

int checkState(char* line)
{
    /*
    nothing = 0
    & = 1 
    | = 2 
    > = 3 
    < = 4
    */
    int length = strlen(line);
    
    if (line[length - 1] == '&')
        return 1;
    else
    {
        const char* temp = strchr(line, '|');
        if (temp != NULL)
            return 2;
        temp = strchr(line, '>');
        if (temp != NULL)
            return 3;
        temp = strchr(line, '<');
        if (temp != NULL)
            return 4;
    }
    return 0;
}

char **splitCommand(char* line)
{
    const char* TOKEN_DELIM = " \"\t\r\n\a";
    int bufferSize = TOKEN_BUFFER;
    int position = 0;
    char **argv = (char**)malloc(bufferSize * sizeof(char*));
    char *arg;
    if (argv == NULL)
    {
        fprintf(stderr, "Allocation error.\n");
        exit(EXIT_FAILURE);
    }
    int checkQuotation = 0;
    if(line[0] == '\"')
        checkQuotation = 1;
    else arg = strtok_r(line, TOKEN_DELIM, &line);
    while (arg != NULL)
    {
        if (checkQuotation == 1)
        {
            memmove(line,line + 1, strlen(line));
            checkQuotation = 0;
            arg = strtok_r(line , "\"", &line);
        }
        argv[position] = arg;
        position++;
        if (position >= bufferSize)
        {
            bufferSize += TOKEN_BUFFER;
            argv = (char**)realloc(argv, bufferSize * sizeof(char*));
            if (argv == NULL)
            {
                fprintf(stderr, "Allocation error.\n");
                exit(EXIT_FAILURE);
            }
        }
        if (line[0] == '\"')
            checkQuotation = 1;
        else arg = strtok_r(line, TOKEN_DELIM, &line);
    }
    argv[position] = NULL;
    return argv;
}

char **splitPath(char* path)
{
    int bufferSize = TOKEN_BUFFER;
    int position = 0;
    char **argv = (char**)malloc(bufferSize * sizeof(char*));
    char *arg;
    if (argv == NULL)
    {
        fprintf(stderr, "Allocation error.\n");
        exit(EXIT_FAILURE);
    }
    int checkQuotation = 0;
    if(path[0] == '\"')
        checkQuotation = 1;
    else arg = strtok_r(path, "", &path);

    while (arg != NULL)
    {
        if (checkQuotation == 1)
        {
            memmove(path,path + 1, strlen(path));
            checkQuotation = 0;
            arg = strtok_r(path , "\"", &path);
        }
        argv[position] = arg;
        position++;
        if (position >= bufferSize)
        {
            bufferSize += TOKEN_BUFFER;
            argv = (char**)realloc(argv, bufferSize * sizeof(char*));
            if (argv == NULL)
            {
                fprintf(stderr, "Allocation error.\n");
                exit(EXIT_FAILURE);
            }
        }
        if (path[0] == '\"')
            checkQuotation = 1;
        else arg = strtok_r(path, "/", &path);
    }
    argv[position] = NULL;
    return argv;
}

int char2int(const char* ch)
{
    int temp = 0;
    for (int i = 0; i < strlen(ch); i++)
    {
        if ((ch[i] > '9') || (ch[i] < '0'))
            return -1;
        temp = temp * 10 + ch[i] - '0';
    }
    return temp;
}
char** splitLine(char* line)
{

	int buffsize = 64;
	int possition = 0;
	char** args = (char**)malloc(buffsize * sizeof(char*));
	char* arg;
	if (args == NULL)
	{
		fprintf(stderr, "Allocation error");
		printf("\n");
		exit(EXIT_FAILURE);
	}

	int check_quoration = 0;
	if (line[0] == '\"')
		check_quoration = 1;
	else
		arg = strtok_r(line, " \"\t\r\n\a" ,&line);
	while (arg != NULL)
	{
		if (check_quoration == 1)
		{
				memmove(line,line + 1,strlen(line));
				check_quoration = 0;
				arg = strtok_r(line,"\"",&line);
		}
		args[possition] = arg;
		possition++;	
		if (possition >= buffsize)
		{
			buffsize += 64;
			args = (char**)realloc(args, buffsize * sizeof(char*));
			if (args == NULL)
			{
				fprintf(stderr, "Allocation error");
				printf("\n");
				exit(EXIT_FAILURE);
			}
		}
		if (line[0] == '\"')
			check_quoration = 1;
		else
			arg = strtok_r(line, " \"\t\r\n\a" ,&line);
	}
	args[possition] = NULL;
	return args;
}