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
bool exec(char* line);
bool launch(char* line, char** cmdHistory, int numHistory);
// BUILT-IN COMMANDS
bool normalHandling(char* line);
bool cdHandling(char* path);
bool handlingRedirectionOutput(char* line);
bool handlingRedirectionInput(char* line);
// void childSignalHandler(int signum); // FIX
// bool ampersandHandling(char* line); // FIX
// UTILITIES
char* clearWhiteSpaces(char* str);
void readLine(char* line);
int checkState(char* line);
char **splitCommand(char* line);
char **splitPath(char* path);
int char2int(const char* ch);
char** splitLine(char* line);
// HISTORY
void showHistory(char** cmdHistory, int numHistory);
char** appendHistory(char* line, int* numHistory);
void freeHistory(char** cmdHistory, int numHistory);
