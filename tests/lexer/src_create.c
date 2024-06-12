#include "../inc/tests.h"

void create_test_file(const char *test_file, int col1_index, int col2_index) 
{
	FILE *src = fopen("files/tests.txt", "r");
	FILE *dst = fopen(test_file, "w");

	if (!src) 
	{
		perror("No se pudo abrir el archivo de origen");
		return;
	}
	if (!dst) 
	{
		perror("No se pudo abrir el archivo de pruebas");
		fclose(src);
		return;
	}

	char line[256];
	while (fgets(line, sizeof(line), src)) 
	{
		char *columns[10];  // Suponiendo un máximo de 10 columnas
		int col_count = 0;

		// Tokeniza la línea por comas
		char *token = strtok(line, ";");
		while (token && col_count < 10) 
		{
			columns[col_count++] = token;
			token = strtok(NULL, ";");
		}

		// Verifica que las columnas especificadas existan
		if (col1_index < col_count && col2_index < col_count) {
			fprintf(dst, "%s;%s\n", columns[col1_index], columns[col2_index]);
		} else
			fprintf(stderr, "Índices de columna fuera de rango en la línea: %s\n", line);
	}

	fclose(src);
	fclose(dst);
}
