/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:14:39 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/20 11:18:34 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

void    close_all(int argc, int **readwrite);
void    close_first_command(int argc, int **readwrite);
void	close_middle_commands(int argc, int **readwrite, int indexpipe);
void	close_last_command(int argc, int **readwrite, int indexpipe);
void	runcmds(char *argv, int input, int output, char **env);
void	doexecve(char **paths, char **arguments);
void	error_msg(char *msg, int errorstatus);
void	error_msg_errno(char *msg, int errorstatus, int iderrno);
void	pathfilter(char *argv, char **envp);
#endif
