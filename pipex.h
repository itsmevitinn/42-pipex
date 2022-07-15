/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:14:39 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/15 11:41:05 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

void	firstchild(char **argv, int *readwrite);
void	secondchild(char **argv, int *readwrite);
void	error_msg(char *msg, int errorstatus);
void	pathexecv(char *argv, char **envp);
void	runcommand(int unusedpipefd, int inputread, int output, char *argv);
void	freeargs(char **arguments);
#endif
