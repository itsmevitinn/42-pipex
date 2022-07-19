/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/18 22:06:51 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex2.h"

int	main(int argc, char *argv[], char **env)
{
	int ratos = argc - 4;
	int	readwrite[argc - 4][2]; // a quantidade de pipes sera sempre a quantidade de comandos - 1
	int countpipe;
	int pid[argc - 3]; // 1 fork para cada comando, comando = argc - 3
	int countcommands;
	int countpid;
	int indexargv;

	indexargv = 2;
	countpid = 0;
	countpipe = 0;
	countcommands = 0;
	if (argc < 5)
		error_msg_errno("ERROR", 22, 22);
	while (countpipe < argc - 4)
		if (pipe(readwrite[countpipe++]) == -1)
			error_msg("Failed to do pipe!", 32);
	while(countcommands < argc - 3)
	{
		pid[countpid] = fork();
		if (pid[countpid] == 0 && countpid == 0)
		{
			close_first_command(readwrite);
			runfirstcommand(argv[indexargv], readwrite[argc - 4], env);
		}
		else if (pid[countpid] == 0)
		{
			close_middle_commands(readwrite, countpid);
			runmiddlecommand(argv[indexargv], readwrite[argc - 4], countpid, env);
		}
		else if (pid[countpid] == 0 && countpid == argc - 2)
		{
			close_last_command(readwrite, argc);
			runlastcommand(argv[indexargv], readwrite[argc - 4], countpid, argc, env);
		}
		indexargv++;
		countpid++;
		countcommands++;
	}
}

void	close_first_command(int **readwrite)
{
	int indexchecker;

	indexchecker = 0;

	while(readwrite[indexchecker])
	{
		if(indexchecker == 0)
			close(readwrite[indexchecker][0]); //no primeiro pipe fecho a leitura dele, pois apenas escrevo.
		else
		{
			close(readwrite[indexchecker][0]);
			close(readwrite[indexchecker][1]);
		}
		indexchecker++;
	}
}

void	close_middle_commands(int **readwrite, int indexpipe)
{
	int indexchecker;

	indexchecker = 0;

	while(readwrite[indexchecker])
	{
		if(indexchecker == indexpipe)
		{
			close(readwrite[indexchecker][0]); //fecho a leitura do pipe atual pois leio do pipe anterior
			close(readwrite[indexchecker - 1][1]); //fecho a escrita do pipe anterior pois escrevo no pipe atual
		}
		else //fecho tudo que nao uso
		{
			close(readwrite[indexchecker][0]);
			close(readwrite[indexchecker][1]);
		}
		indexchecker++;
	}
}

void	close_last_command(int **readwrite, int argc)
{
	int indexchecker;

	indexchecker = 0;

	while(readwrite[indexchecker])
	{
		if(indexchecker == argc - 3)
			close(readwrite[indexchecker][1]); //fecho apenas a escrita do penultimo pipe pois no ultimo pipe eu leio do penultimo
		else //fecho tudo
		{
			close(readwrite[indexchecker][0]);
			close(readwrite[indexchecker][1]);
		}
		indexchecker++;
	}
}

void	runfirstcommand(char *argv, int **readwrite, char **env)
{
	int fdinfile;
	fdinfile = open(argv[1], O_RDONLY);
	dup2(fdinfile, 0);
	dup2(readwrite[0][1], 1);
	close(readwrite[0][1]);
}

void	runmiddlecommands(char *argv, int **readwrite, int indexpipe, char **env)
{
	dup2(readwrite[indexpipe - 1][0], 0);
	dup2(readwrite[indexpipe][1], 1);
	close(readwrite[indexpipe - 1][0]);
	close(readwrite[indexpipe][1]);
	pathfilter(argv, env);
}

void	runlastcommand(char *argv, int **readwrite, int indexpipe, int argc, char **env)
{
	int fdoutfile;
	fdoutfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(readwrite[indexpipe - 1][0], 0);
	dup2(fdoutfile, 1);
	close(readwrite[indexpipe - 1][0]);
}

void	pathfilter(char *argv, char **envp)
{
	char		**paths;
	char		**arguments;
	int			i;
	int			countargs;

	i = 0;
	arguments = ft_split(argv, ' ');
	// while (arguments[countargs++])
	// 	arguments[countargs] = ft_strtrim(arguments[countargs], "'");
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths = ft_split(&envp[i][5], ':');
		i++;
	}
	doexecve(paths, arguments);
}

void	doexecve(char **paths, char **arguments)
{
	char		*pathdone;
	char		*commandpath;
	int			i;

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
