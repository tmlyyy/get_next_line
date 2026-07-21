/*
** main.c — programa de teste da parte MANDATORIA do get_next_line.
** NAO faz parte da entrega do projeto, e apenas para validar o
** comportamento e rodar o valgrind antes de submeter.
**
** Requisitos: coloque "test1.txt" e "test2.txt" na mesma pasta
** deste arquivo antes de compilar.
**
** Compilar (igual ao README, so acrescentando este arquivo):
**   cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl_test
**   cc -Wall -Wextra -Werror -D BUFFER_SIZE=5 get_next_line.c get_next_line_utils.c main.c -o gnl_test
**
** Rodar:
**   ./gnl_test
**
** Checar leaks:
**   valgrind --leak-check=full --show-leak-kinds=all ./gnl_test
*/

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

static void	print_line(int n, char *line)
{
	if (line == NULL)
		printf("  [%d] NULL  (fim de leitura)\n", n);
	else
		printf("  [%d] \"%s\"\n", n, line);
}

static void	read_and_print(char *path)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("  erro ao abrir %s (ele esta na mesma pasta?)\n", path);
		return ;
	}
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		print_line(i++, line);
		free(line);
		line = get_next_line(fd);
	}
	print_line(i, line);
	close(fd);
}

int	main(void)
{
	printf("== test1.txt ==\n");
	read_and_print("test1.txt");

	printf("\n== test2.txt ==\n");
	read_and_print("test2.txt");

	printf("\n== fd invalido (nao aberto) ==\n");
	print_line(0, get_next_line(1234));

	printf("\n== fd negativo ==\n");
	print_line(0, get_next_line(-1));

	printf("\n== lendo test1.txt de novo, do zero, ate o fim ==\n");
	read_and_print("test1.txt");

	return (0);
}
