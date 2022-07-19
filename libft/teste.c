#include <stdio.h>
#include "libft.h"
int main (void)
{
	int i = 0;
	char *teste;
	teste = "seja bem vindo meu 'amigo chato'";

	char **converted;
	converted = ft_split2(teste, ' ');

	while(converted[i])
	{
		printf("String[%i]: %s\n", i, converted[i]);
		i++;
	}
}
