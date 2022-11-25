/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/25 18:57:11 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int	readwrite[2];
	int	pid;
	int	pid2;

	if (argc != 5)
		error_msg_errno("zsh", 22, 22);
	if (pipe(readwrite) == -1)
		error_msg("Failed to do pipe!", 32);
	pid = fork();
	if (pid == -1)
		error_msg("Failed to do first fork!", 10);
	else if (pid == 0)
		firstchild(argv, readwrite);
	pid2 = fork();
	if (pid2 == -1)
		error_msg("Failed to do second fork!", 10);
	else if (pid2 == 0)
		secondchild(argv, readwrite);
	close(readwrite[0]);
	close(readwrite[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

void	firstchild(char **argv, int *readwrite)
{
	int	fdinfile;

	fdinfile = open(argv[1], O_RDONLY);
	if (fdinfile == -1)
		error_msg(argv[1], 2);
	close(readwrite[0]);
	dup2(fdinfile, 0);
	dup2(readwrite[1], 1);
	pathfilter(argv[2]);
}

void	secondchild(char **argv, int *readwrite)
{
	int	fdoutfile;

	fdoutfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fdoutfile == -1)
		error_msg(argv[4], 2);
	close(readwrite[1]);
	dup2(readwrite[0], 0);
	dup2(fdoutfile, 1);
	pathfilter(argv[3]);
}

void	pathfilter(char *argv)
{
	extern char	**environ;
	char		**paths;
	char		**arguments;
	int			i;
	int			countargs;

	i = 0;
	countargs = 0;
	arguments = ft_split_quotes(argv, ' ');
	while (arguments[countargs++])
		arguments[countargs] = ft_strtrim_edges(arguments[countargs], "'\"");
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			paths = ft_split(&environ[i][5], ':');
		i++;
	}
	doexecve(paths, arguments);
}

void	doexecve(char **paths, char **arguments)
{
	char	*pathdone;
	char	*commandpath;
	int		i;

	i = 0;
	while (paths[i++])
	{
		pathdone = ft_strjoin(paths[i], "/");
		commandpath = ft_strjoin(pathdone, arguments[0]);
		free(pathdone);
		if (!access(commandpath, F_OK | X_OK))
			execve(commandpath, arguments, NULL);
		free(commandpath);
	}
	error_msg("zsh: command not found", 127);
}
