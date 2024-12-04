/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:44:51 by dimatayi          #+#    #+#             */
/*   Updated: 2024/12/04 05:07:37 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec(char **path_list, char **args)
{
	int		i;
	char	*full_path;

	i = 0;
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

int	child(char **path_list, char **in_args, char *infile, int fd[])
{
	close(fd[0]);
	if (set_in_out_file(infile, 0))
		return (1);
	dup2(fd[1], 1);
	close(fd[1]);
	return (exec(path_list, in_args));
}

int	parent(char *path_list[], char **out_args, char *outfile, int fd[])
{
	close(fd[1]);
	if (set_in_out_file(outfile, 1))
		return (1);
	dup2(fd[0], 0);
	close(fd[0]);
	return (exec(path_list, out_args));
}

int	init(char *argv[], char **in_args, char **out_args, char *path_list[])
{
	int		pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (return_perror());
	pid = fork();
	if (pid == -1)
		return (return_perror());
	else if (pid == 0)
		return (child(path_list, in_args, argv[1], fd));
	wait(NULL);
	return (parent(path_list, out_args, argv[4], fd));
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
