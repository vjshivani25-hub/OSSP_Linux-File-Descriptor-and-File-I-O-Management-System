#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "file_io.h"

void file_io_demo()
{
    int fd;
    char buffer[100];

    // Open or create the file
    fd = open("sample.txt", O_CREAT | O_RDWR, 0644);

    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }

    printf("\nFile opened successfully!\n");
    printf("File Descriptor: %d\n", fd);

    // Write data to file
    char *message = "Hello from Linux File Descriptor Management System!\n";

    write(fd, message, strlen(message));

    printf("Data written successfully!\n");

    // Move file pointer back to beginning
    lseek(fd, 0, SEEK_SET);

    // Read data from file
    int bytes = read(fd, buffer, sizeof(buffer) - 1);

    if (bytes > 0)
    {
        buffer[bytes] = '\0';
        printf("Data read from file:\n%s", buffer);
    }

    // Close file
    close(fd);

    printf("File Descriptor %d closed successfully!\n", fd);
}
