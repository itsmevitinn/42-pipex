#include <fcntl.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int fdinfile = open("infile.txt", O_RDONLY, 0777);
	int fdoutfile = open("outfile.txt", O_WRONLY, 0777);
	int fd[2];
	pipe(fd);
	int pid = fork();
	
	if (pid == 0)
	{
		char *buffer;
		buffer = malloc(6);
		close(fd[1]);
		dup2(fdoutfile, 1);
		read(fd[0], buffer, 6);
		printf("bufer: %s", buffer);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		char *buffer;
		buffer = malloc(6);
		dup2(fdinfile, 0);
		read(0, buffer, 6);
		write(fd[1], buffer, 6);
		close(fd[1]);
		// close(fd[0]);
		// write(fd[1], "arroz", 4);
		// close(fd[1]);
	}
}

