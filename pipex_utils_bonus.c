/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:28:13 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/26 11:58:22 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	waitpids(int *pid, int argc)
{
	int	countwait;

	countwait = 0;
	while (countwait < argc - 3)
		waitpid(pid[countwait++], NULL, 0);
}

void	do_pipes(int argc, int **readwrite)
{
	int	countpipes;

	countpipes = 0;
	while (countpipes < argc - 3)
		if (pipe(readwrite[countpipes++]) == -1)
			error_msg("Failed to do pipe!", 32);
}

void	free_pointers(int **readwrite, int *pid, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 3)
		free(readwrite[i++]);
	free(readwrite);
	free(pid);
}

void	doexecve(char **paths, char **arguments)
{
	char	*pathdone;
	char	*commandpath;
	int		i;

	i = 0;
	while (paths[i++])
	{
		if (!access(arguments[0], F_OK | X_OK))
			execve(arguments[0], arguments, NULL);
		pathdone = ft_strjoin(paths[i], "/");
		commandpath = ft_strjoin(pathdone, arguments[0]);
		free(pathdone);
		if (!access(commandpath, F_OK | X_OK))
			execve(commandpath, arguments, NULL);
		free(commandpath);
	}
	error_msg("zsh: command not found", 127);
}
