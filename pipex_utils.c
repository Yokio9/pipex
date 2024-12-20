/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 05:07:38 by dimatayi          #+#    #+#             */
/*   Updated: 2024/12/21 00:15:49 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_double_ptr(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
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
		if (!temp)
			return (NULL);
		executable = ft_strjoin(temp, cmd);
		free(temp);
		if (!executable)
			return (NULL);
		if (access(executable, F_OK | X_OK) == 0)
			return (executable);
		free(executable);
		executable = NULL;
	}
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
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

char	**assemble(int size, int indicator, char **args)
{
	char	*temp;
	char	**cmd;

	temp = ft_table_join(size, &args[indicator], " ");
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
	free(temp);
	if (!cmd[1])
	{
		free(cmd[0]);
		return (NULL);
	}
	cmd[1][ft_strlen(cmd[1]) - 1] = '\0';
	return (cmd);
}

char	**check_args(char **args)
{
	int		size;
	int		j;
	int		indicator;

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
		return (assemble(size, indicator, args));
	return (args);
}
