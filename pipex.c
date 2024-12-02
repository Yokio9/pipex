//< file1 cmd1 | cmd2 > file2

//		< infile ls -l | wc -l > outfile
//./pipex infile "ls -l" "wc -l" outfile

//		< infile grep a1 | wc -w > outfile
//./pipex infile "grep a1" "wc -w" outfile

//if argv[1] == "<"	-->	input = argv[2] else input = argv[1]
//access(input)

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int	i;
	char	full_path[256] = {0};

	i = 0;
	char **args = malloc((argc - 1) * sizeof(char *));
	while (argv[i + 1])
	{
		args[i] = strdup(argv[i + 1]);
		i++;
	}
	const char *path_list[] = {"/usr/local/bin/", "/usr/bin/", "/bin/", "/sbin/", "/usr/sbin/", NULL};
	i = 0;
	while(path_list[i])
	{
		memset(full_path, 0, 256);
		strcat(full_path, path_list[i++]);
		strcat(full_path, args[0]);
		execve(full_path, args, NULL);
	}
	printf("couldnt find command\n");
	return 0;
}
	//char *args[] = {"ls", "-l", NULL};

	//settings set target.run-args ls
	//frame variable