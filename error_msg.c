/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 09:21:47 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/15 18:39:39 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_msg(char *msg, int errorstatus)
{
	perror(msg);
	exit(errorstatus);
}

void	error_msg_errno(char *msg, int errorstatus, int iderrno)
{
	errno = iderrno;
	perror(msg);
	exit(errorstatus);
}
