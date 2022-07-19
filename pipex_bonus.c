/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/19 02:49:27 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char **env)
{
	int readwrite[argc - 4][2]; // a quantidade de pipes sera sempre a quantidade de comandos - 1
	int countpipe;
	int pid[argc - 3]; // 1 fork para cada comando, comando = argc - 3
	int countpid;

	countpid = 0;
	countpipe = 0;
	if (argc < 5)
		error_msg_errno("ERROR", 22, 22);
	while (countpipe < argc - 3)
	{
		if (pipe(readwrite[countpipe]) == 0)
		{
			printf("Pipe [%i]\n", countpipe);
			countpipe++;
		}
	}
	pid[countpid] = fork();
	if (pid[countpid] == 0)
	{
		printf("First Child [%i]\n", countpid);
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
			printf("Mid child [%i]\n", countpid);
			close_middle_commands(argc, readwrite, countpid);
			runcmds(argv[countpid + 2], readwrite[countpid - 1][0], readwrite[countpid][1], env);
		}
		countpid++;
	}
	pid[countpid] = fork();
	if (pid[countpid] == 0)
	{
		printf("Last child [%i]\n", countpid);
		int fdoutfile;
		fdoutfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		close_last_command(argc, readwrite, countpid);
		runcmds(argv[argc - 2], readwrite[countpid - 1][0], fdoutfile, env);
	}
	close_all(argc, readwrite);
	wait(pid);
	return (0);
}

void close_all(int argc, int readwrite[argc - 4][2])
{
	int index;
	index = 0;
	while (readwrite[index])
	{
		close(readwrite[index][0]);
		close(readwrite[index][1]);
		index++;
	}
}

void close_first_command(int argc, int readwrite[argc - 4][2])
{
	int indexchecker;

	indexchecker = 0;

	while (readwrite[indexchecker])
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
}

void close_middle_commands(int argc, int readwrite[argc - 4][2], int indexpipe)
{
	int indexchecker;

	indexchecker = 0;

	while (readwrite[indexchecker])
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

void close_last_command(int argc, int readwrite[argc - 4][2], int indexpipe)
{
	int indexchecker;

	indexchecker = 0;

	while (readwrite[indexchecker])
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

	i = 0;
	arguments = ft_split(argv, ' ');
	// while (arguments[countargs++])
	// 	arguments[countargs] = ft_strtrim(arguments[countargs], "'");
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
