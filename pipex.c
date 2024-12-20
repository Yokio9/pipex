/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:44:51 by dimatayi          #+#    #+#             */
/*   Updated: 2024/12/21 00:23:40 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **envp)
{
	char	**args;
	char	*full_path;

	args = NULL;
	full_path = NULL;
	args = ft_split(cmd, ' ');
	if (!args)
		exit (1);
	args = check_args(args);
	full_path = get_path(envp, args[0]);
	if (!full_path || !ft_strncmp(full_path, "wrong_cmd", 10))
	{
		if (!full_path)
			perror("");
		else
			free(full_path);
		free_double_ptr(args);
		exit (1);
	}
	execve(full_path, args, NULL);
	free_double_ptr(args);
	free(full_path);
	perror("");
	exit (1);
}

void	child(char **args, char **envp, int fd[])
{
	int	oldfile;

	close(fd[0]);
	if (access(args[1], R_OK) == -1)
	{
		perror(args[1]);
		exit (1);
	}
	oldfile = open(args[1], O_RDONLY, 0777);
	dup2(oldfile, 0);
	dup2(fd[1], 1);
	close(fd[1]);
	exec(args[2], envp);
}

void	parent(char **args, char **envp, int fd[])
{
	int	oldfile;

	close(fd[1]);
	oldfile = open(args[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(oldfile, 1);
	dup2(fd[0], 0);
	close(fd[0]);
	exec(args[3], envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5 && *argv[2] && *argv[3])
	{
		if (pipe(fd) == -1)
		{
			perror("");
			exit (-1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("");
			exit (-1);
		}
		if (pid == 0)
			child(argv, envp, fd);
		wait(NULL);
		parent(argv, envp, fd);
	}
	ft_putstr_fd("./pipex infile cmd1 cmd2 outfile\n", 2);
	return (0);
}
