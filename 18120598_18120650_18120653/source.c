#include "library.h"


int main(int argc, char* argv[])
{
    char input[MAX_LENGTH];
    char copyOfInput[MAX_LENGTH];
    char directory[MAX_LENGTH];
    char * args[MAX_LENGTH] = {NULL}; // command line arguments

    // Check concurently
    int numbersArgs, signalConcurrent = 0; 

    // Define process
    int should_run = 1; // flag to determine when to exit program
    pid_t pid; 
    int status;

    int signalRedirection = 0; // 1 for input, 2 for output.
    int posRedirection;

    // Pipe
    int checkPipe = 0;
    char* firstCmd_pipe = NULL;
    char* secondCmd_pipe = NULL;

    // Define history
    char history[MAX_LENGTH];
    int IsHistoryFull = 0;
    int file_desc;

    while (should_run)  {
        printf("osh>");
        // Read input
        fgets(input, MAX_LENGTH, stdin);
        // Copy input
        strcpy(copyOfInput, input);

        if (strchr(copyOfInput, '|') != NULL) {
            const char delim[] = "|";
            firstCmd_pipe = strtok(copyOfInput, delim);
            secondCmd_pipe = strtok(NULL, delim);
            checkPipe = 1;
        }
        
        // String to arguments
        parse(copyOfInput, args, &numbersArgs);
        signalRedirection = redirection(args, numbersArgs, &posRedirection);

        if (strcmp(args[0], "cd") == 0) {
            if (chdir(args[1]) < 0)
                perror(args[1]);
            continue;
        }

        if (strcmp(args[0], "exit") == 0 && numbersArgs == 1) {
            should_run = 0;
            continue;
        }
        else if (strcmp(args[0], "!!") == 0 && numbersArgs == 1) {
            // Check buffer
            if (IsHistoryFull == 1) {
                printf("The command in history is : %s\n", history);
                strcpy(copyOfInput, history);


                if (strchr(copyOfInput, '|') != NULL) {
                    const char delim[] = "|";
                    firstCmd_pipe = strtok(copyOfInput, delim);
                    secondCmd_pipe = strtok(NULL, delim);
                    checkPipe = 1;
                }

                parse(copyOfInput, args, &numbersArgs);
            }
            else {
                printf("No command in history\n");
                continue;
            }
        }
        // Save into history
        strcpy(history, input);

        if (IsHistoryFull == 0) {
            IsHistoryFull = 1;
        }

        if (strcmp(args[numbersArgs - 1], "&") == 0) {
            signalConcurrent = 1;
            args[numbersArgs - 1] = NULL;
        }
        
        // Create child process
        pid = fork();

        if (pid == -1) { // Initialization failed
            printf("Can't create child process\n");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) { // Initialization success
            int newPipe[2];

            // Create new process, execute command line
            pid_t pid1;

            // Have Redirection
            if (signalRedirection != 0) {
                int flag, newfd;

                // Check Redirect
                if (signalRedirection == 1) { // redirect input
                    flag = O_RDONLY | O_CREAT;
                    newfd = 0;
                }
                else if (signalRedirection == 2) { // redirect output
                    flag = O_WRONLY | O_CREAT;
                    newfd = 1;
                }

                // Open file for redirection
                int fd = open(args[posRedirection + 1], flag);

                if (fd < 0) { // End this process
                    perror("Couldn't open file for redirection\n");
                    exit(EXIT_FAILURE);
                }

                dup2(fd, newfd);

                // Close file descriptor
                close(fd);

                // Set args at > or < equal NULL 
                args[posRedirection] = NULL;
            }

            if (checkPipe == 1) {

                if (pipe(newPipe) < 0) {
                    exit(EXIT_FAILURE);
                }

                pid1 = fork();

                if (pid1 == 0) { // Child process
                    // parse cmd2
                    parse(firstCmd_pipe, args, &numbersArgs);
                    close(newPipe[0]);
                    dup2(newPipe[1],1);

                    // Execute cmd printf
                    execvp(args[0], args);
                    perror("cant exec cmd1");
                }
                else { // Father process
                    // Close newPipe[0] avoid lag
                    close(newPipe[1]);

                    // Copy pipe of stdout with pipe of newPipe
                    dup2(newPipe[0],0);

                    parse(secondCmd_pipe, args, &numbersArgs);
                }
            }
            
            if (execvp(args[0], args) < 0) {
                perror(args[0]);
                exit(EXIT_FAILURE);
            }
          
            exit(0);
        }
        else {
            // Success create father process
            if (signalConcurrent == 0) {
                // Haven't signal concurrent, father process, wait child process
                if (waitpid(pid, &status, 0) > 0) { 
              
                    if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                        // printf("program execution successfull\n");
                    }
                    else if (WIFEXITED(status) && WEXITSTATUS(status)) { 
                        if (WEXITSTATUS(status) == 127) { 
                            // execv failed 
                            printf("execv failed\n"); 
                        } 
                        else {
                            printf("program terminated normally,"
                            " but returned a non-zero status\n");       
                        }          
                    } 
                    else {
                        printf("program didn't terminate normally\n");
                    }             
                }  
                else { 
                    // waitpid() failed 
                    printf("waitpid() failed\n"); 
                } 
            }
            else {
                // Father process exec concurrent with child process
                signalConcurrent = 0;
            }

            if (checkPipe == 1) {
                checkPipe = 0;
            }

        }
    }

    printf("End!!!\n");

    return 0;
}