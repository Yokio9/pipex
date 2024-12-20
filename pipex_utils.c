/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 05:07:38 by dimatayi          #+#    #+#             */
/*   Updated: 2024/12/20 23:12:39 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	return_perror(int error)
{
	perror("");
	exit (error);
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

char	*build_cmd(char **split_path, char *cmd)
{
	int		i;
	char	*temp;
	char	*executable;

	i = -1;
	temp = NULL;
	executable = NULL;
	while (split_path[++i])
	{
		temp = ft_strjoin(split_path[i], "/");
		executable = ft_strjoin(temp, cmd);
		free(temp);
		temp = NULL;
		if (access(executable, F_OK | X_OK) == 0)
			return (executable);
		if (!split_path[i + 1])
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		free(executable);
		executable = NULL;
	}
	return (NULL);
}

char	*get_path(char *envp[], char *arg)
{
	int		i;
	char	*cmd;
	char	**split_path;

	i = 0;
	split_path = NULL;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			split_path = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (!split_path)
		return (NULL);
	cmd = build_cmd(split_path, arg);
	free_double_ptr(split_path);
	if (cmd == NULL)
		return (ft_strdup("wrong_cmd"));
	return (cmd);
}

char	**check_args(char **args)
{
	int		size;
	int		j;
	int		indicator;
	char	*temp;
	char	**cmd;

	j = 0;
	size = 0;
	indicator = 0;
	while (args[++size])
	{
		if (*args[size] == 39)
			indicator = size;
	}
	size--;
	while (args[size][j])
		j++;
	if (indicator && args[size][--j] == 39)
	{
		temp = ft_strjoin_double_ptr(size, &args[indicator], " ");
		if (!temp)
			return (NULL);
		cmd = ft_calloc(3, sizeof(char *));
		if (!cmd)
		{
			free(temp);
			return (NULL);
		}
		cmd[0] = args[0];
		cmd[1] = ft_strdup(temp + 1);
		cmd[1][ft_strlen(cmd[1]) - 1] = '\0';
		free(temp);
		return (cmd);
	}
	return (args);
}
