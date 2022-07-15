/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:14:39 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/15 13:35:03 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

void	closepipes(int *pipe);
void	firstchild(char **argv, int *readwrite, char **envp);
void	secondchild(char **argv, int *readwrite, char **envp);
void	error_msg(char *msg, int errorstatus);
void	pathexecv(char *argv, char **envp);
#endif
