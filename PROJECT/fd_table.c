#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include "fd_table.h"

void display_fd_table()
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc/self/fd");

    if (dir == NULL)
    {
        perror("Error opening /proc/self/fd");
        return;
    }

    printf("\n========================================\n");
    printf("       ACTIVE FILE DESCRIPTORS\n");
    printf("========================================\n");
    printf("FD\tTARGET\n");
    printf("----------------------------------------\n");

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] >= '0' && entry->d_name[0] <= '9')
        {
            char path[512];
            char target[256];

            snprintf(path, sizeof(path),
                     "/proc/self/fd/%s", entry->d_name);

            ssize_t length = readlink(path, target, sizeof(target) - 1);

            if (length != -1)
            {
                target[length] = '\0';
                printf("%s\t%s\n", entry->d_name, target);
            }
        }
    }

    printf("----------------------------------------\n");

    closedir(dir);
}
