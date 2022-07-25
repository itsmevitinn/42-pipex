/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/25 00:13:57 by vsergio          ###   ########.fr       */
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
