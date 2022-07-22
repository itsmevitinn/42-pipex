/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:14:39 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/22 10:46:52 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>

void	doexecve(char **paths, char **arguments);
void	firstchild(char **argv, int *readwrite);
void	secondchild(char **argv, int *readwrite);
void	error_msg(char *msg, int errorstatus);
void	error_msg_errno(char *msg, int errorstatus, int iderrno);
void	pathfilter(char *argv);
#endif
