/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:14:39 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/25 00:33:17 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>

void	close_first_pipe(int argc, int **readwrite);
void	close_middle_pipes(int argc, int usedpipe, int **readwrite);
void	close_last_pipe(int argc, int usedpipe, int **readwrite);
int		do_files(char *argv, int type);
void	here_doc(char **argv, int **readwrite);
void	check_argc(int argc);
int		first_command(char **argv, int argc, int **readwrite);
int		middle_commands(char **argv, int argc, int **readwrite, int indexpipe);
int		last_command(char **argv, int argc, int **readwrite, int indexpipe);
void	runcmds(char *argv, int input, int output);
void	waitpids(int *pid, int argc);
void	do_pipes(int argc, int **readwrite);
void	free_pointers(int **readwrite, int *pid, int argc);
void	doexecve(char **paths, char **arguments);
void	close_all(int argc, int **readwrite);
void	error_msg(char *msg, int errorstatus);
void	error_msg_errno(char *msg, int errorstatus, int iderrno);
#endif
