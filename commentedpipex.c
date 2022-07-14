/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commentedpipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:19 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/13 22:33:40 by vsergio          ###   ########.fr       */
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
	// parent's fork return pid of child
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
	//split the first command to goes in execve divided by each argument
	// e.g = "wc -l" -> "wc" "-l"
	arguments = ft_split(argv, ' ');
	while (environ[i])
	{
		// here we check if the line of environ have PATH= at start
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		//if yes, we split this line by ':' to catch all the possibles pathcommands
			paths = ft_split(&environ[i][5], ':');
		// if this line doesnt have PATH=, we go to the next line
		i++;
	}
	while (paths[j])
	{
		// here, we put in each possible pathcommand a '/' at the end
		// e.g.: /usr/bin -> /usr/bin/
		paths[j] = ft_strjoin(paths[j], "/");
		// we add the first argument from the command
		// e.g.: /usr/bin/ -> /usr/bin/wc
		paths[j] = ft_strjoin(paths[j], arguments[0]);
		// and here we check if this path exists and executes
		if (!access(paths[j], F_OK | X_OK))
		// if yes, we do a execve in this pathcommand
		// e.g-> arguments = "wc" "-l"
		// e.g -> paths[j] = /usr/bin/wc
			execve(paths[j], arguments, NULL);
		// if this path isnt correct, go to the next path and check
		j++;
	}
	// free(paths[j]);
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
	//apply command from execve in input
	dup2(inputread, 0);
	//write output from execve to pipe
	dup2(output, 1);
	pathexecv(argv);
}
