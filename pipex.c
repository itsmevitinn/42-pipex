/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/17 19:50:38 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
int	main(int argc, char **argv, char **env)
{
	int	readwrite[2];
	int	pid;
	int	pid2;

	if (argc != 5)
		error_msg_errno("ERROR", 22, 22);
	if (pipe(readwrite) == -1)
		error_msg("Failed to do pipe!", 32);
	pid = fork();
	if (pid == -1)
		error_msg("Failed to do first fork!", 10);
	else if (pid == 0)
		firstchild(argv, readwrite, env);
	pid2 = fork();
	if (pid2 == -1)
		error_msg("Failed to do second fork!", 10);
	else if (pid2 == 0)
		secondchild(argv, readwrite, env);
	close(readwrite[0]);
	close(readwrite[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

void	firstchild(char **argv, int *readwrite, char **env)
{
	int	fdinfile;

	fdinfile = open(argv[1], O_RDONLY);
	if (fdinfile == -1)
		error_msg("Failed to open infile!", 2);
	close(readwrite[0]);
	dup2(fdinfile, 0);
	dup2(readwrite[1], 1);
	pathfilter(argv[2], env);
}

void	secondchild(char **argv, int *readwrite, char **env)
{
	int	fdoutfile;

	fdoutfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fdoutfile == -1)
		error_msg("Failed to open outfile!", 2);
	close(readwrite[1]);
	dup2(readwrite[0], 0);
	dup2(fdoutfile, 1);
	pathfilter(argv[3], env);
}

void	pathfilter(char *argv, char **env)
{
	char		**paths;
	char		**arguments;
	int			i;
	int			countargs;

	i = 0;
	arguments = ft_split(argv, ' ');
	while (arguments[countargs++])
		arguments[countargs] = ft_strtrim(arguments[countargs], "'");
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			paths = ft_split(&env[i][5], ':');
		i++;
	}
	doexecve(paths, arguments);
}

void	doexecve(char **paths, char **arguments)
{
	char		*pathdone;
	char		*commandpath;
	int			i;

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
	perror("Command not found!");
}
