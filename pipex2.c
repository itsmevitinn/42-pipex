/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:12:28 by vsergio           #+#    #+#             */
/*   Updated: 2022/07/16 23:35:30 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex2.h"

int	main(int argc, char *argv[], char **envp)
{
	int	readwrite[argc - 4][2];
	int countpipe;
	int pid[argc - 3];
	int i;
	int countpid;
	int indexargv;
	int indexpipe;
	int close[argc - 4][2];

	indexpipe = 0;
	indexargv = 2;
	countpid = 0;
	countpipe = 0;
	i = 0;
	// if (argc != 6)
	// 	error_msg_errno("ERROR", 22, 22);
	while (countpipe++ < argc - 4)
	{
		if (pipe(readwrite[countpipe]) == -1)
			error_msg("Failed to do pipe!", 32);
	}
	while(i++ < argc - 3)
	{
		pid[countpid] = fork();
		if (pid[countpid++] == 0 && countpid == 0)
		{
			int fdinfile;
			fdinfile = open(argv[1], O_RDONLY);
			close(readwrite[0][0]);
			close(readwrite[1][0]);
			close(readwrite[1][1]);
			close(readwrite[2][0]);
			close(readwrite[2][1]);
			dup2(fdinfile, 0);
			dup2(readwrite[0][1], 1)
			firstcommand(argv[indexargv++], envp, &readwrite[1][2]);
			close(readwrite[0][1]);
		}
		else if (pid[countpid++] == 0)
		{
			dup2()
			middlecommands(argv[indexargv++], envp, readwrite);
		}
		else if (pid[countpid++] == 0 && countpid == argc - 2)
		{

			commandtofile(argv[indexargv++], envp, readwrite);
		}
	}
}

void	writecommand(char *argv, char **envp, int readwrite[5][3])
{

}

void	docommand(char *argv, char **envp, int **readwrite)
{
	int i;
	i = 0;
	close();	
}
	// pid = fork();
	// if (pid == -1)
		// error_msg("Failed to do first fork!", 10);
	// else if (pid == 0)
	{
		int	fdinfile;

		fdinfile = open(argv[1], O_RDONLY);
		if (fdinfile == -1)
			error_msg("Failed to open infile!", 2);
		close(readwrite[0][0]);
		close(readwrite[1][0]);
		close(readwrite[1][1]);
		close(readwrite[2][0]);
		close(readwrite[2][1]);
		dup2(fdinfile, 0);
		dup2(readwrite[0][1], 1);
		close(readwrite[0][1]);
		pathfilter(argv[2], envp);
	}
		// firstchild(argv, readwrite, envp);
	// pid2 = fork();
	// if (pid2 == -1)
	// 	error_msg("Failed to do second fork!", 10);
	// else if (pid2 == 0)
	{
		close(readwrite[0][1]);
		close(readwrite[1][0]);
		close(readwrite[2][0]);
		close(readwrite[2][1]);
		dup2(readwrite[0][0], 0);
		dup2(readwrite[1][1], 1);
		close(readwrite[0][0]);
		close(readwrite[1][1]);
		pathfilter(argv[3], envp);
	}
		// secondchild(argv, readwrite, envp);
	// pid3 = fork();
	// if (pid3 == -1)
	// 	error_msg("Failed to do third fork!", 10);
	// else if (pid3 == 0)
	{
		int	fdoutfile;

		fdoutfile = open(argv[5], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fdoutfile == -1)
			error_msg("Failed to open outfile!", 2);
		close(readwrite[0][0]);
		close(readwrite[0][1]);
		close(readwrite[1][1]);
		close(readwrite[2][0]);
		close(readwrite[2][1]);
		dup2(readwrite[1][0], 0);
		dup2(fdoutfile, 1);
		close(readwrite[1][0]);
		pathfilter(argv[4], envp);
	}	
			// thirdchild(argv, readwrite, envp);
	close(readwrite[0][0]);
	close(readwrite[0][1]);
	close(readwrite[1][0]);
	close(readwrite[1][1]);
	close(readwrite[2][0]);
	close(readwrite[2][1]);
	// waitpid(pid, NULL, 0);
	// waitpid(pid2, NULL, 0);
	// waitpid(pid3, NULL, 0);
	// return (0);
}

// void	firstchild(char **argv, int **readwrite, char **envp)
// {
// 	int	fdinfile;

// 	fdinfile = open(argv[1], O_RDONLY);
// 	if (fdinfile == -1)
// 		error_msg("Failed to open infile!", 2);
// 	close(readwrite[0][0]);
// 	dup2(fdinfile, 0);
// 	dup2(readwrite[0][1], 1);
// 	close(readwrite[0][1]);
// 	close(readwrite[1][0]);
// 	close(readwrite[1][1]);
// 	close(readwrite[2][0]);
// 	close(readwrite[2][1]);
// 	pathfilter(argv[2], envp);
// }

// void	secondchild(char **argv, int **readwrite, char **envp)
// {
	// close(readwrite[0][1]);
	// dup2(readwrite[0][0], 0);
	// dup2(readwrite[1][1], 1);
	// close(readwrite[0][0]);
	// close(readwrite[1][0]);
	// close(readwrite[1][1]);
	// close(readwrite[2][0]);
	// close(readwrite[2][1]);
	// pathfilter(argv[3], envp);
// }

// void	thirdchild(char **argv, int **readwrite, char **envp)
// {
	// int	fdoutfile;

	// fdoutfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	// if (fdoutfile == -1)
	// 	error_msg("Failed to open outfile!", 2);
	// close(readwrite[1][1]);
	// dup2(readwrite[1][0], 0);
	// dup2(fdoutfile, 1);
	// 	close(readwrite[0][0]);
	// 	close(readwrite[0][1]);
	// 	close(readwrite[1][0]);
	// 	close(readwrite[2][0]);
	// 	close(readwrite[2][1]);
	// 	pathfilter(argv[3], envp);
// }

void	pathfilter(char *argv, char **envp)
{
	char		**paths;
	char		**arguments;
	int			i;
	int			countargs;

	i = 0;
	arguments = ft_split(argv, ' ');
	while (arguments[countargs++])
		arguments[countargs] = ft_strtrim(arguments[countargs], "'");
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
