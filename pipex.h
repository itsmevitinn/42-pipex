/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:14:39 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/14 22:46:16 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

void	closepipes(int readwrite[]);
void	check_params(int argc);
void	checker(int pipe, int fdinfile, int fdoutfile, int pid);
void	pathexecv(char *argv);
void	runcommand(int unusedpipefd, int inputread, int output, char *argv);
void	freeargs(char **arguments);
#endif
