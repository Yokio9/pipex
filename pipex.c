//< file1 cmd1 | cmd2 > file2

//		< infile ls -l | wc -l > outfile
//./pipex infile "ls -l" "wc -l" outfile

//		< infile grep a1 | wc -w > outfile
//./pipex infile "grep a1" "wc -w" outfile

//if argv[1] == "<"	-->	input = argv[2] else input = argv[1]
//access(input)

#include "pipex.h"

char	**get_path(char *envp[])
{
	int		i;
	char	**split_path;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		if (strncmp("PATH=", envp[i], 5) == 0)
		{
			split_path = ft_split(envp[i] + 5, ':');
			i = -1;
			while (split_path[++i])
			{
				temp = split_path[i];
				split_path[i] = ft_strjoin(split_path[i], "/");
				free (temp);
			}
			return (split_path);
		}
		i++;
	}
	return (NULL);
}

int main(int argc, char *argv[], char *envp[])
{
	int	i;
	int	open1;
	int	infile;
	char	*full_path;
	char	**path_list;

	i = 0;
	if (argc < 2)					//CHANGE THIS TO argc != 5
		return (0);
	open1 = open(argv[1], O_RDONLY);
	if (open1 < 0)
	{
		printf("cant open file\n");
		return (1);
	}
	infile = dup2(open1, 0);
	if (infile == -1)
		return (1);
	char **args = calloc(argc, sizeof(char *));
	if (!args)
		exit(1);
	while (argv[i + 2])			//2 bc 1 for argv[0] and 1 for the file
	{
		args[i] = strdup(argv[i + 2]);
		if (!args[i])
		{
			while (i > 0)
				free (args[--i]);
			free (args);
			exit(1);
		}
		i++;
	}
	path_list = get_path(envp);
	i = 0;
	while(path_list[i])
	{
		full_path = ft_strjoin(path_list[i++], args[0]);
		if (!full_path)
			break;
		printf("%s\n", full_path);
		execve(full_path, args, NULL);
		free (full_path);
	}
	i = 0;
	while (args[i])
		free (args[i++]);
	free (args);
	exit(1);
/* 	while (path_list[i])
		printf("%s\n", path_list[i++]);
	while (--i >= 0)
		free (path_list[i]);
	free (path_list);*/
}
	//char *args[] = {"ls", "-l", NULL};

	//settings set target.run-args ls
	//frame variable