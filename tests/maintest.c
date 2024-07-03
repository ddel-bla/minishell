#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void ft_exec_proc(char **cmd) {
	execvp(cmd[0], cmd);
	perror("execvp");
	exit(EXIT_FAILURE);
}

void ft_pipe_and_fork(char ***cmds, int n) {
	int fds[2];
	int pid;
	int prev_fd;
	int i;

	prev_fd = 0; // Para la lectura del extremo previo de la tubería
	i = 0;
	while (i < n - 1)
	{
		if (pipe(fds) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (pid == 0) 
		{
			// Proceso hijo
			close(fds[0]); // Cerrar el extremo de lectura de la tubería actual
			dup2(prev_fd, STDIN_FILENO); // Redirigir stdin al extremo previo de la tubería
			dup2(fds[1], STDOUT_FILENO); // Redirigir stdout al extremo de escritura de la tubería actual
			close(fds[1]); // Cerrar el extremo de escritura de la tubería actual
			ft_exec_proc(cmds[i]);
		} 
		else 
		{
			// Proceso padre
			close(fds[1]); // Cerrar el extremo de escritura de la tubería actual
			close(prev_fd); // Cerrar el extremo previo de lectura, ya que no es necesario
			prev_fd = fds[0]; // Guardar el extremo de lectura de la tubería actual para la siguiente iteración
		}
		i++;
	}

	// El último comando
	dup2(prev_fd, STDIN_FILENO); // Redirigir stdin al extremo de lectura de la última tubería
	close(prev_fd); // Cerrar el extremo de lectura de la última tubería
	ft_exec_proc(cmds[n - 1]);
}

int main(int argc, char *argv[]) 
{
	if (argc < 2) 
	{
		fprintf(stderr, "Usage: %s \"cmd1 arg1 | cmd2 arg2 | ...\"\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// Parse input commands
	char *input = strdup(argv[1]);
	char *token;
	char **cmd;
	char ***cmds;
	int i, j, count;

	count = 1;
	i = 0;
	while (input[i]) 
	{
		if (input[i] == '|')
			count++;
		i++;
	}

	cmds = malloc(count * sizeof(char **));
	token = strtok(input, "|");
	i = 0;
	while (token != NULL) {
		cmd = malloc(10 * sizeof(char *)); // Asumir máximo 10 argumentos por comando
		char *arg = strtok(token, " ");
		j = 0;
		while (arg != NULL)
		{
			cmd[j] = arg;
			arg = strtok(NULL, " ");
			j++;
		}
		cmd[j] = NULL;
		cmds[i] = cmd;
		token = strtok(NULL, "|");
		i++;
	}

	ft_pipe_and_fork(cmds, count);

	free(input);
	i = 0;
	while (i < count) 
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
	return 0;
}
