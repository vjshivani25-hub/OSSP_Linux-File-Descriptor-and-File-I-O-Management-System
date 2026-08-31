#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "redirect.h"

void duplicate_fd_demo()
{
    int fd, new_fd;

    fd = open("sample.txt", O_RDWR);

    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }

    printf("\nOriginal File Descriptor: %d\n", fd);

    new_fd = dup(fd);

    if (new_fd == -1)
    {
        perror("dup failed");
        close(fd);
        return;
    }

    printf("Duplicated File Descriptor: %d\n", new_fd);

    write(new_fd, "\nData written using duplicated FD.\n", 34);

    printf("Data successfully written using duplicated FD.\n");

    close(new_fd);
    close(fd);

    printf("Both file descriptors closed successfully.\n");
}

void redirect_stdout_demo()
{
    int fd;
    int saved_stdout;

    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("Error opening output file");
        return;
    }

    saved_stdout = dup(STDOUT_FILENO);

    printf("\nRedirecting stdout to output.txt...\n");
    fflush(stdout);

    dup2(fd, STDOUT_FILENO);

    printf("This message is redirected to output.txt\n");
    fflush(stdout);

    dup2(saved_stdout, STDOUT_FILENO);

    close(saved_stdout);
    close(fd);

    printf("stdout restored to terminal.\n");
}
    
void fcntl_demo()
{
    int fd;
    int flags;

    fd = open("sample.txt", O_RDWR);

    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }

    printf("\n========================================\n");
    printf("          FCNTL DESCRIPTOR DEMO\n");
    printf("========================================\n");

    flags = fcntl(fd, F_GETFL);

    if (flags == -1)
    {
        perror("fcntl failed");
        close(fd);
        return;
    }

    printf("File Descriptor: %d\n", fd);

    if ((flags & O_ACCMODE) == O_RDWR)
        printf("Access Mode: Read + Write\n");
    else if ((flags & O_ACCMODE) == O_WRONLY)
        printf("Access Mode: Write Only\n");
    else
        printf("Access Mode: Read Only\n");

    printf("fcntl successfully retrieved descriptor flags.\n");

    close(fd);

    printf("File Descriptor closed successfully.\n");
}
