/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/24 06:51:47 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[])
{
	int	**readwrite;
	int	*pid;
	int	countfd;
	int	countpid;

	check_argc(argc);
	countfd = 0;
	countpid = 0;
	readwrite = (int **)malloc(sizeof(int *) * (argc - 3));
	while (countfd < argc - 3)
		readwrite[countfd++] = (int *)malloc(sizeof(int) * 2);
	pid = (int *)malloc(sizeof(int) * 2);
	do_pipes(argc, readwrite);
	pid[countpid++] = first_command(argv, argc, readwrite);
	while (countpid < argc - 4)
	{
		pid[countpid] = middle_commands(argv, argc, readwrite, countpid);
		countpid++;
	}
	pid[countpid] = last_command(argv, argc, readwrite, countpid);
	close_all(argc, readwrite);
	waitpids(pid, argc);
	free_pointers(readwrite, pid, argc);
	return (0);
}

int	first_command(char **argv, int argc, int **readwrite)
{
	int	pid;
	int	indexchecker;

	pid = fork();
	if (pid == 0)
	{
		indexchecker = 0;
		while (indexchecker < argc - 4)
		{
			if (indexchecker == 0)
				close(readwrite[indexchecker][0]);
			else
			{
				close(readwrite[indexchecker][0]);
				close(readwrite[indexchecker][1]);
			}
			indexchecker++;
		}
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			here_doc(argv, readwrite);
		else
			runcmds(argv[2], do_files(argv[1], 0), readwrite[0][1]);
	}
	return (pid);
}

int	middle_commands(char **argv, int argc, int **readwrite, int pipe)
{
	int	pid;
	int	indexchecker;

	pid = fork();
	if (pid == 0)
	{
		indexchecker = 0;
		while (indexchecker < argc - 4)
		{
			if (indexchecker == pipe - 1)
				close(readwrite[indexchecker][1]);
			else if (indexchecker == pipe)
				close(readwrite[indexchecker][0]);
			else
			{
				close(readwrite[indexchecker][0]);
				close(readwrite[indexchecker][1]);
			}
			indexchecker++;
		}
		runcmds(argv[pipe + 2], readwrite[pipe - 1][0], readwrite[pipe][1]);
	}
	return (pid);
}

int	last_command(char **argv, int argc, int **readwrite, int indexpipe)
{
	int	indexchecker;
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		indexchecker = 0;
		while (indexchecker < argc - 4)
		{
			if (indexchecker == indexpipe - 1)
				close(readwrite[indexchecker][1]);
			else
			{
				close(readwrite[indexchecker][0]);
				close(readwrite[indexchecker][1]);
			}
			indexchecker++;
		}
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			runcmds(argv[argc - 2], readwrite[indexpipe - 1][0], do_files(argv[argc - 1], 2));
		else
			runcmds(argv[argc - 2], readwrite[indexpipe - 1][0], do_files(argv[argc - 1], 1));
	}
	return (pid);
}

void	runcmds(char *argv, int input, int output)
{
	extern char	**environ;
	char		**paths;
	char		**arguments;
	int			i;
	int			countargs;

	countargs = 0;
	i = 0;
	arguments = ft_split_quotes(argv, ' ');
	while (arguments[countargs++])
		arguments[countargs] = ft_stredgestrim(arguments[countargs], "'\"");
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			paths = ft_split(&environ[i][5], ':');
		i++;
	}
	dup2(input, 0);
	close(input);
	dup2(output, 1);
	close(output);
	doexecve(paths, arguments);
}
