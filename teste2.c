#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "pipex.h"
int main(int argc, char *argv[])
{
	int fdinfile = open("infile.txt", O_RDONLY);
	int fdoutfile = open("outfile.txt", O_WRONLY);
	int readWrite[2];
	int pid;
	check_params(argc);
	if (fdinfile == -1 || fdoutfile == -1)
	{
		perror("Failed to open file!");
		exit(1);
	}
	if (pipe(readWrite) == -1)
	{
		perror("Failed to create pipe!");
		exit(1);
	}
	// parent's fork return pid of child
	pid = fork();
	if (pid == -1)
	{
		perror("Failed to do fork!");
		exit(1);
	}
	// child
	else if (pid == 0)
	{
		close(readWrite[0]);
		dup2(readWrite[1], 1);
		// tratar o pipe passando aqui kkk 
		pathexecv1(argv);
		//o proprio pipexdeve chamar outro execve pra tratar o cmd1, retornar, depois outro execve pra tratar esse retorno
		//nesse primeiro execve do infile/cmd1 devo abrir o infile e rodar o comando baseado nesse infile
		//depois pegar o resultado desse primeiro execve, jogar no execve do cmd2/outfile e finalizar.
		close(readWrite[1]);
	}
	else
	{
		char *buffer;
		buffer = malloc(50);
		close(readWrite[1]);
		wait(&pid);
		dup2(readWrite[0], 0);
		char *const args[] = {argv[3], NULL};
		char *const env[] = {NULL};
		if (execve("/usr/bin/wc", args, env) == -1 )
		{
			perror("Second execve failed");
			exit(1);
		}
		close(readWrite[0]);
	}
}
