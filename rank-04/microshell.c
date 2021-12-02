#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef enum e_type
{
	end_type,
	pipe_type,
	semicolon_type
}			t_type;

//Good old ft_strlen
int	ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

void	print_error(char *s)
{
	write(STDERR_FILENO, s, ft_strlen(s));
}

void	fatal_error(char **s)
{
	if (s != NULL)
		free(s);
	print_error("error: fatal\n");
	exit(EXIT_FAILURE);
}

// if first argument is NUll then has 0 arguments
// if second argument is not NULL then has more than 1 argument
// both cases are wrong
void	cd(char **arguments)
{
	if (arguments[0] == NULL || arguments[1] != NULL)
		print_error("error: cd: bad arguments\n");
	else if (chdir(arguments[0]) == -1)
	{
		print_error("error: cd: cannot change directory to ");
		print_error(arguments[0]);
		print_error("\n");
	}
}

int		parse_next_command(char **input, char ***command, t_type *type)
{
	int i = 0;
	while (input[i] && strcmp(input[i], "|") && strcmp(input[i], ";"))
		i++;
	
	if (i == 0)
		return (1);
	else if ((*command = (char**)malloc(sizeof(char*) * (i + 1))) == NULL)
		fatal_error(NULL);
	
	for (int j = 0; j < i; j++)
		(*command)[j] = input[j]; // reuses pointers, no need for ft_strdup()
	(*command)[i] = NULL;

	if (input[i] == NULL)
		*type = end_type;
	else if (!strcmp(input[i], "|"))
		*type = pipe_type;
	else if (!strcmp(input[i], ";"))
		*type = semicolon_type;
	return (i + 1);
}


int		main(int argc, char **argv, char **env)
{
	t_type	type;
	int		pipes[2];
	int		pid;
	int		last_time_pipe = 0;
	int		stdin_copy = dup(STDIN_FILENO);
	char	**command;

	argv = &argv[1];

	for (int i = 1; i < argc; i++)
	{
		int x = parse_next_command(argv, &command, &type);
		argv = &argv[x];

		if (x == 1) // go to next iteration
			continue;
		else if (!strcmp(command[0], "cd"))
			cd(&command[1]);
		else
		{
			if (type == pipe_type && pipe(pipes) == -1)
				fatal_error(command);

			pid = fork();
			if (pid == -1)
			{
				close(pipes[0]);
				close(pipes[1]);
				fatal_error(command);
			}
			else if (pid == 0) // child process
			{
				if (type == pipe_type)
					dup2(pipes[1], STDOUT_FILENO);
				if (execve(command[0], command, env) == -1)
				{
					print_error("error: cannot execute ");
					print_error(command[0]);
					print_error("\n");
				}
				close(pipes[0]);
				close(pipes[1]);
				free(command);
				return (0);
			}
			else
				waitpid(pid, NULL, 0);
		}
		free(command);
		if (type == pipe_type)
		{
			dup2(pipes[0], STDIN_FILENO);
			last_time_pipe = 1;
			close(pipes[0]);
			close(pipes[1]);
		}
		else
		{
			if (last_time_pipe == 1)
				last_time_pipe = 0;
			dup2(stdin_copy, STDIN_FILENO);
		}
		if (type == end_type)
			break;
	}
	close(stdin_copy);
	return (0);
}