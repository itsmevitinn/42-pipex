#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
int main(int argc, char *argv[])
{
	int fdinfile = open("infile.txt", O_RDONLY);
	int fdoutfile = open("outfile.txt", O_WRONLY);
	int readWrite[2];
	if (pipe(readWrite) == -1)
		perror("Failed to create pipe!");
	//fork return pid of child
	int pid = fork();
	if (pid == 0)
	{
		close(readWrite[0]);
		dup2(readWrite[1], 1);
		char *infile;
		char *cmd1;
		infile = malloc(8 + ft_strlen(argv[1]));
		ft_strlcpy(infile, "INFILE=", 8);
		ft_strlcat(infile, argv[1], 8 + ft_strlen(argv[1]));
		cmd1 = malloc(6 + ft_strlen(argv[2]));
		ft_strlcpy(cmd1, "CMD1=", 6);
		ft_strlcat(cmd1, argv[2], 6 + ft_strlen(argv[2]));
		//o proprio pipexdeve chamar outro execve pra tratar o cmd1, retornar, depois outro execve pra tratar esse retorno
		//nesse primeiro execve do infile/cmd1 devo abrir o infile e rodar o comando baseado nesse infile
		//depois pegar o resultado desse primeiro execve, jogar no execve do cmd2/outfile e finalizar.
		char *const args[] = {"sh", "-c", "< $INFILE $CMD1", NULL};
		char *const env[] = {infile, cmd1, NULL};
		execve("/bin/sh", args, env);
		close(readWrite[1]);
	}
	else
	{
		close(readWrite[1]);
		wait(&pid);
		char *resultcmd1;
		char *envar;
		char *cmd2;
		cmd2 = malloc(ft_strlen(argv[3]));
		envar = malloc(50);
		resultcmd1 = malloc(50);
		//&pid = processo do pai retorna o pid do filho no fork
		read(readWrite[0], resultcmd1, 15);
		ft_strlcpy(cmd2, "CMD2=", 6);
		ft_strlcat(cmd2, argv[3], 6 + ft_strlen(argv[3]));
		ft_strlcpy(envar, "RESULTCMD1=", 20);
		ft_strlcat(envar, resultcmd1, 50);
		// write(fdoutfile, envar, 50);
		char *const args[] = {"sh", "-c", "echo $RESULTCMD1 | $CMD2 > outfile.txt", NULL};
		char *const env[] = {envar, cmd2, NULL};
		execve("/bin/sh", args, env);
	}
}
