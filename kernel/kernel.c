#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include "system.h"
#include "common.h"

void run_command_line_interface() {
    int pid, fd;
    SYMBOL term;

    printf("[MiniOS SSU] Hello, World!\n");
    print_prompt();

    char *path;

    while(1) {
        printf("[SSU OS 8팀] (종료를 원하시면 exit를 입력해주세요.) :");
        term = parse(&pid, FALSE, NULL);

        if (term != S_AMP && pid != 0) {
            waitfor(pid);
        }

        if (term == S_NL) {
            print_prompt();
        }

        for (fd = 3; fd < MAXFD; fd++) {
            close(fd);
        }
    }
}

int main(int argc, char **argv) {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        run_gtk_application(argc, argv);
    } else if (pid > 0) { // Parent process
        run_command_line_interface();
        wait(NULL); // Wait for the GTK application to finish
    } else {
        fprintf(stderr, "Failed to fork.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
