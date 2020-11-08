#include "library.h"

int redirection(char ** args, int numbersArgs, int* posRedirection)
{

    for (int i = 0; i < numbersArgs; i++) {
        if (strcmp(args[i], "<") == 0) {
            *posRedirection = i;
            return 1;
        }
        else if (strcmp(args[i], ">") == 0) {
            *posRedirection = i;
            return 2;
        }
    }

    *posRedirection = -1;
    return 0;
}

int parse(char * input, char ** args, int * numbersArgs)
{
    // Loại bỏ ký tự \n ở cuối chuỗi
    int i = 0;

    while (input[i] != '\n' && input[i] != '\0') {
        i++;
    }

    input[i] = '\0';
    
    // Dùng hàm strtok để cắt chuỗi thành các thành phần nhờ vào ký tự " " phân chia
    const char delim[2] = " ";
    char * token = strtok(input, delim);
    i = 0;

    while (token != NULL) {
        args[i] = token;
        token = strtok(NULL, delim);
        i++;
    }

    args[i] = NULL;

    // Gán số lượng tham số cho nubmerOfArgs
    *numbersArgs = i;
}
