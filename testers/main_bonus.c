/*
** main_bonus.c — programa de teste da parte BONUS do get_next_line.
** NAO faz parte da entrega do projeto.
**
** Requisitos: coloque "test1.txt" e "test2.txt" na mesma pasta
** deste arquivo antes de compilar.
**
** Compilar (igual ao README, so acrescentando este arquivo):
**   cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus_test
**   cc -Wall -Wextra -Werror -D BUFFER_SIZE=5 get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus_test
**
** Rodar:
**   ./gnl_bonus_test
**
** Checar leaks:
**   valgrind --leak-check=full --show-leak-kinds=all ./gnl_bonus_test
*/

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

static void	print_line(char *label, char *line)
{
	if (line == NULL)
		printf("  %s: NULL (fim de leitura)\n", label);
	else
		printf("  %s: \"%s\"\n", label, line);
}

int	main(void)
{
	int		fd_a;
	int		fd_b;
	char	*line;

	printf("== leitura intercalada: test1.txt (A) e test2.txt (B) ==\n");
	fd_a = open("test1.txt", O_RDONLY);
	fd_b = open("test2.txt", O_RDONLY);
	if (fd_a == -1 || fd_b == -1)
	{
		printf("erro ao abrir test1.txt/test2.txt (estao na mesma pasta?)\n");
		return (1);
	}

	line = get_next_line(fd_a); print_line("A", line); free(line);
	line = get_next_line(fd_b); print_line("B", line); free(line);
	line = get_next_line(fd_a); print_line("A", line); free(line);
	line = get_next_line(fd_b); print_line("B", line); free(line);
	line = get_next_line(fd_a); print_line("A", line); free(line);
	line = get_next_line(fd_b); print_line("B", line); free(line);

	printf("\n-- esvaziando o resto de A --\n");
	line = get_next_line(fd_a);
	while (line != NULL)
	{
		print_line("A", line);
		free(line);
		line = get_next_line(fd_a);
	}
	print_line("A (fim)", line);

	printf("\n-- esvaziando o resto de B --\n");
	line = get_next_line(fd_b);
	while (line != NULL)
	{
		print_line("B", line);
		free(line);
		line = get_next_line(fd_b);
	}
	print_line("B (fim)", line);

	close(fd_a);
	close(fd_b);

	printf("\n== fd invalido (nao aberto, dentro do MAX_FD) ==\n");
	line = get_next_line(1234);
	print_line("invalido", line);
	free(line);

	printf("\n== fd negativo ==\n");
	line = get_next_line(-1);
	print_line("negativo", line);
	free(line);

	printf("\n== fd fora da tabela (>= MAX_FD) ==\n");
	line = get_next_line(999999);
	print_line("fora_da_tabela", line);
	free(line);

	printf("\n== reabrindo test1.txt do zero (novo fd) e lendo tudo ==\n");
	fd_a = open("test1.txt", O_RDONLY);
	line = get_next_line(fd_a);
	while (line != NULL)
	{
		print_line("A2", line);
		free(line);
		line = get_next_line(fd_a);
	}
	print_line("A2", line);
	close(fd_a);

	return (0);
}
