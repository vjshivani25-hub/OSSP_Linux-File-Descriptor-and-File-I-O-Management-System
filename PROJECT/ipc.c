#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "ipc.h"

void pipe_fork_demo()
{
    int pipe_fd[2];
    pid_t pid;
    char message[] = "Hello from Parent Process!";
    char buffer[100];

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe failed");
        return;
    }

    pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        return;
    }

    if (pid > 0)
    {
        close(pipe_fd[0]);

        printf("\n========================================\n");
        printf("          PIPE + FORK IPC DEMO\n");
        printf("========================================\n");

        printf("Parent PID: %d\n", getpid());
        printf("Child PID : %d\n", pid);

        write(pipe_fd[1], message, strlen(message) + 1);

        printf("Parent sent: %s\n", message);

        close(pipe_fd[1]);

        wait(NULL);

        printf("Parent process completed.\n");
    }
    else
    {
        close(pipe_fd[1]);

        read(pipe_fd[0], buffer, sizeof(buffer));

        printf("Child received: %s\n", buffer);

        close(pipe_fd[0]);

        printf("Child process completed.\n");

        exit(0);
    }
}
