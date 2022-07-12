#include "pipex.h"
int main(int argc, char *argv[])
{
	int fdinfile = open("infile.txt", O_RDONLY);
	int fdoutfile = open("outfile.txt", O_WRONLY);
	int readWrite[2];
	int pid;
	// check_params(argc);
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
	else if (pid == 0)
	{
		close(readWrite[0]);
		dup2(readWrite[1], 1);
		pathexecv1(argv);
		close(readWrite[1]);
	}
	else
	{
		close(readWrite[1]);
		wait(&pid);
		dup2(readWrite[0], 0);
		pathexecv2(argv);
		close(readWrite[0]);
	}
}
