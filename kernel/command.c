// kernel 소스 코드
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include "common.h"

int check_arg(char *av[], const char *opt)
{
	int count = 0;

	while(*av != '\0')
	{
		if(!strcmp(av[count], opt))
		{
			return TRUE;
		}

		av++;
	}

	return FALSE;
}

void cmd_cd(int ac, char *av[])
{
	char *path;

	if(ac > 1)
	{
		path = av[1];
	}
	
	else if((path = (char*)getenv("HOME")) == NULL)
	{
		path = ".";
	}

	if(chdir(path) == ERROR)
	{
		fprintf(stderr, "%s: bad directory.\n", path);
	}
}
void cmd_exit()
{
	exit(1);
}

void cmd_ls(int ac, char *av[])
{
	DIR *dp;
	struct dirent *entry;
	char *path;
	int count;
	int opt_a;
	int opt_l;

	if(ac < 2)
	{
		path = ".";
	}
	
	else
	{
		path = av[1];
	}

	if((dp = opendir(path)) == NULL)
	{
		fprintf(stderr, "Can't open directory: %s", av[1]);
		return;
	}

	opt_a = check_arg(av, "-a");
	opt_l = check_arg(av, "-l");

	count = 0;

	while((entry = readdir(dp)) != NULL)
	{
		if(!opt_a)
		{
			if(entry->d_name[0] == '.')
			{
				continue;
			}
		}
		
		
		printf("%s\t", entry->d_name);

		if(opt_l)
		{
			printf("\n");
		}
		
		else
		{
			if(count > 3)
			{
				printf("\n");
				count = 0;
			}
			else
			{
				count++;
			}
		}
	}

	closedir(dp);
	printf("\n");
}
