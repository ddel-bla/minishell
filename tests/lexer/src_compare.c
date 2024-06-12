#include "../inc/tests.h"

void compare(const char *input, const char *expected)
{
	char buffer[100];
	strcpy(buffer, input);
	ft_quotes(buffer);

	if (strcmp(buffer, expected) == 0) {
		printf("Prueba pasada: \"%s\" -> \"%s\"\n", input, buffer);
	} else {
		printf("Prueba fallida: \"%s\" -> \"%s\" (esperado: \"%s\")\n", input, buffer, expected);
	}
}
