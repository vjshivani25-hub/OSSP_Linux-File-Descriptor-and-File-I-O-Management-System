#include <stdio.h>
#include "file_io.h"
#include "fd_table.h"
#include "redirect.h"
#include "ipc.h"
#include "monitor.h"

int main()
{
    int choice;

    while (1)
    {
        printf("\n========================================\n");
        printf(" LINUX FILE DESCRIPTOR MANAGEMENT SYSTEM\n");
        printf("========================================\n");
        printf("1. File I/O Operations\n");
        printf("2. Display File Descriptor Table\n");
        printf("3. Duplicate File Descriptor\n");
        printf("4. fcntl() Descriptor Information\n");
        printf("5. Pipe + Fork IPC\n");
        printf("6. Check FD Limit\n");
        printf("7. Detect FD Leaks\n");
        printf("8. Redirect stdout\n");
        printf("0. Exit\n");
        printf("========================================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                file_io_demo();
                break;

            case 2:
                display_fd_table();
                break;

            case 3:
                duplicate_fd_demo();
                break;

            case 4:
                fcntl_demo();
                break;

            case 5:
                pipe_fork_demo();
                break;

            case 6:
                check_fd_limit();
                break;

            case 7:
                detect_fd_leaks();
                break;

            case 8:
                redirect_stdout_demo();
                break;

            case 0:
                printf("\nExiting program...\n");
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
