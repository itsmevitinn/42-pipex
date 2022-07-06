#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
	int fd[2];
	pipe(fd);
	int pid = fork();

	if (pid == 0)
	{
		close(fd[0]);
		write(fd[1], "arroz", 5);
		close(fd[1]);
	}
	else
	{
		char *buffer;
		buffer = malloc(5);
		close(fd[1]);
		read(fd[0], buffer, 5);
		close(fd[0]);
		printf("sao: %s", buffer);
	}
}
