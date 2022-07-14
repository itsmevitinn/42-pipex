/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:19 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/14 18:59:17 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	main(int argc, char *argv[])
{
	int	fdinfile;
	int	fdoutfile;
	int	readwrite[2];
	int	pid;

	check_params(argc);
	fdinfile = open(argv[1], O_RDONLY);
	fdoutfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	checker(fdinfile, fdoutfile, 0);
	if (pipe(readwrite) == -1)
	{
		perror("Failed to create pipe!");
		exit(32);
	}
	pid = fork();
	checker(0, 0, pid);
	if (pid == 0)
		runcommand(readwrite[0], fdinfile, readwrite[1], argv[2]);
	waitpid(pid, NULL, 0);
	runcommand(readwrite[1], readwrite[0], fdoutfile, argv[3]);
}

void	pathexecv(char *argv)
{
	extern char	**environ;
	char		**paths;
	char		**arguments;
	char		*commandpath;
	int			i;
	int			j;

	j = 0;
	i = 0;
	arguments = ft_split(argv, ' ');
	// do this dinamically \/
	// arguments[1] = ft_strtrim(arguments[1], "'");
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			paths = ft_split(&environ[i][5], ':');
		i++;
	}
	while (paths[j])
	{
		paths[j] = ft_strjoin(paths[j], "/");
		commandpath = ft_strjoin(paths[j], arguments[0]);
		free(paths[j]);
		if (!access(commandpath, F_OK | X_OK))
			execve(commandpath, arguments, NULL);
		free(commandpath);
		j++;
	}
	freeargs(arguments);
	perror("command not found");
}

void	checker(int fdinfile, int fdoutfile, int pid)
{
	if (fdinfile == -1)
	{
		perror("Failed to open infile!");
		exit(2);
	}
	else if (fdoutfile == -1)
	{
		perror("Failed to open outfile!");
		exit(2);
	}
	else if (pid == -1)
	{
		perror ("Failed to do fork!");
		exit (10);
	}
}

void	runcommand(int unusedpipefd, int inputread, int output, char *argv)
{
	close(unusedpipefd);
	dup2(inputread, 0);
	dup2(output, 1);
	pathexecv(argv);
}
