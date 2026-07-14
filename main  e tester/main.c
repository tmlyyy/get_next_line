#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 1;
	printf("--- Teste 1: FD Inválido (42) ---\n");
	line = get_next_line(42);
	if (line == NULL)
		printf("OK: Retornou NULL para FD inválido.\n\n");
	else
	{
		printf("ERRO: Deveria retornar NULL.\n\n");
		free(line);
	}
	if (argc < 2)
		fd = 0;
	else
	{
		printf("--- Teste 2: Lendo do arquivo '%s' ---\n", argv[1]);
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			perror("Erro ao abrir arquivo");
			return (1);
		}
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("[%02d]|%s", line_count++, line);
		free(line);
	}
	if (line == NULL)
		printf("\n--- FIM DO ARQUIVO / EOF --- \n");
	if (fd != 0)
		close(fd);
	return (0);
}
