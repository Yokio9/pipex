/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 05:07:38 by dimatayi          #+#    #+#             */
/*   Updated: 2024/12/04 05:13:18 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	return_perror(void)
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

int	set_in_out_file(char *file, int in_out)
{
	int	oldfile;
	int	dup_check;

	if (in_out)
		oldfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		oldfile = open(file, O_RDONLY, 0777);
	if (oldfile == -1)
		return (return_perror());
	dup_check = dup2(oldfile, in_out);
	close(oldfile);
	if (dup_check == -1)
		return (return_perror());
	return (0);
}
