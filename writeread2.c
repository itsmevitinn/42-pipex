#include <fcntl.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int fdinfile = open("infile.txt", O_RDONLY, 0777);
	int fdoutfile = open("outfile.txt", O_WRONLY, 0777);
	int readWrite[2];
	pipe(readWrite);
	int pid = fork();
	
	if (pid == 0)
	{
		char *buffer;
		buffer = malloc(6);
		close(readWrite[1]);
		dup2(fdoutfile, 1);
		read(readWrite[0], buffer, 6);
		write(1, buffer, 6);
		close(readWrite[0]);
	}
	else
	{
		close(readWrite[0]);
		char *buffer;
		buffer = malloc(6);
		dup2(fdinfile, 0);
		read(0, buffer, 6);
		write(readWrite[1], buffer, 6);
		close(readWrite[1]);
	}
}

