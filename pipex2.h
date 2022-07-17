/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:14:39 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/16 22:49:01 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

void	writecommand(char *argv, char **envp, int **readwrite);
void	doexecve(char **paths, char **arguments);
void	firstchild(char **argv, int **readwrite, char **envp);
void	secondchild(char **argv, int **readwrite, char **envp);
void	thirdchild(char **argv, int **readwrite, char **envp);
void	error_msg(char *msg, int errorstatus);
void	error_msg_errno(char *msg, int errorstatus, int iderrno);
void	pathfilter(char *argv, char **envp);
#endif
