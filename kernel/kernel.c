#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "system.h"
#include "common.h"

void print_minios(char* str);

int main(int ac, char *av[], int sourcefd, int destfd) {
    print_minios("[MiniOS SSU] Hello, World!");

    char *path;

    while(1) {
        printf("[SSU OS 8팀] :");
        // readline을 사용하여 입력 받기
        av[0] = readline("커맨드를 입력하세요(종료:exit) : ");
        // cd
        if(!strcmp(av[0], "cd"))
        {
            cmd_cd(ac, av);
        }
        // ls
        else if(!strcmp(av[0], "ls"))
        {
            cmd_ls(ac, av);
        }
        else if(!strcmp(av[0], "exit"))
        {
            printf("mini Shell commend exit...");
            cmd_exit();
        }

        else if (strcmp(av[0],"minisystem") == 0){//fsadf
                minisystem();
        }
        else system(av[0]);
    }

    // 메모리 해제합니다..jgh
    free(av[0]);
    print_minios("[MiniOS SSU] MiniOS Shutdown........");

    return(1);
}

void print_minios(char* str) {
        printf("%s\n",str);
}
