#include <stdio.h>
#include <dirent.h>
#include <sys/resource.h>
#include "monitor.h"

int count_open_fds()
{
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir("/proc/self/fd");

    if (dir == NULL)
    {
        perror("Error opening /proc/self/fd");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] >= '0' &&
            entry->d_name[0] <= '9')
        {
            count++;
        }
    }

    closedir(dir);

    return count;
}

void check_fd_limit()
{
    struct rlimit limit;
    int current_fds;
    double usage;

    if (getrlimit(RLIMIT_NOFILE, &limit) == -1)
    {
        perror("getrlimit failed");
        return;
    }

    current_fds = count_open_fds();

    if (current_fds == -1)
        return;

    usage = ((double)current_fds / limit.rlim_cur) * 100;

    printf("\n========================================\n");
    printf("       FILE DESCRIPTOR MONITOR\n");
    printf("========================================\n");
    printf("Current Open FDs : %d\n", current_fds);
    printf("FD Limit         : %lu\n",
           (unsigned long)limit.rlim_cur);
    printf("Usage            : %.2f%%\n", usage);

    if (usage >= 80.0)
        printf("Status           : WARNING - FD usage is high!\n");
    else
        printf("Status           : SAFE\n");

    printf("========================================\n");
}

void detect_fd_leaks()
{
    int current_fds;

    current_fds = count_open_fds();

    if (current_fds == -1)
        return;

    printf("\n========================================\n");
    printf("          FD LEAK DETECTION\n");
    printf("========================================\n");
    printf("Currently Open FDs: %d\n", current_fds);

    if (current_fds > 10)
        printf("Warning: High number of open descriptors detected.\n");
    else
        printf("No obvious file descriptor leak detected.\n");

    printf("========================================\n");
}
