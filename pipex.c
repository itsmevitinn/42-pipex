/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/14 22:51:36 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	int	fdinfile;
	int	fdoutfile;
	int	readwrite[2];
	int	pid;
	int	pid2;

	check_params(argc);
	fdinfile = open(argv[1], O_RDONLY);
	fdoutfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	checker(pipe(readwrite), fdinfile, fdoutfile, 0);
	pid = fork();
	checker(0, 0, 0, pid);
	if (pid == 0)
		runcommand(readwrite[0], fdinfile, readwrite[1], argv[2]);
	pid2 = fork();
	checker(0, 0, 0, pid2);
	if (pid2 == 0)
		runcommand(readwrite[1], readwrite[0], fdoutfile, argv[3]);
	close(readwrite[0]);
	close(readwrite[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

void	pathexecv(char *argv)
{
	extern char	**environ;
	char		**paths;
	char		**arguments;
	char		*commandpath;
	int			i;

	i = 0;
	arguments = ft_split(argv, ' ');
	while (*environ)
	{
		if (ft_strncmp(*environ, "PATH=", 5) == 0)
			paths = ft_split(*environ + 5, ':');
		environ++;
	}
	while (paths[i++])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		commandpath = ft_strjoin(paths[i], arguments[0]);
		free(paths[i]);
		if (!access(commandpath, F_OK | X_OK))
			execve(commandpath, arguments, NULL);
		free(commandpath);
	}
	freeargs(arguments);
	perror("command not found");
}

void	checker(int pipe, int fdinfile, int fdoutfile, int pid)
{
	if (pipe == -1)
	{
		perror("Failed to do pipe!");
		exit(32);
	}
	else if (fdinfile == -1)
	{
		perror("Failed to open infile");
		exit(2);
	}
	else if (fdoutfile == -1)
	{
		perror("Failed to open outfile!");
		exit(2);
	}
	else if (pid == -1)
	{
		perror("Failed to do fork!");
		exit(10);
	}
}

void	runcommand(int unusedpipefd, int inputread, int output, char *argv)
{
	close(unusedpipefd);
	dup2(inputread, 0);
	dup2(output, 1);
	pathexecv(argv);
}
