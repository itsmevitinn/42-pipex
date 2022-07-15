/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/15 13:36:19 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	int	readwrite[2];
	int	pid;
	int	pid2;

	if (argc != 5)
	{
		errno = 22;
		error_msg("ERROR", 22);
	}
	if (pipe(readwrite) == -1)
		error_msg("Failed to do pipe!", 32);
	pid = fork();
	if (pid == -1)
		error_msg("Failed to do first fork!", 10);
	else if (pid == 0)
		firstchild(argv, readwrite, envp);
	pid2 = fork();
	if (pid2 == -1)
		error_msg("Failed to do second fork!", 10);
	else if (pid2 == 0)
		secondchild(argv, readwrite, envp);
	closepipes(readwrite);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

void	firstchild(char **argv, int *readwrite, char **envp)
{
	int	fdinfile;

	fdinfile = open(argv[1], O_RDONLY);
	if (fdinfile == -1)
		error_msg("Failed to open infile!", 2);
	close(readwrite[0]);
	dup2(fdinfile, 0);
	dup2(readwrite[1], 1);
	pathexecv(argv[2], envp);
}

void	secondchild(char **argv, int *readwrite, char **envp)
{
	int	fdoutfile;

	fdoutfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fdoutfile == -1)
		error_msg("Failed to open file!", 2);
	close(readwrite[1]);
	dup2(readwrite[0], 0);
	dup2(fdoutfile, 1);
	pathexecv(argv[3], envp);
}

void	pathexecv(char *argv, char **envp)
{
	char		**paths;
	char		**arguments;
	char		*pathdone;
	char		*commandpath;
	int			i;

	i = 0;
	arguments = ft_split(argv, ' ');
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths = ft_split(&envp[i][5], ':');
		i++;
	}
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

void	closepipes(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}
