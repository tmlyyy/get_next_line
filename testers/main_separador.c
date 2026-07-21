/*
** main_separador.c — testa a alteracao de live coding: separador
** customizado no lugar de '\n'.
** NAO faz parte da entrega do projeto.
**
** Como usar:
**   1. Va em get_next_line_utils.c (ou get_next_line_utils_bonus.c),
**      na funcao gnl_has_nl, e troque o '\n' pelo separador pedido
**      pelo avaliador. Ex: trocar por ',':
**
**          if (s[i] == ',')   // <- era '\n'
**
**   2. Ajuste a macro SEPARADOR abaixo para o MESMO caractere que
**      voce colocou em gnl_has_nl (e so pra este arquivo de teste
**      saber montar um arquivo de exemplo compativel).
**
**   3. Compile (mandatoria):
**        cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main_separador.c -o gnl_sep_test
**
**      ou (bonus):
**        cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c main_separador.c -o gnl_sep_test
**      (nesse caso troque o include logo abaixo para "get_next_line_bonus.h")
**
**   4. Rode: ./gnl_sep_test
*/

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

# ifndef SEPARADOR
#  define SEPARADOR ','
# endif

static void	write_str(int fd, char *s)
{
	write(fd, s, strlen(s));
}

static void	make_test_file(void)
{
	int	fd;

	fd = open("t_separador.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write_str(fd, "campo1,campo2,campo3,campo4 sem separador no final");
	close(fd);
}

static void	print_line(int n, char *line)
{
	if (line == NULL)
		printf("  [%d] NULL (fim de leitura)\n", n);
	else
		printf("  [%d] \"%s\"\n", n, line);
}

int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	printf("Separador esperado neste teste: '%c'\n", SEPARADOR);
	printf("(se voce mudou gnl_has_nl para outro caractere, ajuste\n");
	printf(" a macro SEPARADOR no topo deste arquivo tambem)\n\n");

	make_test_file();

	printf("== arquivo separado por '%c' ==\n", SEPARADOR);
	fd = open("t_separador.txt", O_RDONLY);
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

	return (0);
}
