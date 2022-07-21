/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/21 00:36:36 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char **env)
{
	int	pid[argc - 3]; // 1 fork para cada comando, comando = argc - 3
	int	**readwrite;// a quantidade de pipes sera sempre a quantidade de comandos - 1
	int	countpipe;
	int	countpid;

	if (argc < 5)
		error_msg_errno("ERROR", 22, 22);
	countpipe = 0;
	countpid = 0;
	readwrite = (int **)malloc(sizeof(int *) * (argc - 3)); // eh -3 e nao -4 pois estamos trabalhando com aloocamento, e a contagem comeca no 1, diferente do array que comeca no 0
	while (countpipe < argc - 3)
	{
		readwrite[countpipe] = (int *)malloc(sizeof(int) * 2);
		if (pipe(readwrite[countpipe]) == -1)
			error_msg("Failed to do pipe!", 32);
		countpipe++;
	}
	pid[countpid] = fork();
	if (pid[countpid] == 0)
		first_child(argv, argc, readwrite, env);
	waitpid(pid[countpid++], NULL, 0);
	while (countpid < argc - 4)
	{
		pid[countpid] = fork();
		if (pid[countpid] == 0)
		{
			close_middle_commands(argc, readwrite, countpid);
			runcmds(argv[countpid + 2], readwrite[countpid - 1][0], readwrite[countpid][1], env);
		}
		countpid++;
	}
	pid[countpid] = fork();
	if (pid[countpid] == 0)
		last_child(argv, argc, readwrite, countpid, env);
	close_all(argc, readwrite);
	return (0);
}

void	first_child(char **argv, int argc, int **readwrite, char **env)
{
	int	indexchecker;
	int	fdinfile;

	indexchecker = 0;
	while (indexchecker < argc - 4)
	{
		if (indexchecker == 0)
			close(readwrite[indexchecker][0]); // fecho apenas a leitura do pipe 0 pois a escrita eu utilizo
		else
		{
			close(readwrite[indexchecker][0]);
			close(readwrite[indexchecker][1]);
		}
		indexchecker++;
	}
	fdinfile = open(argv[1], O_RDONLY);
	runcmds(argv[2], fdinfile, readwrite[0][1], env);
}

void	close_middle_commands(int argc, int **readwrite, int indexpipe)
{
	int	indexchecker;

	indexchecker = 0;
	while (indexchecker < argc - 4)
	{
		if (indexchecker == indexpipe - 1)
			close(readwrite[indexchecker][1]); // fecho a escrita do pipe anterior e preservo a leitura do pipe anterior
		else if (indexchecker == indexpipe)
			close(readwrite[indexchecker][0]); // fecho a leitura atual pois uso a leitura do pipe anterior
		else
		{
			close(readwrite[indexchecker][0]);
			close(readwrite[indexchecker][1]);
		}
		indexchecker++;
	}
}

void	last_child(char **argv, int argc, int **readwrite, int indexpipe, char **env)
{
	int	indexchecker;
	int	fdoutfile;

	indexchecker = 0;

	while (indexchecker < argc - 4)
	{
		if (indexchecker == indexpipe - 1)
			close(readwrite[indexchecker][1]); // fecho a escrita do pipe anterior e preservo a leitura
		else // fecho tudo
		{
			close(readwrite[indexchecker][0]);
			close(readwrite[indexchecker][1]);
		}
		indexchecker++;
	}
	fdoutfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	runcmds(argv[argc - 2], readwrite[indexpipe - 1][0], fdoutfile, env);
}

void	runcmds(char *argv, int input, int output, char **env)
{
	char	**paths;
	char	**arguments;
	int		i;
	int		countargs;

	countargs = 0;
	i = 0;
	arguments = ft_split_quotes(argv, ' ');
	while (arguments[countargs++])
		arguments[countargs] = ft_strtrim(arguments[countargs], "'\"");
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			paths = ft_split(&env[i][5], ':');
		i++;
	}
	dup2(input, 0);
	close(input);
	dup2(output, 1);
	close(output);
	doexecve(paths, arguments);
}
