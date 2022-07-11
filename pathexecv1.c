#include "pipex.h"
#include <stdio.h>

int pathexecv1(char *argv[])
{
	extern char **environ;
	char **paths;
	char **arguments;
	int i;
	int j;
	int count;
	count = 0;
	j = 0;
	i = 0;
	arguments = ft_split(argv[1], ' ');
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
		printf("%s\n", paths[j]);
		if (!access(paths[j], F_OK | X_OK))
			execve(paths[j], arguments, NULL);
		count++;
		j++;
	}
	return (0);
}
int main(int argc, char *argv[])
{
	pathexecv1(argv);
}
