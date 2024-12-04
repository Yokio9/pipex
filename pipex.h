/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 00:46:15 by dimatayi          #+#    #+#             */
/*   Updated: 2024/12/04 05:17:20 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "./libft/libft.h"

int		return_perror(void);
int		free_double_ptr(char **args);
char	**add_slash(char **split_path);
char	**get_path(char *envp[]);
int		set_in_out_file(char *file, int in_out);
int		exec(char **path_list, char **args);
int		child(char **path_list, char **in_args, char *infile, int fd[]);
int		parent(char *path_list[], char **out_args, char *outfile, int fd[]);
int		init(char *argv[], char **in_args, char **out_args, char *path_list[]);

#endif