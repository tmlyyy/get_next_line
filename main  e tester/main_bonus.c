#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;
	int		line_count;

	line_count = 1;
	printf("--- Teste 1: FD Inválido (42) ---\n");
	line1 = get_next_line(42);
	if (line1 == NULL)
		printf("OK: Retornou NULL para FD inválido.\n\n");
	else
	{
		printf("ERRO: Deveria retornar NULL.\n\n");
		free(line1);
	}
	if (argc < 3)
	{
		fd1 = 0;
		while ((line1 = get_next_line(fd1)) != NULL)
		{
			printf("[%02d]|%s", line_count++, line1);
			free(line1);
		}
	}
	else
	{
		printf("--- Teste 2: Leitura intercalada de '%s' e '%s' ---\n", argv[1], argv[2]);
		fd1 = open(argv[1], O_RDONLY);
		fd2 = open(argv[2], O_RDONLY);
		if (fd1 < 0 || fd2 < 0)
		{
			perror("Erro ao abrir arquivos");
			return (1);
		}
		line1 = (char *)1;
		line2 = (char *)1;
		while (line1 != NULL || line2 != NULL)
		{
			if (line1 != NULL)
			{
				line1 = get_next_line(fd1);
				if (line1 != NULL)
				{
					printf("[ARQ 1 - Linha %02d]| %s", line_count, line1);
					free(line1);
				}
			}
			if (line2 != NULL)
			{
				line2 = get_next_line(fd2);
				if (line2 != NULL)
				{
					printf("[ARQ 2 - Linha %02d]| %s", line_count, line2);
					free(line2);
				}
			}
			line_count++;
		}
		close(fd1);
		close(fd2);
	}
	printf("\n--- FIM DOS TESTES BÔNUS --- \n");
	return (0);
}
