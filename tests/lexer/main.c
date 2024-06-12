#include "../inc/tests.h"

int main() 
{
	FILE *file = fopen("lexer/ft_quotes.txt", "r");
	if (!file) {
		perror("No se pudo abrir el archivo de casos de prueba");
		return 1;
	}

	char line[256];
	while (fgets(line, sizeof(line), file)) {
		char *semicolon = strchr(line, ';');
		if (!semicolon) {
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
		test_ft_quotes(input, expected);
	}
	fclose(file);
    return 0;
}
