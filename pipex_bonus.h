/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:14:39 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/21 17:35:38 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

void	do_pipes(int argc, int **readwrite);
void	check_argc(int argc);
int		first_command(char **argv, int argc, int **readwrite);
int		middle_commands(char **argv, int argc, int **readwrite, int indexpipe);
int		last_command(char **argv, int argc, int **readwrite, int indexpipe);
void	close_all(int argc, int **readwrite);
void	runcmds(char *argv, int input, int output);
void	doexecve(char **paths, char **arguments);
void	error_msg(char *msg, int errorstatus);
void	error_msg_errno(char *msg, int errorstatus, int iderrno);
void	waitpids(int *pid, int argc);
void	free_pointers(int **readwrite, int *pid);
#endif
