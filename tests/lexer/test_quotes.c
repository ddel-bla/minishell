#include "../inc/tests.h"

void	test_quotes(const char *test_file, int col1_index, int col2_index)
{
	FILE *file;
	
	create_test_file(test_file, col1_index,col2_index);
	file = fopen("files/quotes.txt", "r");
	if (!file) 
	{
		perror("No se pudo abrir el archivo de casos de prueba");
		return ;
	}

	char line[256];
	while (fgets(line, sizeof(line), file)) 
	{
		char *semicolon = strchr(line, ';');
		if (!semicolon)
		{
			fprintf(stderr, "Formato incorrecto en la línea: %s\n", line);
			continue;
		}

		*semicolon = '\0';  // Reemplaza el punto y coma con un terminador nulo
		char *input = line;
		char *expected = semicolon + 1;

		// Elimina el salto de línea del expected si está presente
		char *newline = strchr(expected, '\n');
		if (newline)
			*newline = '\0';
		compare(input, expected);
	}
	fclose(file);
}

