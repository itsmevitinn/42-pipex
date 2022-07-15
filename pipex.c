/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/15 11:40:18 by vsergio          ###   ########.fr       */
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
		error_msg("", 22);
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
	close(readwrite[0]);
	close(readwrite[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

void	firstchild(char **argv, int *readwrite)
{
	int fdinfile;

	fdinfile = open(argv[1], O_RDONLY);
	if (fdinfile == -1)
		error_msg("Failed to open infile!", 2);
	runcommand(readwrite[0], fdinfile, readwrite[1], argv[2]);
}

void	secondchild(char **argv, int *readwrite)
{
	int fdoutfile;

	fdoutfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fdoutfile == -1)
		error_msg("Failed to open file!", 2);
	runcommand(readwrite[1], readwrite[0], fdoutfile, argv[3]);
}

void	pathexecv(char *argv, char **envp)
{
	char		**paths;
	char		**arguments;
	char 		*completepath;
	char		*commandpath;
	int i;

	i = 0;

	arguments = ft_split(argv, ' ');
	while (*envp++)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			paths = ft_split(*envp + 5, ':');
	}
	while (*paths++)
	{
		completepath = ft_strjoin(*paths, "/");
		commandpath = ft_strjoin(completepath, arguments[0]);
		free(completepath);
		if (!access(commandpath, F_OK | X_OK))
		{
			// execve(commandpath, arguments, NULL);
			write(1, "hi", 2);
			exit(1);
		}
		free(commandpath);
	}
	freeargs(arguments);
	perror("command not found");
}

void	runcommand(int unusedpipefd, int inputread, int output, char *argv)
{
	close(unusedpipefd);
	dup2(inputread, 0);
	dup2(output, 1);
	pathexecv(argv);
}
