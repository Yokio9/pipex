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
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
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

int	set_infile(char *infile)
{
	int	open_check;
	int	dup_check;

	open_check = open(infile, O_RDONLY);
	if (open_check == -1)
	{
		perror("");
		return (0);
	}
	dup_check = dup2(open_check, 0);
	close(open_check);
	if (dup_check == -1)
	{
		perror("");
		return (0);
	}
	return (1);
}

int main(int argc, char *argv[], char *envp[])
{
	int		i;
	char	**args;
	char	*full_path;
	char	**path_list;

	i = 0;
	if (argc != 3)					//CHANGE THIS TO argc != 5
		return (0);
	if (!set_infile(argv[1]))
		return (1);
	args = ft_split(argv[2], ' ');
	if (!args)
		exit(1);
	path_list = get_path(envp);
	i = 0;
	while(path_list[i])
	{
		full_path = ft_strjoin(path_list[i++], args[0]);
		if (!full_path)
			break;
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