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
	char	*path;
	char	**split_path;

	i = 0;
	while (envp[i])
	{
		if (strncmp("PATH=", envp[i], 5) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			if (!path)
				return (NULL);
			split_path = ft_split((const char *)path, ':');
			free (path);
			return (split_path);
		}
		i++;
	}
	return (NULL);
}

int main(int argc, char const *argv[], char *envp[])
{
	(void)argv;
	if (argc < 1)
		return (1);
	int	i = 0;
	char **output = get_path(envp);
	while (output[i])
		printf("%s\n", output[i++]);
	while (--i >= 0)
		free (output[i]);
	free (output);
	return 0;
}


/* int main(int argc, char *argv[], char *envp[])
{
	int	i;
	char	*full_path;

	i = 0;
	if (argc < 2)					//CHANGE THIS TO argc != 5
		return (0);
	char **args = calloc(argc, sizeof(char *));
	if (!args)
		exit(1);
	while (argv[i + 1])
	{
		args[i] = strdup(argv[i + 1]);
		if (!args[i])
		{
			while (i > 0)
				free (args[--i]);
			free (args);
			exit(1);
		}
		i++;
	}
	const char *path_list[] = {"/usr/local/bin/", "/usr/bin/", "/bin/", "/sbin/", "/usr/sbin/", NULL};
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
} */
	//char *args[] = {"ls", "-l", NULL};

	//settings set target.run-args ls
	//frame variable