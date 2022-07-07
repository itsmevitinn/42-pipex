#include <fcntl.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
int main(int argc, char *argv[])
{
	int fdinfile = open("infile.txt", O_RDONLY);
	int readWrite[2];
	pipe(readWrite);
	//fork return pid of child
	int pid = fork();
	
	char *infile = (char *)malloc(ft_strlen(argv[1]));
	char *cmd1 = (char *)malloc(ft_strlen(argv[2]));
	char *cmd2 = (char *)malloc(ft_strlen(argv[3]));
	char *outfile = (char *)malloc(ft_strlen(argv[4]));

	char *const args[] = {binaryPath, "-c", "< $infile $cmd1 | $cmd2 > $outfile", NULL};
	char *const env[] = {infile, cmd1, cmd2, outfile, NULL};
	if (pid == 0)
	{
		close(readWrite[0]);
		char *command1;
		command1 = malloc(15);
		read(fdinfile, command1, 15);
		write(readWrite[1], command1, 15);
		close(readWrite[1]);
	}
	else
	{
		close(readWrite[1]);
		wait(&pid);
		dup2(readWrite[0], 0);
		execve("./teste.out", NULL, NULL);
	}
}
