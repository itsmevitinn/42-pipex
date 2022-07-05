#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	// int fdinfile = open ("infile.txt", O_WRONLY);
	// int fdoutfile = open ("outfile.txt", O_RDONLY);

	int fd[2];
	pipe(fd);
	int id = fork();
	
	if (id == 0)
	{
		close(fd[0]);
		write(fd[1], "arroz", 5);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		char *buffer;
		buffer = malloc(5);
		read(fd[0], buffer, 5);
		close(fd[0]);
		printf("%s", buffer);
	}
}

