/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h> // used in unix_pipe.c?
#include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>

#define MAX_LINE 80 /* 80 chars per line, per command */
#define READ_END 0	// used for fd pipe in unix_pipe.c
#define WRITE_END 1

const char *delim = " \t\r\n\v\f";

int parse_input(char *args[], char *cmd);

int parse_redirect_in(char *str, char **str_input);

int parse_redirect_out(char *str, char **str_input);

void execPiped(char **parsed, char **parsedpipe);

int main(void)
{
	char *args[MAX_LINE / 2 + 1]; /* command line (of 80) has max of 40 arguments */
	char *cmd = (char *)malloc(MAX_LINE + 1);

	int should_run = 1;

	// if input flag, "1", if outputflag "2", none "0"
	parse_redirect();

	while (should_run)
	{
		printf("osh>");
		fflush(stdout);

		int args_num = parse_input(args, cmd);

		/**
         	 * After reading user input, the steps are:
         	 * (1) fork a child process
         	 * (2) the child process will invoke execvp()
         	 * (3) if command included &, parent will invoke wait()
         	 */

		// see unix_pipe.c
		pid_t pid;
		//int fd[2];

		/* create the pipe 
		if (pipe(fd) == -1)
		{
			fprintf(stderr, "Pipe failed");
			return 1;
		} 
		*/

		/* now fork a child process */
		pid = fork();

		if (pid < 0)
		{
			fprintf(stderr, "Fork failed");
			return 1;
		}
		// child process running execvp
		else if (pid == 0)
		{ /* child process */
			execvp(args[0], args);
		}
		// (3) parent will invoke wait() unless comand included &
		else
		{
			// if has &. run concurrently with child
			wait(NULL);
		}
	}

	// free memory
	free(args);

	return 0;
}

int parse_input(char *args[], char *cmd)
{
	// Read command
	int arg_num = 0; // number of arguments
	if (fgets(cmd, MAX_LINE + 1, stdin) == NULL)
	{
		fprintf(stderr, "Error reading command.\n");
		free(cmd);
		exit(1);
	}

	// break command into tokens
	args[arg_num] = strtok(cmd, delim); // get 1st token
	while (args[arg_num] != NULL)
	{ // get the rest
		++arg_num;
		args[arg_num] = strtok(NULL, delim);
	}

	// HISTORY
	// if user enters "!!" as input, repeat last command.
	if (args[0] == "!!")
	{

		// if no command in history, return error message

		// length of command array == 0
		// print "No commands found in history"
	}

	// keep log of commands
	strcpy(args, cmd);

	return arg_num;
};

// function for parsing command words
void parseSpace(char *str, char **parsed)
{
	int i;

	for (i = 0; i < MAX_LINE; i++)
	{
		parsed[i] = strsep(&str, " ");

		if (parsed[i] == NULL)
			break;
		if (strlen(parsed[i]) == 0)
			i--;
	}
};

int processString(char *str, char **parsed, char **parsedpipe, char **parse_redirect)
{

	char *strpiped[2];
	char *str_input[2], *str_output[2];
	int piped = 0;
	int redirect = 0;

	piped = parsePipe(str, strpiped);

	redirect = parse_redirect(str, str_redirect);

	if (piped)
	{
		parseSpace(strpiped[0], parsed);
		parseSpace(strpiped[1], parsedpipe);
	}
	else if (redirect)
	{
		parseSpace(str_input[0], parsed);
		parseSpace(str_input[1], parse_redirect);
	}
	else
	{
		parseSpace(str, parsed);
	}

	//if (ownCmdHandler(parsed))
	//return 0;
	//else
	//return 1 + piped;
};

int parse_redirect(char *str, char **str_redirect)
{
	/*
	int i;
	for (i = 0; i < 2; i++)
	{
		//output redirect
		str_input[i] = strtok(&str, "<");
		if (str_input[i] == NULL)
			break;
	}
	if (str_input[1] == NULL)
		return 0; // returns zero if no redirect is found
	else
	{
	}
	*/
	for (i = 0; argv[i] != '\0'; i++)
	{
		if (strcmp(argv[i], "<") == 0)
		{
			argv[i] = NULL;
			strcpy(input, argv[i + 1]);
			return 1;
		}

		if (strcmp(argv[i], ">") == 0)
		{
			argv[i] = NULL;
			strcpy(output, argv[i + 1]);
			return 2;
		}
	}
};

// function for finding pipe
int parsePipe(char *str, char **strpiped) // https://www.geeksforgeeks.org/making-linux-shell-c/
{
	int i;
	for (i = 0; i < 2; i++)
	{
		strpiped[i] = strtok(&str, "|");
		if (strpiped[i] == NULL)
			break;
	}

	if (strpiped[1] == NULL)
		return 0; // returns zero if no pipe is found.
	else
	{
		return 1;
	}
};

void execRedirect(char **parsed, char **parse_redirect)
//https://stackoverflow.com/questions/11515399/implementing-shell-in-c-and-need-help-handling-input-output-redirection
{
	int fd[2];
	pid_t pid;

	char input[64], output[64];

	pid = fork();

	if (pid < 0)
	{
		fprintf(stderr, "Fork failed");
		return 1;
	}

	else if (pid == 0)
	{
		// input flag
		if (redirect = 2)
		{
			// input file descriptor
			int fd0 = open(input, O_RDONLY);
			dup2(fd0, STDIN_FILENO);
			close(fd0);
		}

		// output flag
		if (redirect = 3)
		{
			int fd1 = creat(output, 0644);
			dup2(fd1, STDOUT_FILENO);
			close(fd1);
		}

		execvp(*argv, argv);
		perror("execvp");
		exit(1);
	}
	else
	{ //parent
		while (!(wait(&status) == pid))
		// good coding to avoid race_conditions(errors)
	}
};

void execPiped(char **parsed, char **parsedpipe)
// https://www.geeksforgeeks.org/making-linux-shell-c/
{
	// 0 is read end, 1 is write end
	int pipefd[2];
	pid_t p1, p2;

	if (pipe(pipefd) < 0)
	{
		printf("\nPipe could not be initialized");
		return;
	}
	p1 = fork();
	if (p1 < 0)
	{
		printf("\nCould not fork");
		return;
	}

	if (p1 == 0)
	{
		// Child 1 executing..
		// It only needs to write at the write end
		close(pipefd[READ_END]);
		dup2(pipefd[WRITE_END], STDOUT_FILENO);
		close(pipefd[WRITE_END]);

		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nCould not execute command 1..");
			exit(0);
		}
	}
	else
	{
		// Parent executing
		p2 = fork();

		if (p2 < 0)
		{
			printf("\nCould not fork");
			return;
		}

		// Child 2 executing..
		// It only needs to read at the read end
		if (p2 == 0)
		{
			close(pipefd[WRITE_END]);
			dup2(pipefd[READ_END], STDIN_FILENO);
			close(pipefd[READ_END]);
			if (execvp(parsedpipe[0], parsedpipe) < 0)
			{
				printf("\nCould not execute command 2..");
				exit(0);
			}
		}
		else
		{
			// parent executing, waiting for two children
			wait(NULL);
			wait(NULL);
		}
	}
};