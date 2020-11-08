#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h> 
#include <errno.h>   
#include <sys/wait.h> 
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

//The maximum length command
#define MAX_LENGTH 80

int parse(char * input, char ** args, int * numbersArgs);
int redirection(char ** args, int numbersArgs, int* posRedirection);