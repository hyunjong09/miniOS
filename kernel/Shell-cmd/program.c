//  kernel 소스코드 system.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

// 프로그램 오류 발생 시 
void fatal(char *message)
{
	fprintf(stderr, "Error: %s\n", message);
	exit(1);
}
// 시스템 호출 오류
void syserr(char *message)
{
	fprintf(stderr, "Error: %s (%d", message, errno);
	exit(1);
}
// 프로세스 종료까지 대기
void waitfor(int pid)
{
	int wpid, status;

	while ((wpid = wait(&status)) != pid && wpid != ERROR);
}
// 터미널 프롬포트 출력
void print_prompt()
{
	char *ps;
	char *index;
	if((ps = (char*)getenv("PS2")) != NULL)
	{
		while(*ps != '\0')
		{
			if(*ps == '\\')
			{
				ps++;

				if(*ps == 'u')
				{
					printf("%s", getenv("USER"));
				}
				
				else if(*ps == 'h')
				{
					printf("%s", getenv("HOSTNAME"));
				}
				
				
				else if(*ps == 'w')
				{
					printf("%s", get_current_dir_name());
				}
			}
			
			else
			{
				printf("%c", *ps);
				ps++;
			}
		}
	}
	
	else
	{
		printf(">> ");
	}
}
// 쉘 커맨드 함수
BOOLEAN shellcmd(int ac, char *av[], int sourcefd, int destfd)
{
	char *path;

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
		printf("minios Shell 커맨드 exit!!\n");
		cmd_exit();
	}
    else if (!strcmp(av[0], "minisystem"))
    {
        minisystem();
    }
	else if (!strcmp(av[0], "touch") == 0) {
        cmd_touch(ac, av);
    }
	else
	{
		return FALSE;
	}

	if (sourcefd != 0 || destfd != 1)
	{
		fprintf(stderr, "Ilegal redirection or pipeline.\n");
	}

	return TRUE;
}
