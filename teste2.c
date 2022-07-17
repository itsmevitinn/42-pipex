#include "pipex.h"
int main(int argc, char **argv, char **envp)
{
int readWrite[2];

// pipe(readwrite[index]);
//
int readwrite[argc - 2][2];
int i;
int j;
int pid[argc - 2];
j = 0;
i = 0;
while (i++ < argc - 2)
	if (pipe(readwrite[i]) == -1)
		perror("Failed to do pipe");
	
while(j < argc - 2)
{

}
	int fdinfile = open (argv[1], O_RDONLY);
	pid[j] = fork();

	pid[j]

	if (pid1 == 0)
	{
		close(readwrite[index])
		dup2(fdinfile, 0);
		dup2(readwrite[index++], 1);
		execve...
	}
}
