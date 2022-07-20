/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/20 16:56:56 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft/libft.h"

int main(int argc, char *argv[], char **env)
{
	int **readwrite; // a quantidade de pipes sera sempre a quantidade de comandos - 1
	int countpipe;
	int pid[argc - 3]; // 1 fork para cada comando, comando = argc - 3
	int countpid;
	int allocate;
	int countwait;

	countwait = 0;
	allocate = 0;
	readwrite = (int **)malloc(sizeof(int *) * (argc - 3)); // eh -3 e nao -4 pois estamos trabalhando com aloocamento, e a contagem comeca no 1, diferente do array que comeca no 0
	while (allocate < argc - 3) // aqui a mesma coisa, ex.: temos 3 comandos, ou seja, 6 argumentos - 3 = 3 (comandos), 0 eh menor que 3 ? sim, 1 eh menor que 3? sim, 2 eh menor que 3 ? sim ... ou seja, 3 alocamentos (1 p cada comando)
	{
		printf("8 bytes mallocados para as colunas da matriz: readwrite[%i]\n", allocate);
		readwrite[allocate] = (int *)malloc(sizeof(int) * 2);
		allocate++;
	}
	countpid = 0;
	countpipe = 0;
	if (argc < 5)
		error_msg_errno("ERROR", 22, 22);
	while (countpipe < argc - 3)
	{
		// if (pipe(readwrite[countpipe++]) == -1)
			// error_msg("Failed to do pipe!", 32);
		if (pipe(readwrite[countpipe]) == 0)
			printf("Pipe posicao [%i] criado!\n", countpipe);
		countpipe++;
	}
	pid[countpid] = fork();
	if (pid[countpid] == 0)
	{
		int fdinfile;
		fdinfile = open(argv[1], O_RDONLY);
		close_first_command(argc, readwrite);
		runcmds(argv[2], fdinfile, readwrite[0][1], env);
	}
	countpid++;
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
	{
		int fdoutfile;
		fdoutfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		close_last_command(argc, readwrite, countpid);
		runcmds(argv[argc - 2], readwrite[countpid - 1][0], fdoutfile, env);
	}
	close_all(argc, readwrite);
	while (countwait < argc - 3)
	{
		int res;
		res = waitpid(pid[countwait], NULL, 0);
		printf("I waited for my child ID: %i\n", res);
		countwait++;
	}
	return (0);
}

void close_all(int argc, int **readwrite)
{
	int index;

	index = 0;
	while (index < argc - 4)
	{
		close(readwrite[index][0]);
		close(readwrite[index][1]);
		index++;
	}
}

void close_first_command(int argc, int **readwrite)
{
	int indexchecker;

	indexchecker = 0;

	while (indexchecker < argc - 4)
	{
		if (indexchecker == 0)
		{
			close(readwrite[indexchecker][0]); // fecho apenas a leitura do pipe 0 pois a escrita eu utilizo
		}
		else
		{
			close(readwrite[indexchecker][0]);
			close(readwrite[indexchecker][1]);
		}
		indexchecker++;
	}
}

void close_middle_commands(int argc, int **readwrite, int indexpipe)
{
	int indexchecker;

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

void close_last_command(int argc, int **readwrite, int indexpipe)
{
	int indexchecker;

	indexchecker = 0;

	while (indexchecker < argc - 4)
	{
		if (indexchecker == indexpipe - 1)
			close(readwrite[indexchecker][1]); // fecho a escrita do pipe anterior e preservo a leitura
		else								   // fecho tudo
		{
			close(readwrite[indexchecker][0]);
			close(readwrite[indexchecker][1]);
		}
		indexchecker++;
	}
}

void runcmds(char *argv, int input, int output, char **env)
{
	dup2(input, 0);
	close(input);
	dup2(output, 1);
	close(output);
	pathfilter(argv, env);
}

void pathfilter(char *argv, char **env)
{
	char **paths;
	char **arguments;
	int i;
	int countargs;
	
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
	doexecve(paths, arguments);
}

void doexecve(char **paths, char **arguments)
{
	char *pathdone;
	char *commandpath;
	int i;

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
