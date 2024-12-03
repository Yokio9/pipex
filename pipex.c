/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:44:51 by dimatayi          #+#    #+#             */
/*   Updated: 2024/12/04 00:52:43 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//< file1 cmd1 | cmd2 > file2

//		< infile ls -l | wc -l > outfile
//./pipex infile "ls -l" "wc -l" outfile

//		< infile grep a1 | wc -w > outfile
//./pipex infile "grep a1" "wc -w" outfile

//if argv[1] == "<"	-->	input = argv[2] else input = argv[1]
//access(input)

#include "pipex.h"

int	free_double_ptr(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	return (1);
}

char	**add_slash(char **split_path)
{
	int		i;
	char	*temp;

	i = -1;
	while (split_path[++i])
	{
		temp = split_path[i];
		split_path[i] = ft_strjoin(split_path[i], "/");
		if (!split_path[i])
		{
			i = 0;
			while (split_path[i])
			{
				free(split_path[i]);
				i++;
			}
			return (NULL);
		}
		free (temp);
	}
	return (split_path);
}

char	**get_path(char *envp[])
{
	int		i;
	char	**split_path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			split_path = ft_split(envp[i] + 5, ':');
			if (!split_path)
				return (NULL);
			if (add_slash(split_path) == NULL)
			{
				free(split_path);
				return (NULL);
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

	if (access(infile, R_OK) == -1)
	{
		perror("");
		return (0);
	}
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

int	init(char **path_list, char **args, char *cmd1)
{
	int		i;
	int		exec_check;
	char	*full_path;

	i = 0;
	while (path_list[i])
	{
		full_path = ft_strjoin(path_list[i++], cmd1);
		if (!full_path)
			break ;
		exec_check = execve(full_path, args, NULL);
		free (full_path);
	}
	if (exec_check == -1)
		perror("");
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	char	**args;
	char	**path_list;

	i = 0;
	if (argc != 3)					//CHANGE THIS TO argc != 5
		return (0);
	if (!set_infile(argv[1]))
		return (1);
	args = ft_split(argv[2], ' ');
	if (!args)
		return (1);
	path_list = get_path(envp);
	if (!path_list)
		return (free_double_ptr(args));
	i = init(path_list, args, args[0]);
	free_double_ptr(args);
	free_double_ptr(path_list);
	return (i);
}
/* 	while (path_list[i])
		printf("%s\n", path_list[i++]);
	while (--i >= 0)
		free (path_list[i]);
	free (path_list);*/
	//char *args[] = {"ls", "-l", NULL};

	//settings set target.run-args ls
	//frame variable