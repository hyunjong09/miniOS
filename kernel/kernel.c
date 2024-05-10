#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

#include "system.h"
#include "common.h"


int main() {
    int pid, fd;
	SYMBOL term;

    printf("[MiniOS SSU] Hello, World!\n");
    print_prompt();

    char *path;

    while(1) {
        printf("[SSU OS 8팀] (종료를 원하시면 exit를 입력해주세요.) :");
        // readline을 사용하여 입력 받기
        term = parse(&pid, FALSE, NULL);

        if (term != S_AMP && pid != 0)
		{
			waitfor(pid);
		}

		if (term == S_NL)
		{
			print_prompt();
		}

		for (fd=3; fd<MAXFD; fd++)
		{
			close(fd);
		}
    }
}