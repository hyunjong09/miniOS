#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "system.h"
#include "common.h"

void print_minios(char* str);

int main() {
    print_minios("[MiniOS SSU] Hello, World!");

    char *input;

    while(1) {
        pritnf("[SSU OS 8팀] :");
        // readline을 사용하여 입력 받기
        input = readline("커맨드를 입력하세요(종료:exit) : ");
        if(!strcmp(av[0], "cd"))
        {
            cmd_cd(ac, av);
        }
        // ls
        else if(!strcmp(av[0], "ls"))
        {
            cmd_ls(ac, av);
        }
        // cp
        else if(!strcmp(av[0], "cp"))
        {
            cmd_cp(ac, av);
        }
        // rm
        else if(!strcmp(av[0], "rm"))
        {
            cmd_rm(ac, av);
        }
        // mv
        else if(!strcmp(av[0], "mv"))
        {
            cmd_mv(ac, av);
        }
        // mkdir
        else if(!strcmp(av[0], "mkdir"))
        {
            cmd_mkdir(ac, av);
        }
        // rmdir
        else if(!strcmp(av[0], "rmdir"))
        {
            cmd_rmdir(ac, av);
        }
        // cat
        else if(!strcmp(av[0], "cat"))
        {
            cmd_cat(ac, av);
        }
        // exit
        else if(!strcmp(av[0], "exit"))
        {
            printf("mini Shell commend exit...");
            cmd_exit();
        }

        else if (strcmp(input,"minisystem") == 0){//fsadf
                minisystem();
        }
        else system(input);
    }

    // 메모리 해제합니다..jgh
    free(input);
    print_minios("[MiniOS SSU] MiniOS Shutdown........");

    return(1);
}

void print_minios(char* str) {
        printf("%s\n",str);
}
