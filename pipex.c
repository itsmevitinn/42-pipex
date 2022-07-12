#include "pipex.h"
int main(int argc, char *argv[])
{
	int fdoutfile = open(argv[4], O_WRONLY | O_CREAT);
	int readWrite[2];
	int pid;
	check_params(argc);
	if (fdoutfile == -1)
	{
		perror("Failed to open outfile!");
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
		dup2(fdoutfile, 1);
		pathexecv2(argv);
		close(readWrite[0]);
	}
}

void	pathexecv1(char *argv[])
{
	extern char **environ;
	char **paths;
	char **arguments;
	char *infile;
	int i;
	int params;
	int j;
	params = 0;
	j = 0;
	i = 0;
	infile = argv[1];
	arguments = ft_split(argv[2], ' ');
	while (arguments[params])
		params++;
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
		{
			arguments[params] = infile;
			execve(paths[j], arguments, NULL);	
		}
		j++;
	}
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
}
