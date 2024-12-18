/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:46:15 by dimatayi          #+#    #+#             */
/*   Updated: 2024/12/18 12:19:06 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/syscall.h>
# include "./libft/libft.h"

int		return_perror(int error);
int		free_double_ptr(char **args);
void	exec(char *cmd, char **envp);
char	*get_path(char *envp[], char *cmd);
char	*build_cmd(char **split_path, char *cmd);
void	child(char **args, char **envp, int fd[]);
void	parent(char **args, char **envp, int fd[]);

#endif