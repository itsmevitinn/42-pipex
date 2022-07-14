/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/14 15:39:05 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>
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
	checker(fdinfile, fdoutfile, 0);
	if (pipe(readwrite) == -1)
	{
		perror("Failed to create pipe!");
		exit(1);
	}
	pid = fork();
	checker(0, 0, pid);
	if (pid == 0)
	{
		close(readwrite[0]);
		dup2(fdinfile, 0);
		dup2(readwrite[1], 1);
		pathexecv(argv[2]);
		close(readwrite[1]);
	}
	pid2 = fork();
	checker(0, 0, pid2);
	if (pid2 == 0)
	{
		close(readwrite[1]);
		dup2(readwrite[0], 0);
		dup2(fdoutfile, 1);
		pathexecv(argv[3]);
		close(readwrite[0]);
	}
	waitpid(pid, NULL, 0);
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
		else
			printf("command not found: %s -> %s", argv, strerror(2));
		j++;
	}
	free(paths[j]);
}

void	checker(int fdinfile, int fdoutfile, int pid)
{
	if (fdinfile == -1)
	{
		perror("Failed to open infile");
		exit(1);
	}
	else if (fdoutfile == -1)
	{
		perror("Failed to open outfile!");
		exit(1);
	}
	else if (pid == -1)
	{
		perror("Failed to do fork!");
		exit(1);
	}
}
