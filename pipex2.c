/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:19 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/13 23:18:25 by vsergio          ###   ########.fr       */
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
	checkfiles(fdinfile, fdoutfile);
	if (pipe(readwrite) == -1)
	{
		perror("Failed to create pipe!");
		exit(1);
	}
	pid = fork();
	checkpid(pid);
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
	int			i;
	int			j;

	j = 0;
	i = 0;
	arguments = ft_split(argv, ' ');
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			paths = ft_split(&environ[i][5], ':');
		i++;
	}
	while (paths[j])
	{
		paths[j] = ft_strjoin(paths[j], "/");
		paths[j] = ft_strjoin(paths[j], arguments[0]);
		if (!access(paths[j], F_OK | X_OK))
			execve(paths[j], arguments, NULL);
		j++;
	}
	free(paths[j]);
}

void	checkfiles(int fdinfile, int fdoutfile)
{
	if (fdinfile == -1 | fdoutfile == -1)
	{
		perror("Failed to open files");
		exit(1);
	}
}

void	checkpid(int pid)
{
	if (pid == -1)
	{
		perror("Failed to do fork!");
		exit(1);
	}
}

void	runcommand(int unusedpipefd, int inputread, int output, char *argv)
{
	close(unusedpipefd);
	dup2(inputread, 0);
	dup2(output, 1);
	pathexecv(argv);
}
