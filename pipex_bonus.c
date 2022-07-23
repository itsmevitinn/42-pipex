/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/23 13:07:37 by vsergio          ###   ########.fr       */
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
	int	fdinfile;

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
		{
			int fdheredoc = open("here_doc", O_RDONLY);
			int fdtemp = open("tempfile.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (fdheredoc == -1 || fdtemp == -1)
				error_msg("Failed to open file!", 1);
			char *content;
			char *checklimiter;
			printf("Limiter: %s\n", argv[2]);
			content = get_next_line(fdheredoc);
			checklimiter = ft_strtrim(content, "\n");
			while (ft_strncmp(checklimiter, argv[2], ft_strlen(checklimiter)) && content != NULL)
			{
				free(checklimiter);
				write(fdtemp, content, ft_strlen(content));
				free(content);
				content = get_next_line(fdheredoc);
				checklimiter = ft_strtrim(content, "\n");
				printf("Check limiter: %s ", checklimiter);
				printf("Nossa string: %s", content);
			}
			// free(content);
			int fdout = open("tempfile.txt", O_RDONLY);
			// unlink("tempfile.txt");
			runcmds(argv[3], fdout, readwrite[0][1]);
		}
		fdinfile = open(argv[1], O_RDONLY);
		if (fdinfile == -1)
			error_msg("Failed to open infile!", 1);
		runcmds(argv[2], fdinfile, readwrite[0][1]);
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
		runcmds (argv[pipe + 2], readwrite[pipe - 1][0], readwrite[pipe][1]);
	}
	return (pid);
}

int	last_command(char **argv, int argc, int **readwrite, int indexpipe)
{
	int	indexchecker;
	int	fdoutfile;
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
			fdoutfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fdoutfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fdoutfile == -1)
			error_msg("Failed to open outfile!", 1);
		runcmds(argv[argc - 2], readwrite[indexpipe - 1][0], fdoutfile);
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
