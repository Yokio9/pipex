/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:44:51 by dimatayi          #+#    #+#             */
/*   Updated: 2024/12/04 03:03:57 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	return_perror()
{
	perror("");
	return (1);
}

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
	int	oldfile;
	int	dup_check;

	if (access(infile, R_OK) == -1)
		return (return_perror());
	oldfile = open(infile, O_RDONLY);
	if (oldfile == -1)
		return (return_perror());
	dup_check = dup2(oldfile, 0);
	close(oldfile);
	if (dup_check == -1)
		return (return_perror());
	return (0);
}

int	child(char **path_list, char **args, char *infile)
{
	int		i;
	int		exec_check;
	char	*full_path;

	i = 0;
	if (set_infile(infile))
		return (1);
	while (path_list[i])
	{
		full_path = ft_strjoin(path_list[i++], args[0]);
		if (!full_path)
			return (1);
		execve(full_path, args, NULL);
		free (full_path);
	}
	return (return_perror());
}

int	init(char *argv[], char **in_args, char **out_args, char *path_list[])
{
	int		pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (return_perror());
	pid = fork();
	if (fork == -1)
		return (return_perror());
	else if (pid == 0)
		return (child(path_list, in_args, argv[1]));
	else
		parent(path_list, in_args, argv[1], pid);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	char	**in_args;
	char	**out_args;
	char	**path_list;

	i = 0;
	if (argc != 5)
		return (0);
	path_list = get_path(envp);
	if (!path_list)
		return (1);
	in_args = ft_split(argv[2], ' ');
	if (!in_args)
		return (free_double_ptr(path_list));
	out_args = ft_split(argv[3], ' ');
	if (!out_args)
	{
		free_double_ptr(path_list);
		return (free_double_ptr(in_args));
	}
	i = init(argv, in_args, out_args, path_list);
	free_double_ptr(in_args);
	free_double_ptr(out_args);
	free_double_ptr(path_list);
	return (i);
}
