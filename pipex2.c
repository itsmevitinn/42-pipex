#include "pipex.h"
int main(int argc, char *argv[])
{
	int fdinfile = open(argv[1], O_RDONLY);
	int fdoutfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	int readWrite[2];
	int pid;
	check_params(argc);
	errorhandling(fdinfile, fdoutfile);
	if (pipe(readWrite) == -1)
	{
		perror("Failed to create pipe!");
		exit(1);
	}
	// parent's fork return pid of child
	pid = fork();
	if (pid == -1)
	{
		perror("Failed to do first fork!");
		exit(1);
	}
	else if (pid == 0)
	{
		dup2(fdinfile, 0);
		close(readWrite[0]);
		dup2(readWrite[1], 1);
		pathexecv1(argv);
		close(readWrite[1]);
	}
	waitpid(pid, NULL, 0);
	close(readWrite[1]);
	dup2(readWrite[0], 0);
	dup2(fdoutfile, 1);
	pathexecv2(argv);
	close(readWrite[0]);
}

void	pathexecv1(char *argv[])
{
	extern char **environ;
	char **paths;
	char **arguments;
	int i;
	int j;
	j = 0;
	i = 0;
	arguments = ft_split(argv[2], ' ');
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			paths = ft_split(&environ[i][5], ':');
		i++;
	}
	while (paths[j])
	{
		paths[j] = ft_strjoin(paths[j], "/");
		paths[j] = ft_strjoin(paths[j], arguments[0]);
		if (!access(paths[j], F_OK | X_OK))
			execve(paths[j], arguments, NULL);	
		j++;
	}
	// free(paths[j]);
}

void	pathexecv2(char *argv[])
{
	extern char **environ;
	char **paths;
	char **arguments;
	int i;
	int j;
	j = 0;
	i = 0;
	arguments = ft_split(argv[3], ' ');
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			paths = ft_split(&environ[i][5], ':');
		i++;
	}
	while (paths[j])
	{
		paths[j] = ft_strjoin(paths[j], "/");
		paths[j] = ft_strjoin(paths[j], arguments[0]);
		if (!access(paths[j], F_OK | X_OK))
			execve(paths[j], arguments, NULL);
		j++;
	}
	// free(paths[j]);
}
void	errorhandling(int fdinfile, int fdoutfile)
{
	if (fdinfile == -1 | fdoutfile == -1)
	{
		perror("Failed to open files");
		exit(1);
	}
}
