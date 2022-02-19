#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>


int main()
{
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        exit(-1);
    }

    char input_num[50];
    scanf("%s", input_num);

    pid_t pid;
    pid = fork();

    if (pid < 0)            // error
    {
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if (pid == 0)      // child
    {
        close(pipe1[1]);

        char input_num[50];
        char reversed_num[50];
        read(pipe1[0], input_num, 50);


        for (int i = 0; i < strlen(input_num); ++i)
        {
            reversed_num[i] = input_num[strlen(input_num) - i - 1];
        }
        reversed_num[strlen(input_num)] = '\0';

        close(pipe1[0]);
        close(pipe2[0]);

        write(pipe2[1], reversed_num, strlen(reversed_num) + 1);
        close(pipe2[1]);

    }
    else                    // parent
    {
        char reversed_num[50];

        close(pipe1[0]);

        write(pipe1[1], input_num, strlen(input_num) + 1);
        close(pipe1[1]);

        wait(NULL);
        close(pipe2[1]);

        read(pipe2[0], reversed_num, 50);
        printf("%s\n%s\n", input_num, reversed_num);
        close(pipe2[0]);

        exit(0);
    }
}
