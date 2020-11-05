#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LENGTH 100
#define TOKEN_BUFFER 64
#define HISTORY_SIZE 100

// SHELL
bool exec(char* line,char** cmdHistory, int numHistory);
bool launch(char* line, char** cmdHistory, int numHistory);
// BUILT-IN COMMANDS
bool normalHandling(char* line);
bool cdHandling(char *path);
// UTILITIES
char* clearWhiteSpaces(char* str);
void readLine(char* line);
int checkState(char* line);
char **splitCommand(char* line);
char **splitPath(char* path);
int char2int(const char* ch);
// HISTORY
void showHistory(char** cmdHistory, int numHistory);
char** appendHistory(char* line, int* numHistory);
void freeHistory(char** cmdHistory, int numHistory);
