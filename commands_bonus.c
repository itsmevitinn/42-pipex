/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 00:04:11 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/25 10:03:49 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	first_command(char **argv, int argc, int **readwrite)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_msg("Failed to do first fork!", EXIT_FAILURE);
	else if (pid == 0)
	{
		close_first_pipe(argc, readwrite);
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			here_doc(argv, readwrite);
		else
			runcmds(argv[2], do_files(argv[1], 0), readwrite[0][1]);
	}
	return (pid);
}

int	middle_commands(char **argv, int argc, int **readwrite, int pipe)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_msg("Failed to do some middle fork!", EXIT_FAILURE);
	else if (pid == 0)
	{
		close_middle_pipes(argc, pipe, readwrite);
		runcmds(argv[pipe + 2], readwrite[pipe - 1][0], readwrite[pipe][1]);
	}
	return (pid);
}

int	last_command(char **argv, int argc, int **rdwr, int pipe)
{
	char	*lastcmd;
	int		pid;

	lastcmd = argv[argc - 2];
	pid = fork();
	if (pid == -1)
		error_msg("Failed to do last fork!", EXIT_FAILURE);
	else if (pid == 0)
	{
		close_last_pipe(argc, pipe, rdwr);
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			runcmds(lastcmd, rdwr[pipe - 1][0], do_files(argv[argc - 1], 2));
		else
			runcmds(lastcmd, rdwr[pipe - 1][0], do_files(argv[argc - 1], 1));
	}
	return (pid);
}
