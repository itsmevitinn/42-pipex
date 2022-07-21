/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/21 00:22:17 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char **env)
{
	int	pid[argc - 3]; // 1 fork para cada comando, comando = argc - 3
	int	**readwrite;// a quantidade de pipes sera sempre a quantidade de comandos - 1
	int	countpipe;
	int	countpid;
	int	allocate;

	countpipe = 0;
	countpid = 0;
	allocate = 0;
	readwrite = (int **)malloc(sizeof(int *) * (argc - 3)); // eh -3 e nao -4 pois estamos trabalhando com aloocamento, e a contagem comeca no 1, diferente do array que comeca no 0
	while (allocate < argc - 3) // aqui a mesma coisa, ex.: temos 3 comandos, ou seja, 6 argumentos - 3 = 3 (comandos), 0 eh menor que 3 ? sim, 1 eh menor que 3? sim, 2 eh menor que 3 ? sim ... ou seja, 3 alocamentos (1 p cada comando)
	{
		readwrite[allocate] = (int *)malloc(sizeof(int) * 2);
		allocate++;
	}
	if (argc < 5)
		error_msg_errno("ERROR", 22, 22);
	while (countpipe < argc - 3)
		if (pipe(readwrite[countpipe++]) == -1)
			error_msg("Failed to do pipe!", 32);
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

void	doexecve(char **paths, char **arguments)
{
	char	*pathdone;
	char	*commandpath;
	int		i;

	i = 0;
	while (paths[i++])
	{
		pathdone = ft_strjoin(paths[i], "/");
		commandpath = ft_strjoin(pathdone, arguments[0]);
		free(pathdone);
		if (!access(commandpath, F_OK | X_OK))
			execve(commandpath, arguments, NULL);
		free(commandpath);
	}
	perror("Command not found!");
}
